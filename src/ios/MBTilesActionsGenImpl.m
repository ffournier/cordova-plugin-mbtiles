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

- (NSString*) getDirectory {
    return _directory;
}

- (NSString*) getFullDirectory {
    NSString* dir = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex: 0];
    return [dir stringByAppendingPathComponent:_directory];
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
