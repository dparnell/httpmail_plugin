//
//  DPAsyncSocket.m
//  httpmail
//
//  Created by Daniel Parnell on Thu May 29 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import "DPAsyncSocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <unistd.h>

@interface DPAsyncSocket (Private)
- (void)notifyDelegateOfConnection;
- (void)dataAvailable:(NSNotification*)dict;

@end;

@implementation DPAsyncSocket

+ (DPAsyncSocket*)newSocketWithHost: (NSString*)aHost andPort: (int)aPort {
    DPAsyncSocket* result = [[DPAsyncSocket new] autorelease];
    
    [result setHost: aHost];
    [result setPort: aPort];
    
    return result;
}

- (id)init {
//    NSLog(@"DPAsyncSocket init");
    
    self = [super init];
    if(self) {
        socketHandle = nil;
        host = nil;
        port = -1;
        delegate = nil;
    }
    
    return self;
}

- (void)dealloc {
//    NSLog(@"DPAsycnSocket dealloc");
    
    [self setDelegate: nil];
    [self close];
    
    [super dealloc];
}

+ (NSString*) niceError:(int)errorCode {
    switch(errorCode) {
    case ENETDOWN:	return @"Network is down";
    case ENETUNREACH:	return @"Network is unreachable";
    case ENETRESET:	return @"Network dropped connection on reset";
    case ECONNABORTED:	return @"Software caused connection abort";
    case ECONNRESET:	return @"Connection reset by peer";
    case ENOBUFS:	return @"No buffer space available";
    case EISCONN:	return @"Socket is already connected";
    case ENOTCONN:	return @"Socket is not connected";
    case ESHUTDOWN:	return @"Can't send after socket shutdown";
    case ETOOMANYREFS:	return @"Too many references: can't splice";
    case ETIMEDOUT:	return @"Operation timed out";
    case ECONNREFUSED:	return @"Connection refused";

    default:
        return [NSString stringWithFormat: @"%d", errorCode];
    }
}

- (NSString*) host {
    return host;
}

- (void) setHost: (NSString*)aHost {
    [aHost retain];
    [host release];

//    NSLog(@"DPASyncSocket setHost: %@", aHost);
    
    host = aHost;
}

- (int) port {
    return port;
}

- (void) setPort: (int)aPort {
//    NSLog(@"DPASyncSocket setPort: %d", aPort);

    port = aPort;
}

- (void)open {
    struct hostent *h;
    struct sockaddr_in remoteAddr;
    
//    NSLog(@"DPASyncSocket open");

    int fHandle = 0;
    
    h = gethostbyname([host cStringUsingEncoding: NSASCIIStringEncoding]);
    if(h==NULL) {
        [NSException raise: SOCKET_ERROR format: @"Could not find host: %@", host];
    }
    
    remoteAddr.sin_family = h->h_addrtype;
    memcpy((char*) &remoteAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    remoteAddr.sin_port = htons(port);
    
    fHandle = socket(AF_INET, SOCK_STREAM, 0);
    if(fHandle<0) {
        fHandle = 0;
        [NSException raise: SOCKET_ERROR format: @"Could not create socket: %@", [DPAsyncSocket niceError: errno]];
    }
    
    if(connect(fHandle, (const struct sockaddr*)&remoteAddr, sizeof(remoteAddr))==0) {
        socketHandle = [[[NSFileHandle alloc] initWithFileDescriptor: fHandle closeOnDealloc: YES] retain];
                
        [[NSNotificationCenter defaultCenter] addObserver: self selector: @selector(dataAvailable:) name: NSFileHandleReadCompletionNotification object: socketHandle];
        [socketHandle readInBackgroundAndNotify];
        
        [self notifyDelegateOfConnection];
    } else {
        [NSException raise: SOCKET_ERROR format: @"Connect to %@ failed: %@", host, [DPAsyncSocket niceError: errno]];
    }
}

- (void)close {
//    NSLog(@"DPASyncSocket close");
    if(socketHandle) {
        [[NSNotificationCenter defaultCenter] removeObserver: self];
        
        [socketHandle closeFile];
        [socketHandle release];
        socketHandle = nil;
    }
}

- (void)writeData:(NSData*)data {
//    NSLog(@"DPASyncSocket writeData");
    
    if(socketHandle) {
//        NSString* temp = [NSString stringWithCString: [data bytes] length: [data length]];
//        NSLog(@"%@", temp);
        
        [socketHandle writeData: data];
    } else {
        [NSException raise: SOCKET_ERROR format: @"The socket is not open"];
    }
}

- (id) delegate {
    return delegate;
}

- (void) setDelegate: (id)aDelegate {
//    [aDelegate retain];
//    [delegate release];
    delegate = aDelegate;
}

- (void)notifyDelegateOfConnection {
//    NSLog(@"DPASyncSocket notifyDelegateOfConnection");
    if(delegate && [delegate respondsToSelector: @selector(socketConnected:)]) {
        [delegate socketConnected: self];
    }
}

- (void)dataAvailable:(NSNotification*)notification {
//    NSLog(@"DPASyncSocket dataAvailable");
    
    NSDictionary* dict = [notification userInfo];
    NSNumber* error = [dict objectForKey: @"NSFileHandleError"];
    NSData* data = [dict objectForKey: NSFileHandleNotificationDataItem];
        
    if(delegate && [delegate respondsToSelector: @selector(socket:hasData:)]) {                        
//        NSLog(@"notifying deletegate of data");
//        NSString* temp = [NSString stringWithCString: [data bytes] length: [data length]];
//        NSLog(@"data = %@", temp);
        
        [delegate socket: self hasData: data];
    } else {
//        NSLog(@"not notifying deletegate of data");
    }
    
    if([data length]) {
        [socketHandle readInBackgroundAndNotify];
    }
    
    if([error intValue]) {
        if(delegate && [delegate respondsToSelector: @selector(socket:hasError:)]) {                        
            [delegate socket: self hasError: [error intValue]];
        }
    }
}

- (BOOL) isOpen {
    return socketHandle!=nil;
}

@end
