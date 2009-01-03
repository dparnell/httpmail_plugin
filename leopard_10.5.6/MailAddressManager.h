/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

#import "ABImageClient-Protocol.h"

@class NSMutableDictionary, NSMutableSet, ObjectCache;

@interface MailAddressManager : NSObject <ABImageClient>
{
    ObjectCache *_imageCache;
    NSMutableDictionary *emailsAwaitingImage;
    NSMutableDictionary *recordsCache;
    NSMutableSet *addressesWithNoRecords;
    BOOL needToTrimRecordCaches;
    BOOL singleThreaded;
}

+ (id)addressManager;
- (id)init;
- (void)dealloc;
- (void)finalize;
- (void)setOperatesInSingleThread:(BOOL)fp8;
- (BOOL)operatesInSingleThread;
- (id)loadAddressBookAsynchronously;
- (void)loadAddressBookSynchronously;
- (void)_importDidBegin:(id)fp8;
- (void)_importDidUpdate:(id)fp8;
- (void)_importDidEnd:(id)fp8;
- (id)bestRecordMatchingFormattedAddress:(id)fp8;
- (void)trimRecordCachesAfterDelay;
- (void)trimRecordCaches;
- (void)addressBookDidChange:(id)fp8;
- (void)postPhotoChangedNotification;
- (void)recordsMatchingDictionary:(id)fp8;
- (id)recordsMatchingSearchString:(id)fp8;
- (BOOL)addressBookPerson:(id)fp8 nameMatchesSearchWords:(id)fp12;
- (BOOL)email:(id)fp8 matchesSearchWords:(id)fp12;
- (id)betterRecordOfRecent:(id)fp8 addressBook:(id)fp12;
- (id)recordForUniqueId:(id)fp8;
- (id)groupsMatchingString:(id)fp8;
- (void)updateDatesForRecentRecord:(id)fp8;
- (void)_addAddresses:(id)fp8 asRecent:(BOOL)fp12;
- (void)addRecentAddresses:(id)fp8;
- (void)addAddresses:(id)fp8;
- (id)addRecentToAddressBook:(id)fp8;
- (id)addAddressToAddressBook:(id)fp8;
- (void)removeRecordFromAddressBook:(id)fp8 forRecent:(id)fp12;
- (void)removeRecentAddresses:(id)fp8;
- (void)removeRecentRecord:(id)fp8;
- (id)addEmailAddressToCardMatchingFirstAndLastNameFromFormattedAddress:(id)fp8;
- (id)addressBookRecordForRecentRecord:(id)fp8 orEmail:(id)fp12;
- (id)addressBookPersonForEmail:(id)fp8;
- (id)addressBookRecordsForFirstName:(id)fp8 lastName:(id)fp12;
- (id)imageForMailAddress:(id)fp8;
- (void)fetchImageForAddress:(id)fp8;
- (void)consumeImageData:(id)fp8 forTag:(int)fp12;
- (void)cacheImage:(id)fp8 forAddress:(id)fp12;
- (id)groups;
- (void)_addEmailsFromGroup:(id)fp8 toDictionary:(id)fp12;
- (id)emailAddressesFromGroup:(id)fp8;
- (id)expandPrivateAliases:(id)fp8;
- (id)replaceOccurrencesOfPrivateGroupAliasesWithPublicName:(id)fp8;

@end

