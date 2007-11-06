//
//  DPSocket.h
//  httpmail
//
//  Created by Daniel Parnell on Tue Sep 24 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DPSocket : NSObject {
@private
@protected
    int 	fHandle;
    FILE*	fReadFile;
    FILE*	fWriteFile;
    int 	fPort;
    NSString*	fHost;
    int         fTimeout;
@public
}

+ newWithUrl:(NSURL*)url;
- initWithUrl:(NSURL*)url;
- initWithPort:(int)port andHost:(NSString*)host;

- (void) setUrl: (NSURL*)url;

- (BOOL)open;
- (BOOL)close;
- (int)read:(int)count into:(char*)buffer;
- (int)write:(int)count from:(char*)buffer;
- (BOOL)hasData;

- (int)writeString:(NSString*)string;
- (NSString*)readLine;

- (int)writeData:(NSData*)data;

- (int)port;
- (void)setPort:(int)port;

- (BOOL)listenWithBacklog:(int)backlog;
- (BOOL)listen;
- (DPSocket*)accept;

- (void) setSocketTimeout:(int)timeout;
- (int) socketTimeout;

@end
