//
//  MBTilesActionsDataBaseImpl.m
//
//  Created on 20/03/14.
//
//

#import "MBTilesActionsGenDataBaseImpl.h"
#import "MBTilesConstant.h"
#import "CDVFile.h"


@implementation MBTilesActionsGenDataBaseImpl
@synthesize database = _database;
@synthesize lock = _lock;

/**
 * init the class
 */
- (id) init {
    self = [super init];
    _database = nil;
    _lock = [[NSLock alloc] init];
    return self;
}

- (void)open:(NSString*) name {
    
    [self close];
    
    NSFileManager *filemgr =  [NSFileManager defaultManager];
    NSString* dir = [self getFullDirectory];
    if (dir != nil) {
        NSString *absolutePath = [dir stringByAppendingPathComponent:name];
        // test if the file exist
        if ([filemgr fileExistsAtPath: absolutePath ] == YES) {
            const char *dbpath = [absolutePath UTF8String];
            // open the database
            if (sqlite3_open_v2(dbpath, &_database, SQLITE_OPEN_READONLY, NULL) != SQLITE_OK) {
                _database = nil;
            }
        } else {
            _database = nil;
        }
    }
}

- (BOOL)isOpen {
    return _database != nil;
}

- (void)close {
    if (_database != nil) {
        // close db
        sqlite3_close(_database);
    }
    database = nil;
}

- (NSDictionary*)getMetadata {
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    
    // test if the db is open
    if([self isOpen] == YES) {
        // run query metadata
        const char* query = [[NSString stringWithFormat:@"SELECT * FROM metadata"] UTF8String];
        sqlite3_stmt* stmt;
        [_lock lock];
        int ret = sqlite3_prepare_v2(_database, query, -1, &stmt, NULL);
        if(ret == SQLITE_OK) {
            // loop answer
            while(sqlite3_step(stmt) == SQLITE_ROW) {
                NSString* name = [NSString stringWithUTF8String:(const char*)sqlite3_column_text(stmt, 0)];
                NSString* type = [NSString stringWithUTF8String:(const char*)sqlite3_column_text(stmt, 1)];
                if (name && type) {
                    [dict setObject:type forKey:name];
                }
            }
            sqlite3_finalize(stmt);
        }
        [_lock unlock];
    }
    return dict;
}

- (NSDictionary*)getMinZoom {
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    
    // test id the db is open
    if([self isOpen] == YES) {
        // run query min zoom
        const char* query = [[NSString stringWithFormat:@"SELECT MIN(zoom_level) AS min_zoom_level FROM tiles"] UTF8String];
        sqlite3_stmt* stmt;
        [_lock lock];
        int ret = sqlite3_prepare_v2(_database, query, -1, &stmt, NULL);
        if( ret == SQLITE_OK) {
            // treat the answer
            if(sqlite3_step(stmt) == SQLITE_ROW) {
                int min = sqlite3_column_int(stmt, 0);
                [dict setObject:[NSNumber numberWithInt:min] forKey:KEY_MIN_ZOOM];
            }
            sqlite3_finalize(stmt);
        }
        [_lock unlock];
    }
    return dict;
}

- (NSDictionary*)getMaxZoom {
    
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    
    // test if the db is open
    if([self isOpen] == YES) {
        // run query max zoom
        const char* query = [[NSString stringWithFormat:@"SELECT MAX(zoom_level) AS max_zoom_level FROM tiles"] UTF8String];
        sqlite3_stmt* stmt;
        [_lock lock];
        int ret = sqlite3_prepare_v2(_database, query, -1, &stmt, NULL);
        if( ret == SQLITE_OK) {
            // treat the answer
            if(sqlite3_step(stmt) == SQLITE_ROW) {
                int max = sqlite3_column_int(stmt, 0);
                [dict setObject:[NSNumber numberWithInt:max] forKey:KEY_MAX_ZOOM];
            }
            sqlite3_finalize(stmt);
        }
        [_lock unlock];
    }
    return dict;
}

- (NSDictionary*)getTile:(int) zoom_level columnValue:(int) column rowValue:(int) row {
    
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    NSInteger currentLevelZoom = zoom_level;
    
    // test if db is open
    if ([self isOpen]) {
        // get max zoom
        NSDictionary* data = [self getMaxZoom];
        if (data) {
            int maxZoom  = [data[KEY_MAX_ZOOM] intValue];
            // if the currentlevelzoom is higher than the max zoom, reinit it.
            if (currentLevelZoom > maxZoom) {
                currentLevelZoom = maxZoom;
            }
        }
        // run query of tiles.
        const char* query = [[NSString stringWithFormat:@"SELECT tile_data FROM tiles WHERE zoom_level = ?1 AND tile_column = ?2 AND tile_row = ?3"] UTF8String];
        sqlite3_stmt* stmt;
        [_lock lock];
        int ret = sqlite3_prepare_v2(_database, query, -1, &stmt, NULL);
        if( ret == SQLITE_OK) {
            // bind value
            sqlite3_bind_int(stmt, 1, currentLevelZoom);
            sqlite3_bind_int(stmt, 2, column);
            sqlite3_bind_int(stmt, 3, row);
            // treat answer
            if(sqlite3_step(stmt) == SQLITE_ROW) {
                NSUInteger blobLenght = sqlite3_column_bytes(stmt, 0);
                NSData * data = [NSData dataWithBytes:sqlite3_column_blob(stmt, 0) length:blobLenght];
                NSString * stringBase64 = [MBTilesConstant base64forData:data];
                [dict setObject:stringBase64 forKey:KEY_TILE_DATA];
            }
            sqlite3_finalize(stmt);
        }
        [_lock unlock];
    }
    return dict;
}

- (NSDictionary*)executeStatement:(NSString*) query withParams:(NSArray*) params {
    
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    NSMutableArray* rows = [NSMutableArray arrayWithCapacity:0];
    // test if the database is open
    if ([self isOpen]) {
        // run given query
        const char* sql_stmt = [query UTF8String];
        sqlite3_stmt* stmt;
        [_lock lock];
        int ret = sqlite3_prepare_v2(_database, sql_stmt, -1, &stmt, NULL);
        if( ret == SQLITE_OK) {
            
            // bind value
            BOOL result = [self bindValue:stmt withParams:params];
            if (result == YES) {
                NSMutableDictionary* row;
                
                // treat answer
                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    int count = sqlite3_column_count(stmt);
                    row = [NSMutableDictionary dictionaryWithCapacity:0];
                    for (int i = 0; i < count ; i++) {
                        // get type of column
                        int type = sqlite3_column_type(stmt, i);
                        // get name of column
                        NSString* name = [NSString stringWithFormat:@"%s",sqlite3_column_name(stmt, i)];
                        NSObject* object;
                        switch(type) {
                            case SQLITE_INTEGER:
                                object = [NSNumber numberWithInt:sqlite3_column_int(stmt, i)];
                                break;
                            case SQLITE_FLOAT:
                                object = [NSNumber numberWithDouble:sqlite3_column_double(stmt, i)];
                                break;
                            case SQLITE_TEXT:
                                object = [NSString stringWithUTF8String:(char*)sqlite3_column_text(stmt, i)];
                                break;
                            case SQLITE_BLOB:
                            {
                                NSUInteger blobLenght = sqlite3_column_bytes(stmt, i);
                                NSData * data = [NSData dataWithBytes:sqlite3_column_blob(stmt, i) length:blobLenght];
                                object = [MBTilesConstant base64forData:data];
                            }
                                break;
                            case SQLITE_NULL:
                            default:
                                object = [NSNull null];
                                break;
                        }
                        
                        if (object) {
                            // add object in row
                            [row setObject:object forKey:name];
                        }
                    }
                    // add row in rows
                    [rows addObject:row];
                }
            }
        }
        sqlite3_finalize(stmt);
        [_lock unlock];
        // add rows in result dictionnary
        [dict setObject:rows forKey:KEY_EXECUTE_STATEMENT];
    }
    return dict;
}

- (BOOL) bindValue:(sqlite3_stmt*)stmt withParams:(NSArray*)params {
    if (params) {
        for (int i = 1; i <= [params count]; i++) {
            NSObject* object = [params objectAtIndex:(i-1)];
            if (object) {
                // test type of object
                if ([object isEqual:[NSNull null]]) {
                    sqlite3_bind_null(stmt, i);
                } else if ([object isKindOfClass:[NSNumber class]]) {
                    NSNumber* arg = (NSNumber*) object;
                    const char* numberType = [arg objCType];
                    if (strcmp(numberType, @encode(int))) {
                        sqlite3_bind_int(stmt, i, [arg integerValue]);
                    } else if (strcmp(numberType, @encode(long long int))) {
                        sqlite3_bind_int64(stmt, i, [arg longLongValue]);
                    } else if (strcmp(numberType, @encode(double))) {
                        sqlite3_bind_double(stmt, i, [arg doubleValue]);
                    } else if (strcmp(numberType, @encode(float))) {
                        sqlite3_bind_double(stmt, i, [arg floatValue]);
                    } else {
                        sqlite3_bind_text(stmt, i, [[NSString stringWithFormat:@"%@", object] UTF8String], -1, SQLITE_TRANSIENT);
                    }
                } else {
                    sqlite3_bind_text(stmt, i, [[NSString stringWithFormat:@"%@", object] UTF8String], -1, SQLITE_TRANSIENT);
                }
            }
        }
    }
    return YES;
}

- (NSDictionary*) getDirectoryWorking {
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    
    [dict setObject:[self getDirectory] forKey:KEY_DIRECTORY_WORKING];
    return dict;
}

- (void)dealloc {
    if ([self isOpen]) {
        [self close];
    }
}

@end
