//
//  MBTilesPlugin.m
//
//  Created on 19/03/14.
//
//

#import "MBTilesPlugin.h"
#import "MBTilesConstant.h"


@implementation MBTilesPlugin

@synthesize tilesActions;

- (void)open:(CDVInvokedUrlCommand*)command {
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* pluginResult = nil;
        
        NSDictionary* dict = [command.arguments objectAtIndex:0];
         // get the type and name
        NSString* type = dict[KEY_TYPE];
        NSString* name = dict[KEY_NAME];
        if (type && name) {
            // open db with name
            if ([type isEqualToString:@"db"]) {
                tilesActions = [[MBTilesActionsDataBaseImpl alloc] init];
                [tilesActions open:name];
                
                if ([tilesActions isOpen]) {
                   pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
                } else {
                     pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
                }
            // open file name     
            } else if ([type isEqualToString:@"file"]) {
                tilesActions = [[MBTilesActionsFileImpl alloc] init];
                [tilesActions open:name];
                if ([tilesActions isOpen]) {
                   pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
                } else {
                     pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
                }
            } else {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_INVALID_ACTION];
            }
        }
    
        // The sendPluginResult method is thread-safe.
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

- (void)get_metadata:(CDVInvokedUrlCommand*)command {
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* pluginResult = nil;
        
        // test is open
        if ([tilesActions isOpen]) {
            // get metadata
            NSDictionary* data = [tilesActions getMetadata];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:data];
        } else {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        }
        // The sendPluginResult method is thread-safe.
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

- (void)get_min_zoom:(CDVInvokedUrlCommand*)command {
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* pluginResult = nil;
        // test is open
        if ([tilesActions isOpen]) {
            // get min zoom
            NSDictionary* data = [tilesActions getMinZoom];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:data];
        } else {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        }
        
        // The sendPluginResult method is thread-safe.
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

- (void)get_max_zoom:(CDVInvokedUrlCommand*)command {
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* pluginResult = nil;
        // test is open
        if ([tilesActions isOpen]) {
            // get max zoom
            NSDictionary* data = [tilesActions getMaxZoom];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:data];
        } else {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        }
        
        // The sendPluginResult method is thread-safe.
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

- (void)get_tile:(CDVInvokedUrlCommand*)command {
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* pluginResult = nil;
        
        NSDictionary* dict = [command.arguments objectAtIndex:0];
        
        // get zoom_level column and row
        int z = [dict[KEY_Z] intValue];
        int x = [dict[KEY_X] intValue];
        int y = [dict[KEY_Y] intValue];
        if (z && y && x) {
            
            // test is open
            if ([tilesActions isOpen]) {
                // get tiles
                NSDictionary* data = [tilesActions getTile:z columnValue:x rowValue:y];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:data];
            } else {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
            }
        } else {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION];
        }
            
        // The sendPluginResult method is thread-safe.
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

- (void)execute_statement:(CDVInvokedUrlCommand*)command {
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* pluginResult = nil;
        
        NSDictionary* dict = [command.arguments objectAtIndex:0];
        
        // get query and params
        NSString* query = dict[KEY_QUERY];
        NSArray* params = dict[KEY_PARAMS];
        if (query) {
            
            // test is open
            if ([tilesActions isOpen]) {
                // execute request
                NSDictionary* data = [tilesActions executeStatment:query withParams:params];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:data];
            } else {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
            }
        } else {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION];
        }
        
        // The sendPluginResult method is thread-safe.
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];

}

- (void)get_directory_working:(CDVInvokedUrlCommand*)command {
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* pluginResult = nil;
        id<MBTilesAction> actions = nil;
        
        NSDictionary* dict = [command.arguments objectAtIndex:0];
         // get the type and name
        NSString* type = dict[KEY_TYPE];
        if (type) {
            // get directory working of db
            if ([type isEqualToString:@"db"]) {
                actions = [[MBTilesActionsDataBaseImpl alloc] init];
                NSDictionary* data = [actions getDirectoryWorking];
                
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:data];
            // get directory working of file   
            } else if ([type isEqualToString:@"file"]) {
                actions = [[MBTilesActionsFileImpl alloc] init];
                NSDictionary* data = [actions getDirectoryWorking];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:data];
            } else {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION];
            }
        }
    
        // The sendPluginResult method is thread-safe.
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

@end
