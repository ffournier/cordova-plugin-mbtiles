//
//  MBTilesAction.h
//  TestCordova2
//
//  Created by florian on 19/03/14.
//
//

#import <Foundation/Foundation.h>

@protocol MBTilesAction <NSObject>

@required

- (void)open:(NSString*) path;
- (BOOL)isOpen;
- (void)close;
- (NSDictionary*)getMetadata;
- (NSDictionary*)getMinZoom;
- (NSDictionary*)getMaxZoom;
- (NSDictionary*)getTile:(int) zoom_level columnValue:(int) column rowValue:(int) row;

@end


