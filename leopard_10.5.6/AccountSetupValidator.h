/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class Account, ActivityMonitor, AuthScheme, Connection, NSArray, NSString;

@interface AccountSetupValidator : NSObject
{
    NSArray *_attempts;
    Account *_account;
    Connection *_connection;
    AuthScheme *_preferredAuthScheme;
    ActivityMonitor *_validationActivity;
    NSString *_password;
    BOOL _usedSSL;
    id <AccountSetupValidatorDelegate> _delegate;
}

+ (id)validatorWithAccount:(id)fp8 accountInfo:(id)fp12 delegate:(id)fp16;
- (id)_initWithAccount:(id)fp8 accountInfo:(id)fp12 delegate:(id)fp16;
- (void)dealloc;
- (void)cancel;
- (void)_sendValidatorDidChangeState:(id)fp8;
- (void)_sendValidatorDidFail;
- (void)_sendValidatorDidFinish;
- (void)_updateState:(int)fp8;
- (BOOL)_connectIfNeeded;
- (void)_disconnect;
- (BOOL)_attemptInitialConnection;
- (BOOL)_attemptAuthentication;
- (void)_validate;
- (BOOL)usedSSL;
- (void)setUsedSSL:(BOOL)fp8;
- (id)password;
- (void)setPassword:(id)fp8;
- (id)delegate;
- (void)setDelegate:(id)fp8;
- (id)preferredAuthScheme;
- (void)setPreferredAuthScheme:(id)fp8;
- (id)validationActivity;
- (void)setValidationActivity:(id)fp8;
- (id)connection;
- (void)setConnection:(id)fp8;
- (id)account;
- (void)setAccount:(id)fp8;
- (id)attempts;
- (void)setAttempts:(id)fp8;

@end

