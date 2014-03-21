//
//  MBTilesActionsFileImpl.h
//  TestCordovaPlugin
//
//  Created by florian on 21/03/14.
//
//

#import <Foundation/Foundation.h>
#import "MBTilesAction.h"

@interface MBTilesActionsFileImpl : NSObject<MBTilesAction>
{
    NSString* file;
}

+ (BOOL) isFileExist: (NSString*) path;
- (NSArray*) getZoomLevel;

@property(readwrite, assign)NSString* file;
@end
