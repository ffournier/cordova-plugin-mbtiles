//
//  MBTilesActionsGenDataBaseImpl
//
//  Created on 20/03/14.
//
//

#import "MBTilesActionsGenImpl.h"
#import <sqlite3.h>

/**
 * Treat database SQLite
 */
@interface MBTilesActionsGenDataBaseImpl : MBTilesActionsGenImpl
{
    // the database
    sqlite3* database;
    // synchronized
    NSLock* lock;
}

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
