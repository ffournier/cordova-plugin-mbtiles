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

- (void)init:(CDVInvokedUrlCommand*)command {
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* pluginResult = nil;
        
        NSDictionary* dict = [command.arguments objectAtIndex:0];
        // get the type and name
        NSString* type = dict[KEY_TYPE];
        NSString* url = nil;
        if ([dict objectForKey:KEY_URL] != nil) {
            url = dict[KEY_URL];
        }
        
        if (tilesActions != nil) {
            [tilesActions close];
        }
        
        tilesActions = nil;
        
        if (type) {
            // init db with name
            if ([type isEqualToString:@"db"]) {
                tilesActions = [[MBTilesActionsDataBaseImpl alloc] init];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
            }
            // init file name
            else if ([type isEqualToString:@"file"]) {
                tilesActions = [[MBTilesActionsFileImpl alloc] init];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
            }
            // init cdv filename
            else if ([type isEqualToString:@"cdvfile"]) {
                CDVFile* filePlugin = [self.commandDelegate getCommandInstance:@"File"];
                if (url != nil) {
                    tilesActions = [[MBTilesActionsCDVFileImpl alloc] initWithCDVFile:filePlugin withUrl:url];
                } else {
                    tilesActions = [[MBTilesActionsCDVFileImpl alloc] initWithCDVFile:filePlugin];
                }
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
            }
            else {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_IO_EXCEPTION];
            }
        }
        
        // The sendPluginResult method is thread-safe.
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}


- (void)open:(CDVInvokedUrlCommand*)command {
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* pluginResult = nil;
        
        
        if (tilesActions != nil) {
            NSDictionary* dict = [command.arguments objectAtIndex:0];
            NSString* name = dict[KEY_NAME];
            // get name
            if (name) {
                [tilesActions open:name];
                if ([tilesActions isOpen]) {
                    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
                } else {
                    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
                }
            } else {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_IO_EXCEPTION];
            }
        } else {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
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
                NSDictionary* data = [tilesActions executeStatement:query withParams:params];
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
        
        if (tilesActions != nil) {
            NSDictionary* data = [tilesActions getDirectoryWorking];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:data];
        } else {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        }
    
        // The sendPluginResult method is thread-safe.
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }];
}

@end
