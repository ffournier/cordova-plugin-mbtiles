//
//  MBTilesActionsCDVFileImpl.m
//
//  Created on 20/03/14.
//
//

#import "MBTilesActionsCDVFileImpl.h"


@implementation MBTilesActionsCDVFileImpl


- (id)init {
    @throw [NSException exceptionWithName:NSInternalInconsistencyException
                                   reason:@"-init is not a valid initializer for the class MBTilesActionsCDVFileImpl"
                                 userInfo:nil];
    return nil;
}

/**
 * init the class
 */
- (id) initWithCDVFile:(CDVFile*) filePlugin {
    return [self initWithCDVFile:filePlugin withUrl:@"cdvfile://localhost/persistent/tiles/"];
}

/**
 * init the class
 */
- (id) initWithCDVFile:(CDVFile*) filePlugin withUrl:(NSString*) cdvfileURL {
    self = [super init];
    
    // Get a CDVFilesystem URL object from a URL string
    CDVFilesystemURL* url = [CDVFilesystemURL fileSystemURLWithString:cdvfileURL];
    // Get a path for the URL object, or nil if it cannot be mapped to a file
    self.directory = [filePlugin filesystemPathForURL:url];
    
    return self;
}

- (NSString*) getFullDirectory {
    return self.directory;
}



@end
