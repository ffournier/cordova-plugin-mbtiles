//
//  MBTilesActionsFileImpl.h
//
//  Created on 21/03/14.
//
//

#import "MBTilesActionsGenImpl.h"
#import "CDVFile.h"

/**
* Treat file
*/
@interface MBTilesActionsFileImpl : MBTilesActionsGenImpl
{
    // the path of file
    NSString* file;
}

/*
 * init with a specific typepath and specific url
 */
- (id) initWithTypePath:(NSString*)typePath withCDVFile:(CDVFile*)filePlugin withUrl:(NSString*) url;

/** 
 * test if file exist
 *
 * @param path the path of file to test
 * @return if file exist
 */
+ (BOOL) isFileExist: (NSString*) path;

/** 
 * get all Zoom Level
 *
 * @return the existing zoom level
 */
- (NSArray*) getZoomLevel;

@property(readwrite, assign)NSString* file;
@end
