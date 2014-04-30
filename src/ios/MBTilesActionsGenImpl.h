//
//  MBTilesActionsGenImpl
//
//  Created on 20/03/14.
//
//

#import <Foundation/Foundation.h>
#import "MBTilesAction.h"
#import "MBTilesConstant.h"
#import "CDVFile.h"

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
    // the directory
    NSString* typePath;
    
    // cdvfile
    CDVFile* cdvfile;
}

- (id) initWithTypePath:(NSString*)tPath withCDVFile:(CDVFile*) fileplugin;

- (NSString*) getDirectory;
- (NSString*) getFullDirectory;

@property(readwrite, retain)NSString* directory;
@property(readwrite, retain)NSString* typePath;
@property(readwrite, retain)CDVFile* cdvfile;


@end
