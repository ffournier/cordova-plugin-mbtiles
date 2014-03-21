//
//  MBTilesActionsDataBaseImpl.m
//  TestCordova2
//
//  Created by florian on 20/03/14.
//
//

#import "MBTilesActionsDataBaseImpl.h"
#import "MBTilesConstant.h"

@implementation MBTilesActionsDataBaseImpl
@synthesize database = _database;

- (void)open:(NSString*) path {
    NSFileManager *filemgr =  [NSFileManager defaultManager];
   
    NSArray* list = [path componentsSeparatedByString:@"."];
    NSString* absolutePath = [[NSBundle mainBundle] pathForResource:[list objectAtIndex:0] ofType:[list objectAtIndex:1]];
    
    if ([filemgr fileExistsAtPath: absolutePath ] == YES) {
        const char *dbpath = [absolutePath UTF8String];
        
        if (sqlite3_open_v2(dbpath, &_database, SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK) {
            _database = nil;
        }
    }
}

- (BOOL)isOpen {
    return _database != nil;
}

- (void)close {
    if (_database != nil) {
        sqlite3_close(_database);
    }
}

- (NSDictionary*)getMetadata {
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    
    if([self isOpen] == YES) {
        const char* query = [[NSString stringWithFormat:@"SELECT * FROM metadata"] UTF8String];
        sqlite3_stmt* stmt;
        int ret = sqlite3_prepare_v2(_database, query, -1, &stmt, NULL);
        if(ret == SQLITE_OK) {
            
            while(sqlite3_step(stmt) == SQLITE_ROW) {
                NSString* name = [NSString stringWithUTF8String:(const char*)sqlite3_column_text(stmt, 0)];
                NSString* type = [NSString stringWithUTF8String:(const char*)sqlite3_column_text(stmt, 1)];
                if (name && type) {
                    [dict setObject:name forKey:type];
                }
            }
            sqlite3_finalize(stmt);
        }
    }
    return dict;
}

- (NSDictionary*)getMinZoom {
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    
    if([self isOpen] == YES) {
        const char* query = [[NSString stringWithFormat:@"SELECT MIN(zoom_level) AS min_zoom_level FROM tiles"] UTF8String];
        sqlite3_stmt* stmt;
        int ret = sqlite3_prepare_v2(_database, query, -1, &stmt, NULL);
        if( ret == SQLITE_OK) {
            
            if(sqlite3_step(stmt) == SQLITE_ROW) {
               int min = sqlite3_column_int(stmt, 0);
               [dict setObject:[NSNumber numberWithInt:min] forKey:KEY_MIN_ZOOM];
            }
            sqlite3_finalize(stmt);
        }
    }
    return dict;
}

- (NSDictionary*)getMaxZoom {
    
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    
    if([self isOpen] == YES) {
        const char* query = [[NSString stringWithFormat:@"SELECT MAX(zoom_level) AS max_zoom_level FROM tiles"] UTF8String];
        sqlite3_stmt* stmt;
        int ret = sqlite3_prepare_v2(_database, query, -1, &stmt, NULL);
        if( ret == SQLITE_OK) {
            
            if(sqlite3_step(stmt) == SQLITE_ROW) {
                int max = sqlite3_column_int(stmt, 0);
                [dict setObject:[NSNumber numberWithInt:max] forKey:KEY_MAX_ZOOM];
            }
            sqlite3_finalize(stmt);
        }
    }
    return dict;
}

- (NSDictionary*)getTile:(int) zoom_level columnValue:(int) column rowValue:(int) row {
    
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    NSInteger currentLevelZoom = zoom_level;
    
    if ([self isOpen]) {
        NSDictionary* data = [self getMaxZoom];
        if (data) {
           currentLevelZoom = [data[KEY_MAX_ZOOM] intValue];
        }
        const char* query = [[NSString stringWithFormat:@"SELECT tile_data FROM tiles WHERE zoom_level = ?1 AND tile_column = ?2 AND tile_row = ?3"] UTF8String];
        sqlite3_stmt* stmt;
        int ret = sqlite3_prepare_v2(_database, query, -1, &stmt, NULL);
        if( ret == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, zoom_level);
            sqlite3_bind_int(stmt, 2, column);
            sqlite3_bind_int(stmt, 3, row);
            if(sqlite3_step(stmt) == SQLITE_ROW) {
                NSUInteger blobLenght = sqlite3_column_bytes(stmt, 0);
                NSData * data = [NSData dataWithBytes:sqlite3_column_blob(stmt, 0) length:blobLenght];
                NSString * stringBase64 = [MBTilesConstant base64forData:data];
                [dict setObject:stringBase64 forKey:KEY_TILE_DATA];
            }
            sqlite3_finalize(stmt);
        }
    }
    return dict;
}

- (void)dealloc {
    if ([self isOpen]) {
        [self close];
    }
}

@end
