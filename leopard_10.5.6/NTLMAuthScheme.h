/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import <Message/AuthScheme.h>

@interface NTLMAuthScheme : AuthScheme
{
}

+ (void)initialize;
- (Class)authenticatorClassForAccount:(id)fp8;
- (BOOL)requiresDomain;
- (id)name;
- (id)humanReadableName;
- (BOOL)sendsPlainTextPasswords;
- (BOOL)hasEncryption;
- (unsigned int)securityLevel;

@end

