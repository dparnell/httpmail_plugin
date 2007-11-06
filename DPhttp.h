//
//  DPhttp.h
//  httpmail
//
//  Created by Daniel Parnell on Tue Sep 24 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef USE_APPLE_HTTP
#else
#import "DPSocket.h"
#endif

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

@interface DPhttp : NSObject {
@protected
#ifdef USE_APPLE_HTTP
    NSMutableURLRequest*        fUrlRequest;
    NSHTTPURLResponse*          fResponse;
    bool                        done;
    NSMutableData*              data;
#else
    NSURL*			fUrl;
    NSMutableDictionary*	fHeaders;
    NSMutableDictionary*        fCookies;
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
        
    NSString*			nonce;
    NSString*			opaque;
    NSString*			realm;
    NSString*			authMethod;
    NSString*			qop;
    NSMutableDictionary*	nonce_counts;
    BOOL                        stopped;
#endif

    NSString*			fUsername;
    NSString*			fPassword;

    int                         socketTimeout;
    NSArray*                    fHeaderOrder;
@public
}
+ (id)newWithURL:(NSURL*)url;
- (id)initWithURL:(NSURL*)url;

- (void)setURL:(NSURL*)url;
- (NSURL*)URL;

- (void)setMethod:(NSString*)method;
- (NSString*)method;

- (NSData*)get;

- (void)stop;
- (BOOL)stopped;

- (void)setSocketTimeout:(int)timeout;
- (int)socketTimeout;

- (void)setHeaderValue:(NSString*)data forKey:(NSString*)key;
- (NSString*)headerValueForKey:(NSString*)key;
- (void)clearHeaders;
- (NSDictionary*)headers;
- (void)removeHeaderForKey:(NSString*)key;

- (void)setHeaderOrder:(NSArray*)order;
- (NSArray*)headerOrder;

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
@end
