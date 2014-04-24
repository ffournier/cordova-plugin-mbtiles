//
//  MBTilesActionsGenImpl
//
//  Created on 20/03/14.
//
//

#import <Foundation/Foundation.h>
#import "MBTilesAction.h"

#define mustOverride() @throw [NSException exceptionWithName:NSInvalidArgumentException reason:[NSString stringWithFormat:@"%s must be overridden in a subclass/category", __PRETTY_FUNCTION__] userInfo:nil]
#define methodNotImplemented() mustOverride()

/**
 * Gen Actions MBTiles
 */
@interface MBTilesActionsGenImpl : NSObject<MBTilesAction>
{
    
    @protected
    
    // the directory
    NSString* directory;
}

- (NSString*) getDirectory;
- (NSString*) getFullDirectory;

@property(readwrite, retain)NSString* directory;

@end
