/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import <Message/IMAPSingleClientOperation.h>

@class NSString, SASLAuthenticator;

@interface IMAPClientAuthenticateOperation : IMAPSingleClientOperation
{
    NSString *_authenticateType;
    SASLAuthenticator *_authenticator;
}

- (void)dealloc;
- (id)initWithAuthenticator:(id)fp8;
- (const char *)commandTypeCString;
- (BOOL)handlesAllUntaggedResponses;
- (id)createCommandDataForLiteralPlus:(BOOL)fp8;
- (BOOL)executeOnConnection:(id)fp8;
- (id)authenticator;
- (void)setAuthenticator:(id)fp8;
- (id)authenticateType;
- (void)setAuthenticateType:(id)fp8;

@end

