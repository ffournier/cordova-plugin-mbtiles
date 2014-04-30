//
//  NSObject_MBTilesActionsGenImpl.h
//  Geotrek-mobile-mc
//
//  Created by Makina Corpus on 22/04/2014.
//
//

#import "MBTilesActionsGenImpl.h"

@implementation MBTilesActionsGenImpl
@synthesize directory = _directory;
@synthesize typePath = _typePath;
@synthesize cdvfile = _cdvfile;

/**
 * init the class
 */
- (id)init {
    @throw [NSException exceptionWithName:NSInternalInconsistencyException
                                   reason:@"-init is not a valid initializer for the class MBTilesActionsGenImpl"
                                 userInfo:nil];
    return nil;
}


- (id) initWithTypePath:(NSString*)tPath withCDVFile:(CDVFile*) fileplugin{
    self = [super init];
    _typePath = tPath;
    _cdvfile = fileplugin;
    return self;
}


- (NSString*) getDirectory {
    NSString* dir;
    if (_typePath != nil && [_typePath isEqualToString:OPEN_TYPE_PATH_CDVFILE]) {
        dir = self.directory;
        NSRange isRange = [self.directory rangeOfString:@"cdvfile://localhost/persistent/" options:NSCaseInsensitiveSearch];
        if(isRange.location == 0) {
            dir = [self.directory stringByReplacingOccurrencesOfString:@"cdvfile://localhost/persistent/" withString:@""];
        }
        isRange = [self.directory rangeOfString:@"cdvfile://localhost/temporary/" options:NSCaseInsensitiveSearch];
        if(isRange.location == 0) {
            dir = [self.directory stringByReplacingOccurrencesOfString:@"cdvfile://localhost/temporary/" withString:@""];
        }
        return dir;
    } else if (_typePath == nil || [_typePath isEqualToString:OPEN_TYPE_PATH_FULL]) {
        dir =  _directory;
    }
    return dir;
}

- (NSString*) getFullDirectory {
    NSString* dir = nil;
    if (_typePath != nil && [_typePath isEqualToString:OPEN_TYPE_PATH_CDVFILE]) {
        // Get a CDVFilesystem URL object from a URL string
        CDVFilesystemURL* urlCDV = [CDVFilesystemURL fileSystemURLWithString:self.directory];
        // Get a path for the URL object, or nil if it cannot be mapped to a file
        dir = [_cdvfile filesystemPathForURL:urlCDV];
        
    } else if (_typePath == nil || [_typePath isEqualToString:OPEN_TYPE_PATH_FULL]) {
        dir = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex: 0];
        dir = [dir stringByAppendingPathComponent:_directory];
    }
    return dir;
}

/**
 * open database with given parameters
 *
 * @param name the name of the file to open
 */
- (void)open:(NSString*) name {
    mustOverride();
}

/**
 * test if the file was opened
 *
 * @return YES or NO
 */
- (BOOL)isOpen {
    mustOverride();
}


/**
 * close the file
 */
- (void)close {
    mustOverride();
}


/**
 * get the metadata of the file
 *
 * @return a dictionnary which contains the metadata
 */
- (NSDictionary*)getMetadata {
    mustOverride();
}


/**
 * get the min zoom of the file
 *
 * @return a dictionnary which contains the min zoom
 */
- (NSDictionary*)getMinZoom {
    mustOverride();
}


/**
 * get the max zoom of the file
 *
 * @return a dictionnary wich contains the max zoom
 */
- (NSDictionary*)getMaxZoom {
    mustOverride();
}


/**
 * get tiles with given parameters
 *
 * @param zoom_level the zoom level (z)
 * @param column the column (x)
 *  @param row the row (y)
 * @return a dictionnary which contains the tiles associate in base64
 */
- (NSDictionary*)getTile:(int) zoom_level columnValue:(int) column rowValue:(int) row {
    mustOverride();
}


/**
 * execute the given query
 *
 * @param query the query to execute
 * @param params parameters needed
 * @return a dictionnary which contains all object returned by the query
 */
- (NSDictionary*)executeStatement:(NSString*) query withParams:(NSArray*) params {
    mustOverride();
}


/**
 * return the directory of working
 * @return <code>JSONObject</code>
 */
-(NSDictionary*) getDirectoryWorking {
    mustOverride();
}



@end
