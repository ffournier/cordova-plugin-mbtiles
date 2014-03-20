//
//  MBTilesPlugin.h
//  TestCordova2
//
//  Created by florian on 19/03/14.
//
//

#import <Foundation/Foundation.h>
#import <Cordova/CDVPlugin.h>
#import "MBTilesActionsDataBaseImpl.h"



@interface MBTilesPlugin : CDVPlugin {
    
    id<MBTilesAction> tilesActions;
}

@property(retain) id tilesActions;

- (void)open:(CDVInvokedUrlCommand*)command;
- (void)get_metadata:(CDVInvokedUrlCommand*)command;
- (void)get_min_zoom:(CDVInvokedUrlCommand*)command;
- (void)get_max_zoom:(CDVInvokedUrlCommand*)command;
- (void)get_tile:(CDVInvokedUrlCommand*)command;

@end
