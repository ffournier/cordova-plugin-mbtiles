//
//  MBTilesActionsFileImpl.m
//  TestCordovaPlugin
//
//  Created by florian on 21/03/14.
//
//

#import "MBTilesActionsFileImpl.h"
#import "MBTilesConstant.h"

@implementation MBTilesActionsFileImpl
@synthesize file = _file;

- (id) init {
    self = [super init];
    _file = nil;
    return self;
}

- (void)open:(NSString*) path {
     NSArray* dirs = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
     
     NSString* dirPath = [dirs objectAtIndex:0];
     NSString* folderPath = [dirPath stringByAppendingPathComponent:path];
    
    NSFileManager *filemgr =  [NSFileManager defaultManager];
    
    BOOL isDir;
    if ([filemgr fileExistsAtPath: folderPath isDirectory:&isDir] == YES) {
        if (isDir) {
            _file = folderPath;
        } else {
            _file = nil;
        }
    } else {
        _file = nil;
    }
}

- (BOOL)isOpen {
    return _file != nil;
}

- (void)close {
   
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
            NSDirectoryEnumerator * enumDir = [[NSFileManager defaultManager] enumeratorAtPath:pathDir];
            NSString * fileTemp;
            NSMutableArray* list = [[NSMutableArray alloc] init];
            while (fileTemp = [enumDir nextObject]) {
                NSInteger val = [fileTemp integerValue];
                if (val) {
                    [list addObject:[NSNumber numberWithInt:val]];
                }
            }
            // sort List
            [list sortedArrayUsingSelector:@selector(compare:)];
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

- (NSDictionary*)getExecuteStatment:(NSString*) query withParams:(NSArray*) params {
    NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
    if ([self isOpen]) {
        // not implemented
    }
    return dict;
}

- (void)dealloc {
    if ([self isOpen]) {
        [self close];
    }
}

@end
