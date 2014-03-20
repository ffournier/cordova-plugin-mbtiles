//
//  MBTilesActionsDataBaseImpl.h
//  TestCordova2
//
//  Created by florian on 20/03/14.
//
//

#import <Foundation/Foundation.h>
#import "MBTilesAction.h"
#import <sqlite3.h>

@interface MBTilesActionsDataBaseImpl : NSObject<MBTilesAction>
{
    sqlite3* database;
}

@property(readwrite, assign)sqlite3* database;
@end
