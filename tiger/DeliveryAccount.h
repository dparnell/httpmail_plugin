/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "Account.h"

@interface DeliveryAccount : Account
{
}

+ (void)_postDeliveryAccountsHaveChanged;
+ (id)accountWithHostname:(id)fp8 username:(id)fp12;
+ (id)accountWithHostname:(id)fp8 username:(id)fp12 lookForExistingAccounts:(BOOL)fp16;
+ (id)accountWithIdentifier:(id)fp8;
+ (id)accountWithUniqueId:(id)fp8;
+ (void)addDeliveryAccount:(id)fp8;
+ (id)deliveryAccounts;
+ (id)existingAccountWithHostname:(id)fp8 username:(id)fp12;
+ (id)newDefaultInstance;
+ (void)removeDeliveryAccount:(id)fp8;
+ (void)saveAccountInfoToDefaults;
+ (void)setDeliveryAccounts:(id)fp8;
- (Class)deliveryClass;
- (id)identifier;
- (unsigned long long)maximumMessageBytes;
- (void)setMaximumMessageBytes:(unsigned long long)fp8;
- (void)setShouldUseAuthentication:(BOOL)fp8;
- (BOOL)shouldUseAuthentication;
- (void)updateFromSyncedDictionary:(id)fp8;

@end

