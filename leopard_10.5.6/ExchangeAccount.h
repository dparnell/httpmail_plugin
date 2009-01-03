/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import <Message/IMAPAccount.h>

@interface ExchangeAccount : IMAPAccount
{
}

+ (id)accountTypeString;
+ (BOOL)usingActiveDirectory;
+ (id)outlookWebAccessServer;
+ (void)setOutlookWebAccessServer:(id)fp8;
+ (id)exchangeServer;
+ (void)setExchangeServer:(id)fp8;
+ (id)activeDirectoryUser;
+ (void)setActiveDirectoryUser:(id)fp8;
+ (id)activeDirectoryPassword;
+ (void)setActiveDirectoryPassword:(id)fp8;
+ (id)activeDirectoryFullName;
+ (id)activeDirectoryEmailAddress;
- (Class)connectionClass;
- (BOOL)_syncOnly_defaultValueForShouldStoreJunkOnServer;
- (void)updateFromSyncedDictionary:(id)fp8;
- (BOOL)storeDraftsOnServer;
- (BOOL)storeSentMessagesOnServer;
- (BOOL)storeJunkOnServer;
- (id)_defaultSpecialMailboxNameForType:(int)fp8;
- (void)filterMailboxList:(id)fp8 forMailbox:(id)fp12 options:(int)fp16;
- (id)_nonMailboxChildrenOfMailboxWithPath:(id)fp8 iisServer:(id)fp12;
- (void)_filterMailboxList:(id)fp8 forMailboxWithPath:(id)fp12 iisServer:(id)fp16;
- (id)additionalHeaderFields;
- (id)hostname;
- (void)setHostname:(id)fp8;
- (id)username;
- (void)setUsername:(id)fp8;
- (id)passwordFromStoredUserInfo;
- (id)passwordFromKeychain;
- (void)setPassword:(id)fp8;
- (void)setPasswordInKeychain:(id)fp8;
- (void)_removePasswordInKeychain;
- (id)defaultsDictionary;
- (void)handleOpenMailboxError:(id)fp8;

@end

