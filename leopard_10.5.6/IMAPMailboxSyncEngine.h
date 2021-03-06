/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

#import "IMAPResponseHandler-Protocol.h"

@class ActivityMonitor, IMAPGateway, IMAPMailbox, LibraryIMAPStore, NSMutableArray, NSMutableIndexSet;

@interface IMAPMailboxSyncEngine : NSObject <IMAPResponseHandler>
{
    ActivityMonitor *_monitor;
    IMAPGateway *_gateway;
    LibraryIMAPStore *_store;
    IMAPMailbox *_IMAPMailbox;
    NSMutableArray *_unprocessedResponses;
    NSMutableArray *_auxiliaryLists;
    NSMutableIndexSet *_allNewUids;
    NSMutableIndexSet *_UIDsNeedingSkeletons;
    unsigned int _uidNext;
    unsigned int _uidValidity;
    unsigned int _libraryClientUidNext;
    unsigned int _numMessagesOnServer;
    unsigned int _firstMessageNumber;
    NSMutableArray *_messageDetails;
    unsigned int _maxSkeletonsToFetch;
    NSMutableIndexSet *_expungedUids;
    unsigned int _automaticallyStartThread:1;
    unsigned int _storeIsInbox:1;
    unsigned int _newMailReceivedInInbox:1;
    unsigned int _uidValidityChanged:1;
    unsigned int _checkedForNewUids:1;
    unsigned int _synchronizedOldMessages:1;
    unsigned int _progressType:3;
    unsigned int _connectionSupportsUIDPLUS:1;
    unsigned int _progressTotal:21;
    unsigned int _checkNewMailCount;
    BOOL _storeContainsToDos;
}

- (void)dealloc;
- (id)initWithStore:(id)fp8;
- (void)reset;
- (void)_resetClearingGateway:(BOOL)fp8;
- (void)invalidateStore;
- (void)setGateway:(id)fp8 IMAPMailbox:(id)fp12;
- (void)updateCountOfMessagesOnServerFromIMAPMailbox:(id)fp8;
- (void)_lockedUpdateCountOfMessagesOnServerIfNecessary;
- (void)setUidValidity:(unsigned int)fp8;
- (void)responsesWereAddedToIMAPMailbox:(id)fp8;
- (void)messagesWereAddedToLibrary:(id)fp8;
- (BOOL)messageListIsSynchronized;
- (id)messagesBeingAdded;
- (void)setAutomaticallyStartsBackgroundThread:(BOOL)fp8;
- (void)runInCurrentThread;
- (void)runInCurrentThreadWithMessages:(id)fp8;
- (void)requestCheckingNewMail;
- (void)newUIDsWereAddedToServer:(id)fp8 forMessages:(id)fp12;
- (BOOL)_setGateway:(id)fp8;
- (void)_notifyBackgroundFetchCompleted;
- (void)_go;
- (void)_goWithMessages:(id)fp8;
- (BOOL)_shouldContinueSyncingWithMonitor:(id)fp8;
- (BOOL)_unlockIfProcessedResponsesWithMonitor:(id)fp8;
- (BOOL)_unlockIfGotNewMessageSkeletonsWithMonitor:(id)fp8;
- (id)_lockedCreateOperationFromUIDsNeedingSkeletons:(unsigned int)fp8;
- (BOOL)_unlockIfHandledRoutedUidsWithMonitor:(id)fp8;
- (BOOL)_unlockIfFetchedUidsAndFlagsWithMonitor:(id)fp8;
- (BOOL)_unlockIfSyncedWithLibraryWithMonitor:(id)fp8 messages:(id)fp12;
- (BOOL)_unlockIfDidCacheMessagesWithMonitor:(id)fp8;
- (BOOL)_unlockIfDidCacheAttachmentsWithMonitor:(id)fp8;
- (BOOL)_recoverFromErrorInDownload:(id)fp8 uid:(unsigned long)fp12 cacheList:(id)fp16 atIndex:(unsigned int)fp20 downloadCache:(id)fp24;
- (BOOL)_unlockIfHandledInvitationMessagesWithMonitor:(id)fp8;
- (int)_cachePolicyForAccount:(id)fp8;
- (id)description;
- (BOOL)handleResponse:(id)fp8 forOperation:(id)fp12;
- (void)_setupFakeResponseToOperation:(id)fp8 messageNumber:(unsigned int)fp12;
- (BOOL)_handleFailedFetchResponse:(id)fp8 forOperation:(id)fp12;

@end

