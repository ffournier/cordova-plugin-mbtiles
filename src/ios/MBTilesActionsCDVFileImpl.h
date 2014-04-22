//
//  MBTilesActionsCDVFileImpl.h
//
//  Created on 20/03/14.
//
//

#import "MBTilesActionsGenDataBaseImpl.h"
#import "CDVFile.h"

/**
 * Treat database SQLite
 */
@interface MBTilesActionsCDVFileImpl : MBTilesActionsGenDataBaseImpl
{
}

/*
 * init with the defautl url
 */
-(id) initWithCDVFile:(CDVFile*)filePlugin;

/*
 * init with a specific url
 */
- (id) initWithCDVFile:(CDVFile*)filePlugin withUrl:(NSString*) cdvfileURL;

@end