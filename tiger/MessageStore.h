/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "SafeObserver.h"

@class ActivityMonitor, MailAccount, MailboxUid, NSMutableArray, NSMutableSet, NSTimer, ObjectCache;

@interface MessageStore : SafeObserver
{
    struct {
        unsigned int isReadOnly:1;
        unsigned int hasUnsavedChangesToMessageData:1;
        unsigned int haveOpenLockFile:1;
        unsigned int rebuildingTOC:1;
        unsigned int compacting:1;
        unsigned int cancelInvalidation:1;
        unsigned int forceInvalidation:1;
        unsigned int isWritingChangesToDisk:1;
        unsigned int isTryingToClose:1;
        unsigned int compactOnClose:1;
        unsigned int reserved:22;
    } _flags;
    MailboxUid *_mailboxUid;
    MailAccount *_account;
    NSMutableArray *_allMessages;
    unsigned int _allMessagesSize;
    unsigned int _deletedMessagesSize;
    unsigned int _deletedMessageCount;
    unsigned int _unreadMessageCount;
    int _state;
    union {
        struct {
            ObjectCache *_headerDataCache;
            ObjectCache *_headerCache;
            ObjectCache *_bodyDataCache;
            ObjectCache *_bodyCache;
        } objectCaches;
        struct {
            struct __CFDictionary *_headerDataCache;
            struct __CFDictionary *_headerCache;
            struct __CFDictionary *_bodyDataCache;
            struct __CFDictionary *_bodyCache;
        } intKeyCaches;
    } _caches;
    NSTimer *_timer;
    NSMutableSet *_uniqueStrings;
    double timeOfLastAutosaveOperation;
    ActivityMonitor *_openMonitor;
}

+ (struct _NSMapTable *)_storeCacheMapTable;
+ (BOOL)cheapStoreAtPathIsEmpty:(id)fp8;
+ (int)copyMessages:(id)fp8 toMailboxUid:(id)fp12 shouldDelete:(BOOL)fp16;
+ (BOOL)createEmptyStoreForPath:(id)fp8;
+ (BOOL)createEmptyStoreIfNeededForPath:(id)fp8 notIndexable:(BOOL)fp12;
+ (id)currentlyAvailableStoreForUid:(id)fp8;
+ (id)currentlyAvailableStoresForAccount:(id)fp8;
+ (id)descriptionOfOpenStores;
+ (void)initialize;
+ (unsigned int)numberOfCurrentlyOpenStores;
+ (id)registerAvailableStore:(id)fp8;
+ (void)removeStoreFromCache:(id)fp8;
+ (BOOL)storeAtPathIsWritable:(id)fp8;
- (id)_defaultRouterDestination;
- (id)_getSerialNumberString;
- (BOOL)_shouldChangeComponentMessageFlags;
- (BOOL)_shouldChangeComponentMessageFlagsForMessage:(id)fp8;
- (id)account;
- (void)addMessageToAllMessages:(id)fp8;
- (void)addMessagesToAllMessages:(id)fp8;
- (BOOL)allowsAppend;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16;
- (int)appendMessages:(id)fp8 unsuccessfulOnes:(id)fp12 newMessageIDs:(id)fp16 newMessages:(id)fp20;
- (id)bodyDataForMessage:(id)fp8;
- (id)bodyForMessage:(id)fp8 fetchIfNotAvailable:(BOOL)fp12;
- (id)bodyForMessage:(id)fp8 fetchIfNotAvailable:(BOOL)fp12 updateFlags:(BOOL)fp16;
- (BOOL)canCompact;
- (BOOL)canRebuild;
- (void)cancelOpen;
- (id)colorForMessage:(id)fp8;
- (id)copyOfAllMessages;
- (id)copyOfAllMessagesWithOptions:(unsigned int)fp8;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (id)dataForMimePart:(id)fp8;
- (void)dealloc;
- (void)deleteLastMessageWithHeader:(id)fp8 forHeaderKey:(id)fp12 compactWhenDone:(BOOL)fp16;
- (void)deleteMessages:(id)fp8 moveToTrash:(BOOL)fp12;
- (void)deleteMessagesOlderThanNumberOfDays:(int)fp8 compact:(BOOL)fp12;
- (void)deletedCount:(unsigned int *)fp8 andSize:(unsigned int *)fp12;
- (id)description;
- (void)didOpen;
- (id)displayName;
- (const char *)displayNameForLogging;
- (void)doCompact;
- (void)fetchSynchronously;
- (void)finalize;
- (id)finishRoutingMessages:(id)fp8 routed:(id)fp12;
- (id)fullBodyDataForMessage:(id)fp8;
- (id)fullBodyDataForMessage:(id)fp8 andHeaderDataIfReadilyAvailable:(id *)fp12;
- (BOOL)hasCachedDataForMimePart:(id)fp8;
- (BOOL)hasUnsavedChangesToMessageData;
- (id)headerDataForMessage:(id)fp8;
- (id)headersForMessage:(id)fp8;
- (id)headersForMessage:(id)fp8 fetchIfNotAvailable:(BOOL)fp12;
- (unsigned int)indexOfMessage:(id)fp8;
- (id)initWithMailboxUid:(id)fp8 readOnly:(BOOL)fp12;
- (void)insertMessageToAllMessages:(id)fp8 atIndex:(unsigned int)fp12;
- (void)invalidateSavingChanges:(BOOL)fp8;
- (BOOL)isDrafts;
- (BOOL)isOpened;
- (BOOL)isReadOnly;
- (BOOL)isSortedAscending;
- (BOOL)isTrash;
- (id)mailboxUid;
- (void)messageColorsNeedToBeReevaluated;
- (void)messageFlagsDidChange:(id)fp8 flags:(id)fp12;
- (id)messageForMessageID:(id)fp8;
- (id)messageWithValue:(id)fp8 forHeader:(id)fp12 options:(unsigned int)fp16;
- (void)messagesWereAdded:(id)fp8;
- (void)messagesWereCompacted:(id)fp8;
- (id)mutableCopyOfAllMessages;
- (void)openAsynchronously;
- (void)openAsynchronouslyUpdatingMetadata:(BOOL)fp8;
- (void)openAsynchronouslyWithOptions:(unsigned int)fp8;
- (void)openSynchronously;
- (void)openSynchronouslyUpdatingMetadata:(BOOL)fp8;
- (void)queueSaveChangesInvocation;
- (void)rebuildTableOfContentsAsynchronously;
- (id)routeMessages:(id)fp8;
- (id)routeMessages:(id)fp8 isUserAction:(BOOL)fp12;
- (void)setColor:(id)fp8 highlightTextOnly:(BOOL)fp12 forMessages:(id)fp16;
- (void)setFlag:(id)fp8 state:(BOOL)fp12 forMessages:(id)fp16;
- (id)setFlagsFromDictionary:(id)fp8 forMessage:(id)fp12;
- (id)setFlagsFromDictionary:(id)fp8 forMessages:(id)fp12;
- (void)setJunkMailLevel:(int)fp8 forMessages:(id)fp12;
- (void)setJunkMailLevel:(int)fp8 forMessages:(id)fp12 trainJunkMailDatabase:(BOOL)fp16;
- (void)setNumberOfAttachments:(unsigned int)fp8 isSigned:(BOOL)fp12 isEncrypted:(BOOL)fp16 forMessage:(id)fp20;
- (BOOL)setPreferredEncoding:(unsigned long)fp8 forMessage:(id)fp12;
- (id)sortOrder;
- (void)startSynchronization;
- (id)status;
- (id)storePathRelativeToAccount;
- (void)structureDidChange;
- (void)suggestSortOrder:(id)fp8 ascending:(BOOL)fp12;
- (unsigned int)totalCount;
- (unsigned int)totalMessageSize;
- (void)undeleteMessages:(id)fp8;
- (int)undoAppendOfMessageIDs:(id)fp8;
- (id)uniquedString:(id)fp8;
- (unsigned int)unreadCount;
- (void)updateMessageColorsAsynchronouslyForMessages:(id)fp8;
- (void)updateMessageColorsSynchronouslyForMessages:(id)fp8;
- (void)updateMetadata;
- (void)updateMetadataAsynchronously;
- (void)updateNumberOfAttachmentsForMessages:(id)fp8;
- (void)updateUserInfoToLatestValues;
- (id)willBeReleased;
- (void)writeUpdatedMessageDataToDisk;

@end

