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
    
    NSString* dir = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex: 0];
    dir = [dir stringByAppendingPathComponent:@"tiles"];
    self.directory = [dir stringByAppendingString:@"/"];
    return self;
}

@end
