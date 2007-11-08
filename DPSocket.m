//
//  DPSocket.m
//  httpmail
//
//  Created by Daniel Parnell on Tue Sep 24 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "DPSocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/errno.h>
#include <unistd.h>

@implementation DPSocket

static NSString* SOCKET_ERROR = @"Socket Error";

+ newWithUrl:(NSURL*)url {
    return [[[DPSocket alloc] initWithUrl: url] autorelease];
}

+ newWithSocket:(int)handle {
    DPSocket* result = [DPSocket new];
    result->fReadFile = fdopen(handle, "r");
    result->fWriteFile = fdopen(handle, "w");
    result->fHandle = 0;
    result->fHost = NULL;
    result->fPort = 0;
    result->fTimeout = 30;
    
    return [result autorelease];
}

- initWithUrl:(NSURL*)url {
    self = [super init];
    
    if(self) {
        fHandle = 0;
        fReadFile = NULL;
        fWriteFile = NULL;
        fHost = [[url host] retain];
        fPort = [[url port] intValue];
        if(fPort==0)
            fPort = 80;
        fTimeout = 30;
    }
    
    return self;
}

- initWithPort:(int)port andHost:(NSString*)host {
    self = [super init];
    
    if(self) {
        fHandle = 0;
        fReadFile = NULL;
        fWriteFile = NULL;
        fPort = port;
        fHost = [host retain];
        fTimeout = 30;
    }
    
    return self;
}

- init {
    self = [super init];
    
    if(self) {
        fHandle = 0;
        fReadFile = NULL;
        fWriteFile = NULL;
        fPort = 0;
        fHost = NULL;
        fTimeout = 30;
    }
    
    return self;
}

-(void)dealloc {     
    [fHost release];
    
    [super dealloc];
}

- (void) setUrl: (NSURL*)url {
    [self close];
    
    fHandle = 0;
    fReadFile = NULL;
    fWriteFile = NULL;
    [fHost release];
    fHost = [[url host] retain];
    fPort = [[url port] intValue];
    if(fPort==0)
        fPort = 80;
}


- (NSString*) niceError:(int)err {
    switch(err) {
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
    case EAGAIN:        return @"Socket timeout";
    
    default:
        return [NSString stringWithFormat: @"%d", err];
    }
}

-(BOOL)open {
    struct hostent *h;
    struct sockaddr_in remoteAddr;
    struct timeval tv;
    int ret;
    
    fHandle = 0;
    
    h = gethostbyname([fHost cStringUsingEncoding: NSUTF8StringEncoding]);
    if(h==NULL) {
        [NSException raise: SOCKET_ERROR format: @"Could not find host: %@", fHost];
    }
    
    remoteAddr.sin_family = h->h_addrtype;
    memcpy((char*) &remoteAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    remoteAddr.sin_port = htons(fPort);
    
    fHandle = socket(AF_INET, SOCK_STREAM, 0);
    if(fHandle<0) {
        fHandle = 0;
        [NSException raise: SOCKET_ERROR format: @"Could not create socket: %@", [self niceError: errno]];
    }
    
    tv.tv_sec = fTimeout;
    tv.tv_usec = 0;
    
    ret = setsockopt (fHandle, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv) ;
    if(ret!=0) {
        [NSException raise: SOCKET_ERROR format: @"Could not set socket receive timeout: %@", [self niceError: errno]];
    }
    
    ret = setsockopt (fHandle, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof tv) ;
    if(ret!=0) {
        [NSException raise: SOCKET_ERROR format: @"Could not set socket send timeout: %@", [self niceError: errno]];
    }
    
    if(connect(fHandle, (const struct sockaddr*)&remoteAddr, sizeof(remoteAddr))==0) {
        fReadFile = fdopen(fHandle, "r");
        fWriteFile = fdopen(fHandle, "w");
        fHandle = 0;
        return YES;
    }
    
    fHandle = 0;
    
    [NSException raise: SOCKET_ERROR format: @"Connect to %@ failed: %@", fHost, [self niceError: errno]];
    
    return NO; // stops the warning
}

-(BOOL)close {
//    NSLog(@"DPSocket close");
    
    if(fHandle!=0)
        if(close(fHandle)==0) {
            fHandle = 0;
        } else {
            return NO;
        }

    if(fReadFile) {
        if((fclose(fReadFile)==0) && (fclose(fWriteFile)==0)) {
            fReadFile = NULL;
            fWriteFile = NULL;
        } else {
            return NO;
        }
    }
    
    return YES;
}

-(int)read:(int)count into:(char*)buffer {
    int result = fread(buffer, 1, count, fReadFile);
    
    if(result==0 && ferror(fReadFile)) {
        [NSException raise: SOCKET_ERROR format: @"Read error: %@", [self niceError: errno]];
    }
    
    return result;
}

-(int)write:(int)count from:(char*)buffer {
    if(fWriteFile==NULL) {
        [NSException raise: SOCKET_ERROR format: @"Socket write error: attempt to write to a closed socket"];
    }
    
    if(count && buffer) {
        int result = fwrite(buffer, 1, count, fWriteFile);
        
        if(result==0 && ferror(fWriteFile)) {
            [NSException raise: SOCKET_ERROR format: @"Write error: %@", [self niceError: errno]];
        }
        
        fflush(fWriteFile);
        
        return result;
    } else {
        [NSException raise: SOCKET_ERROR format: @"Socket write error: invalid buffer"];
        return 0;
    }
}

-(BOOL)hasData {
    return YES;
}

-(int)writeString:(NSString*)string {
    int L = [string length];
    char* data = (char*)[string cStringUsingEncoding: NSUTF8StringEncoding];
    
    if(L>0) {
        return [self write: L from: data];
    } else {
        [NSException raise: SOCKET_ERROR format: @"Socket write error: invalid string"];
        return 0;
    }
}

-(char) nextChar {
    return fgetc(fReadFile);
}

-(NSString*)readLine {
    if(fReadFile==NULL)
        [NSException raise: SOCKET_ERROR format: @"Socket read error: attempt to read from a closed socket"];
        
    char buffer[1024];
    char* line = fgets(&buffer[0], sizeof(buffer), fReadFile);

    if(line==NULL && ferror(fReadFile)) {
        [NSException raise: SOCKET_ERROR format: @"Read error: %@ - %@", fHost, [self niceError: errno]];
    }
    
    if(line) {
        NSString* s = [NSString stringWithCString: line];
        
        if([s isEqualToString: @"\r\n"]) {
            return @"";
        }
            
        return [s stringByTrimmingCharactersInSet: [NSCharacterSet whitespaceAndNewlineCharacterSet]];
    }
    
    return @"";
}

- (int)writeData:(NSData*)data {
    return [self write: [data length] from: (char*)[data bytes]];
}

- (int)port {
    return fPort;
}

- (void)setPort:(int)port {
    fPort = port;
}

- (BOOL)listenWithBacklog:(int)backlog {
    struct sockaddr_in saddr;
    int ret;
    
    [self close];
    
    fHandle = socket(AF_INET, SOCK_STREAM, 0);
    if(fHandle<0) {
        [NSException raise: SOCKET_ERROR format: @"Could not create socket: %d", errno];
    }
 
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(fPort);   
    
    ret = bind(fHandle, (const struct sockaddr*)&saddr, sizeof(saddr));
    if(ret!=0) {
        [NSException raise: SOCKET_ERROR format: @"Bind failed: %d", errno];
    }
    
    if(fPort==0) {
        unsigned int s = sizeof(saddr);
        ret = getsockname(fHandle, (struct sockaddr*)&saddr, &s);
        
        if(ret!=0) {
            [NSException raise: SOCKET_ERROR format: @"getsockname failed: %d", errno];
        }
        
        fPort = ntohs(saddr.sin_port);
    }
    
    ret = listen(fHandle, backlog);
    if(ret!=0) {
        [NSException raise: SOCKET_ERROR format: @"Listen failed: %d", errno];
    }

    return YES;
}

- (BOOL)listen {
    return [self listenWithBacklog: 5];
}

- (DPSocket*)accept {
    int ret;

    ret = accept(fHandle, NULL, NULL);
    if(ret<0) {
        [NSException raise: SOCKET_ERROR format: @"Accept failed: %d", errno];
    }
    
    return [DPSocket newWithSocket: ret];
}

- (void) setSocketTimeout:(int)timeout {
    fTimeout = timeout;
}

- (int) socketTimeout {
    return fTimeout;
}

@end
