/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "MessageStore.h"

@class IMAPCommandPipeline, IMAPDownloadCache, IMAPMailboxSyncEngine, NSDate, NSMutableDictionary, NSSet, NSString;

@interface LibraryIMAPStore : MessageStore
{
    unsigned int _supportsCustomPermanentFlags:1;
    unsigned int _supportsJunkFlag:1;
    unsigned int _supportsDollarJunkFlag:1;
    unsigned int _supportsNotJunkFlag:1;
    unsigned int _supportsDollarNotJunkFlag:1;
    unsigned int _supportsForwardedFlag:1;
    unsigned int _supportsDollarForwardedFlag:1;
    unsigned int _updatingCache:1;
    unsigned int _updateMetadata:1;
    unsigned int _readyToDealloc:1;
    unsigned int _reserved:19;
    NSString *_mailboxName;
    NSSet *_cachedContents;
    NSDate *_cachedDirModDate;
    IMAPDownloadCache *_downloadCache;
    IMAPCommandPipeline *_fetchPipeline;
    IMAPMailboxSyncEngine *_syncEngine;
    unsigned int _totalCount;
    NSMutableDictionary *_recentFlagChangesByMessageID;
}

+ (BOOL)createEmptyStoreForPath:(id)fp8;
+ (void)initialize;
+ (BOOL)storeAtPathIsWritable:(id)fp8;
- (id)URLString;
- (void)_addOfflineTransferMessages:(id)fp8;
- (BOOL)_allMessagesHaveDateReceived;
- (BOOL)_changedFlagsForMessage:(id)fp8 fetchResponse:(id)fp12 newFlags:(unsigned int *)fp16;
- (void)_countUnreadAndDeleted;
- (void)_countUnreadAndDeletedInMessages:(id)fp8;
- (id)_createDataFromMimePart:(id)fp8 threshold:(unsigned int)fp12;
- (id)_dataForMessage:(id)fp8 readHeadersOnly:(BOOL)fp12;
- (int)_doAppend:(void *)fp8;
- (BOOL)_doUidCopy:(void *)fp8 toStore:(id)fp12 newMessages:(id)fp16;
- (id)_fetchBodyDataForMessage:(id)fp8 andHeaderDataIfReadilyAvailable:(id *)fp12;
- (id)_fetchDataForMimePart:(id)fp8 keepInMemory:(BOOL)fp12 writeToDisk:(BOOL)fp16;
- (void)_fetchForCheckingNewMail:(BOOL)fp8;
- (id)_fetchHeaderDataForMessage:(id)fp8;
- (void)_fetchMessageIDHeaderForMessages:(id)fp8;
- (void)_invalidate;
- (void)_invalidateColorForMessages:(id)fp8;
- (id)_lockedGetCacheDirectoryContents;
- (id)_messageForTemporaryUid:(unsigned long)fp8;
- (id)_messageForUid:(unsigned long)fp8;
- (id)_preferredOrderForFetchingMessageBodies:(id)fp8;
- (void)_rebuildTableOfContentsSynchronously;
- (void)_retrieveNewMessagesForCheckingNewMail:(BOOL)fp8;
- (void)_setBackgroundColorForMessages:(id)fp8 textColorForMessages:(id)fp12;
- (void)_setFlagsAndColorForMessages:(id)fp8;
- (void)_setFlagsForMessages:(id)fp8 mask:(unsigned long)fp12;
- (void)_setFlagsFromDictionary:(id)fp8 forMessages:(id)fp12;
- (void)_setInternalDateForMessages:(id)fp8;
- (BOOL)_shouldCallCompactWhenClosing;
- (BOOL)_shouldChangeComponentMessageFlagsForMessage:(id)fp8;
- (void)_synchronouslyStoreFlagsFromDictionary:(id)fp8 forMessages:(id)fp12;
- (id)_uidsForMessages:(id)fp8;
- (id)addMessage:(id)fp8;
- (void)addMessageToAllMessages:(id)fp8;
- (id)addMessages:(id)fp8 oldMessagesByNewMessage:(id)fp12;
- (BOOL)allowsAppend;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16 newMessages:(id)fp20;
- (id)cacheDirectoryContents;
- (BOOL)canCompact;
- (BOOL)canRebuild;
- (void)checkNewMail;
- (id)colorForMessage:(id)fp8;
- (void)compactMessages:(id)fp8;
- (id)connection;
- (void)connection:(id)fp8 didReceiveResponse:(id)fp12 forCommand:(void *)fp16;
- (BOOL)connection:(id)fp8 shouldHandleUntaggedResponse:(id)fp12 forCommand:(void *)fp16;
- (void)connectionDidDisconnect:(id)fp8;
- (id)copyOfAllMessages;
- (id)copyOfAllMessagesSortedByUidWithOptions:(unsigned int)fp8;
- (id)copyOfAllMessagesWithOptions:(unsigned int)fp8;
- (id)copyOfOldCachedMessagesContentsForUid:(unsigned long)fp8;
- (id)createDictionaryForLocalFlags:(unsigned long)fp8 serverFlags:(unsigned long)fp12 existingDictionary:(id)fp16;
- (id)dataForMimePart:(id)fp8;
- (void)dealloc;
- (void)deleteLastMessageWithHeader:(id)fp8 forHeaderKey:(id)fp12 compactWhenDone:(BOOL)fp16;
- (void)deleteMessagesOlderThanNumberOfDays:(int)fp8 compact:(BOOL)fp12;
- (id)deletedMessages;
- (void)doCompact;
- (id)downloadCache;
- (id)fetchPipeline;
- (void)fetchSynchronously;
- (void)finalize;
- (void)forceResync;
- (id)fullBodyDataForMessage:(id)fp8 andHeaderDataIfReadilyAvailable:(id *)fp12;
- (BOOL)hasCachedDataForMimePart:(id)fp8;
- (BOOL)hasValidCacheFileForMessage:(id)fp8;
- (BOOL)hasValidCacheFileForUid:(unsigned long)fp8;
- (unsigned int)indexOfMessage:(id)fp8;
- (id)initWithCoder:(id)fp8;
- (id)initWithMailboxUid:(id)fp8 readOnly:(BOOL)fp12;
- (void)insertMessageToAllMessages:(id)fp8 atIndex:(unsigned int)fp12;
- (BOOL)isSortedAscending;
- (int)lastUid;
- (id)mailboxName;
- (id)messageForMessageID:(id)fp8;
- (id)messagesBeingRouted;
- (id)messagesForImporter;
- (void)messagesWereAdded:(id)fp8;
- (id)mutableCopyOfAllMessages;
- (void)newMessagesAvailable:(id)fp8;
- (void)openAsynchronouslyWithOptions:(unsigned int)fp8;
- (void)openSynchronouslyUpdatingMetadata:(BOOL)fp8;
- (id)recentFlagChangesForMessageID:(id)fp8;
- (void)removeAllLocalMessages;
- (void)removeCachedFiles:(id)fp8;
- (id)setFlagsFromDictionary:(id)fp8 forMessages:(id)fp12;
- (void)setLocalFlagsFromDictionary:(id)fp8 forMessages:(id)fp12;
- (BOOL)setPreferredEncoding:(unsigned long)fp8 forMessage:(id)fp12;
- (void)setUid:(unsigned long)fp8 forMessageWithTemporaryUid:(unsigned long)fp12;
- (id)sortOrder;
- (void)startSynchronization;
- (unsigned int)totalCount;
- (int)undoAppendOfMessageIDs:(id)fp8;
- (void)updateMetadata;
- (void)updateUserInfoToLatestValues;
- (id)willBeReleased;
- (void)writeUpdatedMessageDataToDisk;

@end

