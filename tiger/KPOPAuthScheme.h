/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import <Message/AuthScheme.h>

@interface KPOPAuthScheme : AuthScheme
{
}

- (Class)authenticatorClassForAccount:(id)fp8;
- (BOOL)canAuthenticateAccount:(id)fp8 connection:(id)fp12;
- (Class)connectionClassForAccount:(id)fp8;
- (unsigned int)defaultPortForAccount:(id)fp8;
- (BOOL)hasEncryption;
- (id)humanReadableName;
- (id)name;
- (BOOL)requiresPassword;
- (BOOL)supportsAccountType:(id)fp8;

@end

