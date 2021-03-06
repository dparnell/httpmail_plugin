/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@class MailboxUid, MessageStore, NSMutableArray;

@interface TransferOperation : NSObject
{
    MessageStore *sourceStore;
    MailboxUid *destinationMailboxUid;
    NSMutableArray *sourceMessages;
    NSMutableArray *unreadSourceMessages;
    NSMutableArray *destinationMessageIDs;
    NSMutableArray *documentIDs;
    BOOL editableDocuments;
}

- (void)dealloc;
- (id)initWithSourceStore:(id)fp8 destinationMailboxUid:(id)fp12 editableDocuments:(BOOL)fp16;
- (id)sourceStore;
- (id)sourceLibraryStore;
- (id)destinationMailboxUid;
- (void)addSourceMessage:(id)fp8;
- (void)removeSourceMessages:(id)fp8;

@end

