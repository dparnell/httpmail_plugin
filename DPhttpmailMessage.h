//
//  DPhttpmailMessage.h
//  httpmail
//
//  Created by Daniel Parnell on Thu Oct 10 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface DPhttpmailMessage : NSObject {
    NSURL*	url;
    int		size;
    NSString*	subject;
    NSString*	from;
    NSString*	to;
    BOOL	read;
    NSDate*	date;
    NSString*	folder;
}

- initWithString:(NSString*)string andFolder:(NSString*)folderUrl;
- (NSURL*)url;
- (int)size;
- (NSString*)subject;
- (NSString*)from;
- (BOOL)read;
- (NSString*)to;
- (NSDate*)date;
- (NSString*)uniqueID;
- (NSString*)folder;

@end
