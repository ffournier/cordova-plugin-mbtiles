//
//  MBTilesConstant.h
//
//  Created on 19/03/14.
//
//

#import <Foundation/Foundation.h>

/**
* Constant
*/
@interface MBTilesConstant : NSObject

    // declaration ok key
    extern NSString * const KEY_TYPE;
    extern NSString * const KEY_TYPEPATH;
    extern NSString * const KEY_URL;
    extern NSString * const KEY_NAME;
    extern NSString * const KEY_PATH;
    extern NSString * const KEY_Z;
    extern NSString * const KEY_Y;
    extern NSString * const KEY_X;
    extern NSString * const KEY_VERSION;
    extern NSString * const KEY_FORMAT;
    extern NSString * const KEY_MIN_ZOOM;
    extern NSString * const KEY_MAX_ZOOM;
    extern NSString * const KEY_TILE_DATA;
    extern NSString * const KEY_QUERY;
    extern NSString * const KEY_PARAMS;
    extern NSString * const KEY_EXECUTE_STATEMENT;
    extern NSString * const KEY_DIRECTORY_WORKING;

    extern NSString * const OPEN_TYPE_PATH_CDVFILE;
    extern NSString * const OPEN_TYPE_PATH_FULL;

/**
 * transform data in string base 64
 *
 * @param theData the data to transform
 * @return string in base 64
 */
+ (NSString*)base64forData:(NSData*)theData;

@end
