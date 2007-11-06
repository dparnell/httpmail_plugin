//
//  DPAsyncSocket.h
//  httpmail
//
//  Created by Daniel Parnell on Thu May 29 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>

#define SOCKET_ERROR @"Socket Error"

@class DPAsyncSocket;

@interface NSObject (DPAsyncSocketDelegaet)

- (void)socketConnected: (DPAsyncSocket*)aSocket;
- (void)socket: (DPAsyncSocket*)aSocket hasData: (NSData*)data;
- (void)socket: (DPAsyncSocket*)aSocket hasError: (int)errorCode;

@end

@interface DPAsyncSocket : NSObject {
    NSFileHandle*	socketHandle;

    NSString*		host;
    int			port;

    id			delegate;
}

+ (DPAsyncSocket*)newSocketWithHost: (NSString*)aHost andPort: (int)aPort;

+ (NSString*) niceError:(int)errorCode;

- (NSString*) host;
- (void) setHost: (NSString*)aHost;
- (int) port;
- (void) setPort: (int)aPort;

- (void)open;
- (void)close;

- (void)writeData:(NSData*)data;

- (id) delegate;
- (void) setDelegate: (id)aDelegate;

- (BOOL) isOpen;

@end
