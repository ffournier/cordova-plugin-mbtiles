//
//  MBTilesConstant.h
//  TestCordova2
//
//  Created by florian on 19/03/14.
//
//

#import <Foundation/Foundation.h>

@interface MBTilesConstant : NSObject

    extern NSString * const KEY_TYPE;
    extern NSString * const KEY_NAME;
    extern NSString * const KEY_Z;
    extern NSString * const KEY_Y;
    extern NSString * const KEY_X;
    extern NSString * const KEY_VERSION;
    extern NSString * const KEY_FORMAT;
    extern NSString * const KEY_MIN_ZOOM;
    extern NSString * const KEY_MAX_ZOOM;
    extern NSString * const KEY_TILE_DATA;

+ (NSString*)base64forData:(NSData*)theData;

@end
