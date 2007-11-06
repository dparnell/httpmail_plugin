//
//  DPAsyncHttp.h
//  httpmail
//
//  Created by Daniel Parnell on Mon May 05 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DPAsyncSocket.h"

#define HTTP_CONTINUE			100
#define HTTP_SWITCHING_PROTOCOLS	101
#define HTTP_OK				200
#define HTTP_CREATED			201
#define HTTP_ACCEPTED			202
#define HTTP_NON_AUTHORITATIVE		203
#define HTTP_NO_CONTENT			204
#define HTTP_RESET_CONTENT		205
#define HTTP_PARTIAL_CONTENT		206
#define HTTP_MULTIPLE_CHOICES		300
#define HTTP_MOVED_PERMANENTLY		301
#define HTTP_MOVED_TEMPORARILY		302
#define HTTP_SEE_OTHER			303
#define HTTP_NOT_MODIFIED		304
#define HTTP_USE_PROXY			305
#define HTTP_BAD_REQUEST		400
#define HTTP_UNAUTHORIZED		401
#define HTTP_PAYMENT_REQUIRED		402
#define HTTP_FORBIDDEN			403
#define HTTP_NOT_FOUND			404
#define HTTP_METHOD_NOT_ALLOWED		405
#define HTTP_NOT_ACCEPTABLE		406
#define HTTP_PROXY_AUTH_REQUIRED	407
#define HTTP_REQUEST_TIMEOUT		408
#define HTTP_CONFLICT			409
#define HTTP_GONE			410
#define HTTP_LENGTH_REQUIRED		411
#define HTTP_PRECONDITION_FAILED	412
#define HTTP_REQUEST_TOO_LARGE		413
#define HTTP_REQUEST_URI_TOO_LARGE	414
#define HTTP_UNSUPPORTED_MEDIA_TYPE	415
#define HTTP_INTERNAL_SERVER_ERROR	500
#define HTTP_NOT_IMPLEMENTED		501
#define HTTP_BAD_GATEWAY		502
#define HTTP_SERVICE_UNAVAILABLE	503
#define HTTP_GATEWAY_TIMEOUT		504
#define HTTP_VERSION_NOT_SUPPORTED	505

#define MAX_LINE_LENGTH 1024

@class DPAsyncHttp;

@interface NSObject (DPAsyncHttpDelegate)
- (void)downloadFinished:(DPAsyncHttp*)sender;
- (void)downloadFailed:(DPAsyncHttp*)sender dueToError:(CFSocketError)error;
- (void)downloadProgress:(int)bytes of:(int)total forAsyncHttp: (DPAsyncHttp*)sender;
- (void)downloadStopped:(DPAsyncHttp*)sender;

@end

@interface DPAsyncHttp : NSObject {
@private
    NSURL*			fUrl;
    NSMutableDictionary*	fHeaders;
    NSMutableDictionary*	fCookies;
    NSString*			fMethod;
    int				fResponseCode;
    NSString*			fResponseString;
    NSMutableDictionary*	fResponseHeaders;
    bool			fFollowRedirections;
    NSData*			fRequestContent;
    NSString*			fRequestContentType;
    
    NSURL*			fProxy;
    NSString*			fProxyUsername;
    NSString*			fProxyPassword;
    NSString*			fProxyRealm;
    
    NSString*			fUsername;
    NSString*			fPassword;
    
    NSString*			nonce;
    NSString*			opaque;
    NSString*			realm;
    NSString*			authMethod;
    NSString*			qop;
    NSMutableDictionary*	nonce_counts;
    
    BOOL			shouldClose;
    id				delegate;
    NSMutableData*		responseData;
    unsigned int		responseSize;
    int				state;
    int				linePos;
    char			lineBuf[MAX_LINE_LENGTH];
    BOOL			proxyAuthSent;
    BOOL			passwordSent;
    int				socketTimeout;
    
    BOOL			fStopped;
    DPAsyncSocket*              socket;
@public
}

+ (id)newWithURL:(NSURL*)url;
- (id)initWithURL:(NSURL*)url;

- (void)setURL:(NSURL*)url;
- (NSURL*)URL;

- (void)setMethod:(NSString*)method;
- (NSString*)method;

- (void)setHeaderValue:(NSString*)data forKey:(NSString*)key;
- (NSString*)headerValueForKey:(NSString*)key;
- (void)clearHeaders;
- (NSDictionary*)headers;
- (void)removeHeaderForKey:(NSString*)key;

- (void)setCookieValue:(NSString*)data forKey:(NSString*)key;
- (NSString*)cookieValueForKey:(NSString*)key;
- (void)clearCookies;
- (NSDictionary*)cookies;
- (void)setCookies:(NSDictionary*)cookies;
- (void)removeCookieForKey:(NSString*)key;

- (int)responseCode;
- (NSString*)responseString;
- (NSString*)responseHeaderForKey:(NSString*)key;
- (NSDictionary*)responseHeaders;

- (void)setFollowRedirections:(bool)follow;
- (bool)followRedirections;

- (NSData*)requestContent;
- (void)setRequestContent:(NSData*)data;
- (NSString*)requestContentType;
- (void)setRequestContentType:(NSString*)type;
- (void)setRequestContentAsString:(NSString*)string;

- (NSURL*)proxy;
- (void)setProxy:(NSURL*)url;
- (void)setProxyUsername:(NSString*)username;
- (NSString*)proxyUsername;
- (void)setProxyPassword:(NSString*)password;
- (NSString*)proxyPassword;

- (void)setUsername:(NSString*)username;
- (NSString*)username;
- (void)setPassword:(NSString*)password;
- (NSString*)password;

- (void)setDelegate:(id)ADelegate;
- (void)asyncGet;
- (NSData*)responseData;

- (NSData*)get;

- (void) stop;
- (BOOL) stopped;
- (void) setSocketTimeout:(int)timeout;
- (int) socketTimeout;

- (void)close;

@end
