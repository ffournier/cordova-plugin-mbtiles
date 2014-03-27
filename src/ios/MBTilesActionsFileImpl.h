//
//  MBTilesActionsFileImpl.h
//
//  Created on 21/03/14.
//
//

#import <Foundation/Foundation.h>
#import "MBTilesAction.h"

/**
* Treat file
*/
@interface MBTilesActionsFileImpl : NSObject<MBTilesAction>
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
