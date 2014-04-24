//
//  MBTilesAction.h
//
//  Created on 19/03/14.
//
//

#import <Foundation/Foundation.h>

@protocol MBTilesAction <NSObject>

@required

/** 
 * open database with given parameters
 *
 * @param name the name of the file to open
 */
- (void)open:(NSString*) name;

/** 
 * test if the file was opened 
 *
 * @return YES or NO
 */
- (BOOL)isOpen;

/** 
 * close the file
 */
- (void)close;

/** 
 * get the metadata of the file
 *
 * @return a dictionnary which contains the metadata
 */
- (NSDictionary*)getMetadata;

/** 
 * get the min zoom of the file
 *
 * @return a dictionnary which contains the min zoom
 */
- (NSDictionary*)getMinZoom;

/** 
 * get the max zoom of the file
 *
 * @return a dictionnary wich contains the max zoom
 */
- (NSDictionary*)getMaxZoom;

/** 
 * get tiles with given parameters
 *
 * @param zoom_level the zoom level (z)
 * @param column the column (x)
*  @param row the row (y)
 * @return a dictionnary which contains the tiles associate in base64
 */
- (NSDictionary*)getTile:(int) zoom_level columnValue:(int) column rowValue:(int) row;

/** 
 * execute the given query
 *
 * @param query the query to execute
 * @param params parameters needed
 * @return a dictionnary which contains all object returned by the query
 */
- (NSDictionary*)executeStatement:(NSString*) query withParams:(NSArray*) params;

/**
* return the directory of working
* @return <code>JSONObject</code>
*/
- (NSDictionary*) getDirectoryWorking;


@end


