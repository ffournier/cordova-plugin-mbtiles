//
//  MBTilesPlugin.h
//
//  Created on 19/03/14.
//
//

#import <Foundation/Foundation.h>
#import <Cordova/CDVPlugin.h>
#import "MBTilesActionsDataBaseImpl.h"
#import "MBTilesActionsFileImpl.h"


/**
* MBTilesPlugin, the plugin to treat *.mbtiles
*/
@interface MBTilesPlugin : CDVPlugin {
    
    // the interface
    id<MBTilesAction> tilesActions;
}

@property(retain) id tilesActions;

/**
* action open 
*/
- (void)open:(CDVInvokedUrlCommand*)command;

/**
* action get_metadata 
*/
- (void)get_metadata:(CDVInvokedUrlCommand*)command;

/**
* action get_min_zoom 
*/
- (void)get_min_zoom:(CDVInvokedUrlCommand*)command;

/**
* action get_max_zoom 
*/
- (void)get_max_zoom:(CDVInvokedUrlCommand*)command;

/**
* action get_tile 
*/
- (void)get_tile:(CDVInvokedUrlCommand*)command;

/**
* action execute_statement
*/
- (void)execute_statement:(CDVInvokedUrlCommand*)command;

/**
* action get_directory_working
*/
- (void)get_directory_working:(CDVInvokedUrlCommand*) command;

@end
