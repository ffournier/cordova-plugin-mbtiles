//
//  MBTilesActionsDataBaseImpl.h
//
//  Created on 20/03/14.
//
//

#import <Foundation/Foundation.h>
#import "MBTilesAction.h"
#import <sqlite3.h>

/**
* Treat database SQLite
*/
@interface MBTilesActionsDataBaseImpl : NSObject<MBTilesAction>
{
    // the database
    sqlite3* database;
    // synchronized
    NSLock* lock;
}

/** 
 * bind value to the statment of sqlite
 *
 * @param stmt the statment of the request
 * @param params the parameters to bind
 * @return YES or NO
 */
- (BOOL) bindValue:(sqlite3_stmt*)stmt withParams:(NSArray*)params;

@property(readwrite, assign)sqlite3* database;
@property(readwrite, retain)NSLock* lock;

@end
