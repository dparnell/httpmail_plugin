/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@class IMAPAccount, NSMutableArray;

@interface IMAPOperationCache : NSObject
{
    IMAPAccount *_account;
    NSMutableArray *_ops;
    unsigned int _lastUid;
    unsigned int _lastSave;
}

- (id)initWithIMAPAccount:(id)fp8;
- (void)dealloc;
- (void)finalize;
- (id)account;
- (void)createMailbox:(id)fp8;
- (void)deleteMailbox:(id)fp8;
- (void)setFlags:(id)fp8 andClearFlags:(id)fp12 forMessages:(id)fp16;
- (void)setFlags:(id)fp8 andClearFlags:(id)fp12 forUids:(id)fp16 forMailbox:(id)fp20;
- (unsigned int)firstUidForCopyingMessages:(id)fp8 fromMailbox:(id)fp12 toMailbox:(id)fp16;
- (unsigned int)uidForAppendingMessageData:(id)fp8 withFlags:(id)fp12 andInternalDate:(id)fp16 toMailbox:(id)fp20;
- (void)_expungeMessageWithTemporaryUid:(unsigned int)fp8 orMessageID:(id)fp12 documentID:(id)fp16;
- (void)expungeTemporaryUid:(unsigned int)fp8;
- (void)expungeMessageWithMessageID:(id)fp8 documentID:(id)fp12;
- (void)saveChanges;
- (unsigned int)numberOfPendingChanges;
- (BOOL)hasOperationsForMailbox:(id)fp8;
- (void)_performCreateOperation:(id)fp8 withContext:(CDAnonymousStruct7 *)fp12;
- (void)_performDeleteOperation:(id)fp8 withContext:(CDAnonymousStruct7 *)fp12;
- (void)_performStoreOperation:(id)fp8 ignoringUids:(id)fp12 withContext:(CDAnonymousStruct7 *)fp16;
- (BOOL)_performAppendOperation:(id)fp8 withContext:(CDAnonymousStruct7 *)fp12 backupManager:(id)fp16 recoveredMailboxName:(id *)fp20 error:(id *)fp24;
- (BOOL)_performCopyOperation:(id)fp8 withContext:(CDAnonymousStruct7 *)fp12 failedSourceUids:(id)fp16 error:(id *)fp20;
- (void)performDeferredOperationsWithGateway:(id)fp8 error:(id *)fp12;
- (id)_deferredOperations;

@end

