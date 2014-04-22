//
//  MBTilesActionsFileImpl.h
//
//  Created on 21/03/14.
//
//

#import "MBTilesActionsGenImpl.h"

/**
* Treat file
*/
@interface MBTilesActionsFileImpl : MBTilesActionsGenImpl
{
    // the path of file
    NSString* file;
}

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
