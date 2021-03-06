/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "Connection.h"

@class NSMutableArray, NSMutableData, NSString;

@interface SMTPConnection : Connection
{
    unsigned int _lastResponseCode:31;
    unsigned int _hideLoggedData:1;
    id _lastResponse;
    NSMutableArray *_serviceExtensions;
    NSMutableData *_mdata;
    NSString *_domainName;
    int _originalSocketTimeout;
    int _lastCommandTimestamp;
}

+ (void)initialize;
- (BOOL)authenticateUsingAccount:(id)fp8;
- (BOOL)authenticateUsingAccount:(id)fp8 authenticator:(id)fp12;
- (id)authenticationMechanisms;
- (BOOL)connectUsingAccount:(id)fp8;
- (void)dealloc;
- (id)domainName;
- (void)finalize;
- (id)init;
- (id)lastResponse;
- (unsigned int)lastResponseCode;
- (int)mailFrom:(id)fp8;
- (unsigned long long)maximumMessageBytes;
- (int)noop;
- (int)quit;
- (int)rcptTo:(id)fp8;
- (int)sendData:(id)fp8;
- (void)setDomainName:(id)fp8;
- (int)state;
- (long)timeLastCommandWasSent;

@end

