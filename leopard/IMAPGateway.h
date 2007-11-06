/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

#import "MonitoredInvocationQueueDelegateProtocol.h"

@class IMAPClientOperationQueue, IMAPConnection, IMAPConnectionPool, MonitoredInvocationQueue, NSCondition, NSLock;

@interface IMAPGateway : NSObject <MonitoredInvocationQueueDelegate>
{
    IMAPConnectionPool *_connectionPool;
    IMAPConnection *_connection;
    IMAPClientOperationQueue *_operationQueue;
    MonitoredInvocationQueue *_executionQueue;
    NSCondition *_connectionAvailabilityCondition;
    unsigned int _clientCount;
    NSLock *_clientCountLock;
    BOOL _canYield;
    BOOL _remainedDeserted;
    BOOL _needsSelect;
    BOOL _isSealedShut;
}

+ (void)_addIdleGateway:(id)fp8;
+ (void)_removeIdleGateway:(id)fp8;
+ (void)_checkIdleGateways;
- (void)dealloc;
- (id)initWithIMAPConnection:(id)fp8 mailbox:(id)fp12 pool:(id)fp16;
- (void)setConnectionPool:(id)fp8;
- (id)connection;
- (void)setConnection:(id)fp8;
- (void)setOperationQueue:(id)fp8;
- (void)observeValueForKeyPath:(id)fp8 ofObject:(id)fp12 change:(id)fp16 context:(void *)fp20;
- (void)checkIn;
- (void)queueDidEmpty;
- (BOOL)_mightWantToCheckInNowWithRetry;
- (BOOL)_mightWantToCheckInNowRetry:(BOOL)fp8;
- (BOOL)checkOut;
- (void)yield;
- (void)suspend;
- (void)resumeWithConnection:(id)fp8 reselect:(BOOL)fp12;
- (void)sealShutAndCompact:(BOOL)fp8 allowNetworking:(BOOL)fp12;
- (BOOL)_finishQueueIdlingAndSuspend:(BOOL)fp8;
- (BOOL)isDeserted;
- (void)allowClientOperationThrough:(id)fp8;
- (void)_allowClientOperationThrough:(id)fp8;
- (void)_executeSuspend:(id)fp8;
- (BOOL)addClientOperation:(id)fp8 toQueueAndWaitUntilFinished:(BOOL)fp12;
- (void)waitUntilClientOperationIsFinished:(id)fp8;
- (void)waitUntilAllOperationsAreFinished;
- (id)mailboxName;
- (void)configureForMailboxName:(id)fp8;
- (BOOL)supportsCapability:(int)fp8;
- (id)mailboxNameIfSelected:(BOOL)fp8;
- (void)_setError:(id *)fp8 fromOperation:(id)fp12;
- (void)_setErrorFromOperation:(id)fp8 overwriteExistingError:(BOOL)fp12;
- (void)noop;
- (void)setServerPathPrefixOnAccount:(id)fp8 withSeparatorChar:(id)fp12;
- (id)namespacesWithSeparatorChar:(id)fp8;
- (void)listingForMailbox:(id)fp8 options:(int)fp12 listingInfo:(id)fp16;
- (void)subscribedListingForMailbox:(id)fp8 options:(int)fp12 listingInfo:(id)fp16;
- (void)fetchStatusForMailboxes:(id)fp8 dataItems:(unsigned int)fp12;
- (id)statusForMailbox:(id)fp8 dataItems:(unsigned int)fp12;
- (BOOL)examineMailbox:(id)fp8;
- (BOOL)selectMailbox:(id)fp8;
- (BOOL)_addSelectOperationForMailbox:(id)fp8 type:(int)fp12;
- (void)_waitForDelayedSelectOperation:(id)fp8;
- (BOOL)_completeSelectOperation:(id)fp8;
- (BOOL)createMailbox:(id)fp8;
- (BOOL)deleteMailbox:(id)fp8;
- (BOOL)renameMailbox:(id)fp8 toMailbox:(id)fp12;
- (BOOL)subscribeMailbox:(id)fp8;
- (BOOL)unsubscribeMailbox:(id)fp8;
- (void)fetchQuotaRootNamesForMailboxes:(id)fp8;
- (BOOL)getQuotaForRootName:(id)fp8;
- (BOOL)check:(id *)fp8;
- (BOOL)expunge;
- (BOOL)expungeUids:(id)fp8;
- (BOOL)_expungeUids:(id)fp8 mailboxName:(id)fp12;
- (void)close;
- (void)logout;
- (void)closeAndLogout;
- (void)unselect;
- (void)fetchTotalSizeAndMessageCount;
- (void)storeFlags:(id)fp8 state:(BOOL)fp12 forUids:(id)fp16;
- (BOOL)_expunge:(BOOL)fp8 orStoreFlags:(id)fp12 state:(BOOL)fp16 forUids:(id)fp20;
- (BOOL)_storeFlags:(id)fp8 state:(BOOL)fp12 forUids:(id)fp16 mailboxName:(id)fp20;
- (BOOL)deleteMessagesOlderThanNumberOfDays:(int)fp8 settingFlags:(id)fp12;
- (BOOL)copyUids:(id)fp8 toMailboxNamed:(id)fp12 messageInfo:(id)fp16 error:(id *)fp20;
- (BOOL)appendData:(id)fp8 toMailboxNamed:(id)fp12 flags:(id)fp16 dateReceived:(id)fp20 messageInfo:(id)fp24 error:(id *)fp28;
- (id)searchUidRange:(CDAnonymousStruct2)fp8 forTerms:(id)fp16;
- (id)searchUidRange:(CDAnonymousStruct2)fp8 forNewMessageIDs:(id)fp16;
- (unsigned int)searchedUidNextForMessageNumber:(unsigned int)fp8;
- (void)refreshDone:(BOOL)fp8 withOperation:(id)fp12;
- (void)startIdle;
- (id)description;
- (BOOL)needsSelect;
- (void)setNeedsSelect:(BOOL)fp8;
- (BOOL)isSealedShut;
- (void)setIsSealedShut:(BOOL)fp8;
- (id)connectionAvailabilityCondition;
- (void)setConnectionAvailabilityCondition:(id)fp8;
- (id)clientCountLock;
- (void)setClientCountLock:(id)fp8;
- (unsigned int)clientCount;
- (void)setClientCount:(unsigned int)fp8;
- (BOOL)remainedDeserted;
- (void)setRemainedDeserted:(BOOL)fp8;
- (BOOL)canYield;
- (void)setCanYield:(BOOL)fp8;
- (id)executionQueue;
- (void)setExecutionQueue:(id)fp8;
- (id)operationQueue;
- (id)connectionPool;

@end

