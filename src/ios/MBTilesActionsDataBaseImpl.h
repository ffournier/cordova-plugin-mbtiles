//
//  MBTilesActionsGenDataBaseImpl
//
//  Created on 20/03/14.
//
//

#import "MBTilesActionsGenImpl.h"
#import "CDVFile.h"
#import <sqlite3.h>

/**
 * Treat database SQLite
 */
@interface MBTilesActionsDataBaseImpl : MBTilesActionsGenImpl
{
    // the database
    sqlite3* database;
    // synchronized
    NSLock* lock;
}

/*
 * init with a specific typepath and specific url
 */
- (id) initWithTypePath:(NSString*)typePath withCDVFile:(CDVFile*)filePlugin withUrl:(NSString*) url;


/**
 * bind value to the statement of sqlite
 *
 * @param stmt the statement of the request
 * @param params the parameters to bind
 * @return YES or NO
 */
- (BOOL) bindValue:(sqlite3_stmt*)stmt withParams:(NSArray*)params;

@property(readwrite, assign)sqlite3* database;
@property(readwrite, retain)NSLock* lock;

@end
