//
//  io.h
//  httpmail
//
//  Created by Daniel Parnell on Sun Dec 08 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <stdio.h>

@interface IO : NSObject {
    FILE*	fHandle;
}

+ (IO*)stdio;
+ (IO*)newWithHandle: (FILE*)aHandle;
+ (IO*)newWithFileName: (NSString*)aFileName;

- (IO*)initWithHandle: (FILE*)aHandle;
- (void)write:(NSString*)string;
- (NSString*)readln;
- (void)close;
- (void)flush;
- (void)writeData:(NSData*)data;

@end
