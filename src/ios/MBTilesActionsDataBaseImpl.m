//
//  MBTilesActionsDataBaseImpl.m
//
//  Created on 20/03/14.
//
//

#import "MBTilesActionsDataBaseImpl.h"

@implementation MBTilesActionsDataBaseImpl

/**
* init the class
*/
- (id) init {
    self = [super init];
    
    self.directory = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex: 0];
    return self;
}

@end
