//
//  DPhttpmailMessage.m
//  httpmail
//
//  Created by Daniel Parnell on Thu Oct 10 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "DPhttpmailMessage.h"


@implementation DPhttpmailMessage

- (NSString*)stringBetween: (NSString*)start and: (NSString*)finish inString: (NSString*)string {
    NSRange r1,r2;
    
    r1 = [string rangeOfString: start];
    if(r1.location!=NSNotFound) {
        r2 = [string rangeOfString: finish];
        
        if(r2.location!=NSNotFound) {
            NSRange r;
        
            r.location = r1.location+r1.length;
            r.length = r2.location - r.location;
            
            return [string substringWithRange: r];
        }
    }
    
    return NULL;
}

- initWithString:(NSString*)string andFolder:(NSString*)folderUrl {
    self = [super init];
    
    if(self) {
        folder = [folderUrl retain];
        
        url = [[NSURL URLWithString: [self stringBetween: @"<D:href>" and: @"</D:href>" inString: string]] retain];
        read = [[self stringBetween: @"<hm:read>" and: @"</hm:read>" inString: string] isEqualToString: @"1"];
        from = [[self stringBetween: @"<m:from>" and: @"</m:from>" inString: string] retain];
        to = [[self stringBetween: @"<m:to>" and: @"</m:to>" inString: string] retain];
        subject = [[self stringBetween: @"<m:subject>" and: @"</m:subject>" inString: string] retain];
        size = [[self stringBetween: @"<D:getcontentlength>" and: @"</D:getcontentlength>" inString: string] intValue];
        date = [[NSDate dateWithString: [self stringBetween: @"<m:date>" and: @"</m:date>" inString: string]] retain];
    }
    
    return self;
}

- (void) dealloc {
    [folder release];
    [url release];
    [subject release];
    [from release];
    [to release];
    [date release];
    
    [super dealloc];
}

- (NSURL*)url {
    return url;
}

- (int)size {
    return size;
}

- (NSString*)subject {
    return subject;
}

- (NSString*)from {
    return from;
}

- (BOOL)read {
    return read;
}

- (NSString*)to {
    return to;
}

- (NSDate*)date {
    return date;
}

- (NSString*)uniqueID {
    return [[url absoluteString] lastPathComponent];
}

- (NSString*)folder {
    return folder;
}

@end
