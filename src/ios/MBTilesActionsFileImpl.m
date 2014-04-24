//
//  MBTilesActionsFileImpl.m
//
//  Created on 21/03/14.
//
//

#import "MBTilesActionsFileImpl.h"
#import "MBTilesConstant.h"

@implementation MBTilesActionsFileImpl
@synthesize directory = _directory;
@synthesize file = _file;

/**
* initialisation
*/
- (id) init {
    self = [super init];
    _file = nil;
    
    self.directory = @"maps/";
    return self;
  
    return self;
}

- (void)open:(NSString*) name {
    [self close];

    
    NSFileManager *filemgr =  [NSFileManager defaultManager];
    BOOL value;
    NSString* dir = [self getFullDirectory];
    
    _file = nil;
    // test if file exist
    if ([filemgr fileExistsAtPath:dir isDirectory:&value] == YES) {
        if (value) {
            _file = dir;
        }
    }
}

- (BOOL)isOpen {
    return _file != nil;
}

- (void)close {
   _file = nil;
}

+ (BOOL) isFileExist: (NSString*) path {
    NSFileManager *filemgr =  [NSFileManager defaultManager];
    return[filemgr fileExistsAtPath: path];
}

- (NSDictionary*)getMetadata {
    NSDictionary* dict = [[NSDictionary alloc] init];
    
    if([self isOpen] == YES) {
        NSString* pathFile = [_file stringByAppendingPathComponent:@"metadata.json"];
        if ([MBTilesActionsFileImpl isFileExist:pathFile]) {
            dict = [NSDictionary dictionaryWithContentsOfFile:pathFile];
        }
    }
    return dict;
}

- (NSArray*) getZoomLevel {
    NSDictionary* dict = [self getMetadata];
    if (dict) {
        NSString* name = dict[KEY_NAME];
        NSString* version = dict[KEY_VERSION];
        if (name && version) {
            NSString* pathDir = [_file stringByAppendingPathComponent:version];
            pathDir = [pathDir stringByAppendingPathComponent:name];
	    
            NSMutableArray* list = [[NSMutableArray alloc] init];
            NSDirectoryEnumerator * enumDir = [[NSFileManager defaultManager] enumeratorAtPath:pathDir];
            if (enumDir != nil) {
                NSString * fileTemp;
		    
                while (fileTemp = [enumDir nextObject]) {
                    NSInteger val = [fileTemp integerValue];
                    if (val) {
                        [list addObject:[NSNumber numberWithInt:val]];
                    }
                }
                // sort List
                [list sortedArrayUsingSelector:@selector(compare:)];
            }
            return list;
        }
    }
    return nil;
}

- (NSDictionary*)getMinZoom {
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    
    if([self isOpen] == YES) {
        NSArray* array = [self getZoomLevel];
        if (array != nil && [array count] > 0) {
            [dict setObject:[array firstObject] forKey:KEY_MIN_ZOOM];
        }
    }
    return dict;
}

- (NSDictionary*)getMaxZoom {
    
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    
    if([self isOpen] == YES) {
        NSArray* array = [self getZoomLevel];
        if (array != nil && [array count] > 0) {
            [dict setObject:[array lastObject] forKey:KEY_MAX_ZOOM];
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
        NSDictionary* metadata = [self getMetadata];
        if (metadata) {
            NSString* name = dict[KEY_NAME];
            NSString* version = dict[KEY_VERSION];
            NSString* format = dict[KEY_FORMAT];
            
            if (format && name && version) {
                NSString* tilePath = [_file stringByAppendingPathComponent:version];
                tilePath = [tilePath stringByAppendingPathComponent:name];
                tilePath = [tilePath stringByAppendingPathComponent:[NSString stringWithFormat:@"%d", (int) currentLevelZoom]];
                tilePath = [tilePath stringByAppendingPathComponent:[NSString stringWithFormat:@"%d", (int) column]];
                tilePath = [tilePath stringByAppendingPathComponent:[NSString stringWithFormat:@"%d", (int) row]];
                tilePath = [tilePath stringByAppendingPathExtension:format];
                
                if ([MBTilesActionsFileImpl isFileExist:tilePath]) {
                    // ReadFile
                    NSData* data = [[NSFileManager defaultManager] contentsAtPath:tilePath];
                    if (data) {
                        // Base 64
                        NSString * stringBase64 = [MBTilesConstant base64forData:data];
                        [dict setObject:stringBase64 forKey:KEY_TILE_DATA];
                    }
                }
                
            }
        }
    }
    return dict;
}

- (NSDictionary*)executeStatement:(NSString*) query withParams:(NSArray*) params {
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    if ([self isOpen]) {
        // not implemented
    }
    return dict;
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
