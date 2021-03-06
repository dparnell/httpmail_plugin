/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "MailApp.h"

@interface MailApp (ApplescriptComposingPreferences)
- (int)defaultMessageFormat;
- (void)setDefaultMessageFormat:(int)fp8;
- (BOOL)autosaveComposeWindows;
- (void)setAutosaveComposeWindows:(BOOL)fp8;
- (int)spellCheckingBehavior;
- (void)setSpellCheckingBehavior:(int)fp8;
- (BOOL)checkGrammarWithSpelling;
- (void)setCheckGrammarWithSpelling:(BOOL)fp8;
- (BOOL)expandGroupAddresses;
- (void)setExpandGroupAddresses:(BOOL)fp8;
- (BOOL)useAddressCompletion;
- (void)setUseAddressCompletion:(BOOL)fp8;
- (id)ldapServerNamed:(id)fp8;
- (id)ldapServers;
- (void)insertInLdapServers:(id)fp8 atIndex:(unsigned int)fp12;
- (void)insertInLdapServers:(id)fp8;
- (void)removeFromLdapServersAtIndex:(unsigned int)fp8;
- (BOOL)replyInSameFormat;
- (void)setReplyInSameFormat:(BOOL)fp8;
- (BOOL)alwaysCCMyself;
- (void)setAlwaysCCMyself:(BOOL)fp8;
- (BOOL)alwaysBCCMyself;
- (void)setAlwaysBCCMyself:(BOOL)fp8;
- (BOOL)includeOriginalMessage;
- (void)setIncludeOriginalMessage:(BOOL)fp8;
- (BOOL)includeAllOfOriginalMessage;
- (void)setIncludeAllOfOriginalMessage:(BOOL)fp8;
- (BOOL)shouldCheckIntranetDomains;
- (BOOL)signOutgoingMessages;
- (void)setSignOutgoingMessages:(BOOL)fp8;
- (BOOL)encryptOutgoingMessages;
- (void)setEncryptOutgoingMessages:(BOOL)fp8;
- (BOOL)inlineSpellCheckingEnabled;
- (void)setInlineSpellCheckingEnabled:(BOOL)fp8;
- (id)intranetDomains;
- (void)setShouldCheckIntranetDomains:(BOOL)fp8 withString:(id)fp12;
@end

