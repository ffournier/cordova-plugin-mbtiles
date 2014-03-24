//
//  MBTilesConstant.m
//  TestCordova2
//
//  Created by florian on 19/03/14.
//
//

#import "MBTilesConstant.h"

@implementation MBTilesConstant

NSString * const KEY_TYPE = @"type";
NSString * const KEY_NAME = @"name";
NSString * const KEY_Z = @"z";
NSString * const KEY_Y = @"y";
NSString * const KEY_X = @"x";
NSString * const KEY_VERSION = @"version";
NSString * const KEY_FORMAT = @"format";
NSString * const KEY_MIN_ZOOM = @"min_zoom";
NSString * const KEY_MAX_ZOOM = @"max_zoom";
NSString * const KEY_TILE_DATA = @"tile_data";
NSString * const KEY_QUERY = @"query";
NSString * const KEY_PARAMS = @"params";
NSString * const KEY_EXECUTE_STATMENT = @"result_execute";

+ (NSString*)base64forData:(NSData*)theData {
    
    const uint8_t* input = (const uint8_t*)[theData bytes];
    NSInteger length = [theData length];
    
    static char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    
    NSMutableData* data = [NSMutableData dataWithLength:((length + 2) / 3) * 4];
    uint8_t* output = (uint8_t*)data.mutableBytes;
    
    NSInteger i;
    for (i=0; i < length; i += 3) {
        NSInteger value = 0;
        NSInteger j;
        for (j = i; j < (i + 3); j++) {
            value <<= 8;
            
            if (j < length) {
                value |= (0xFF & input[j]);
            }
        }
        
        NSInteger theIndex = (i / 3) * 4;
        output[theIndex + 0] =                    table[(value >> 18) & 0x3F];
        output[theIndex + 1] =                    table[(value >> 12) & 0x3F];
        output[theIndex + 2] = (i + 1) < length ? table[(value >> 6)  & 0x3F] : '=';
        output[theIndex + 3] = (i + 2) < length ? table[(value >> 0)  & 0x3F] : '=';
    }
    
    return [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
}

@end
