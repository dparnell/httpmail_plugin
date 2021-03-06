/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class NSArray, NSString;

@interface IMAPOperation : NSObject
{
    unsigned int _type:8;
    unsigned int _temporaryUids:1;
    NSString *_mailboxName;
    union {
        struct {
            NSArray *trueFlags;
            NSArray *falseFlags;
            struct __CFArray *uids;
        } store;
        struct {
            unsigned int uid;
            NSArray *flags;
            int internalDate;
            unsigned int size;
        } append;
        struct {
            struct __CFArray *srcUids;
            struct __CFArray *dstUids;
            NSString *destinationMailbox;
        } copy;
    } _opSpecific;
}

+ (id)deserializeFromData:(id)fp8 cursor:(unsigned int *)fp12;
- (void)_deserializeOpSpecificValuesFromData:(id)fp8 cursor:(unsigned int *)fp12;
- (unsigned char)_magic;
- (BOOL)actsOnTemporaryUid:(unsigned int)fp8;
- (unsigned int)approximateSize;
- (void)dealloc;
- (id)description;
- (id)destinationMailbox;
- (id)destinationUids;
- (void)expungeTemporaryUid:(unsigned int)fp8;
- (void)finalize;
- (unsigned int)firstTemporaryUid;
- (id)flags;
- (id)flagsToClear;
- (id)flagsToSet;
- (BOOL)getMessageId:(id *)fp8 andInternalDate:(id *)fp12 forDestinationUid:(unsigned int)fp16;
- (id)initWithAppendedUid:(unsigned int)fp8 approximateSize:(unsigned int)fp12 flags:(id)fp16 internalDate:(id)fp20 mailbox:(id)fp24;
- (id)initWithFlagsToSet:(id)fp8 flagsToClear:(id)fp12 forUids:(id)fp16 inMailbox:(id)fp20;
- (id)initWithMailboxToCreate:(id)fp8;
- (id)initWithMailboxToDelete:(id)fp8;
- (id)initWithUidsToCopy:(id)fp8 fromMailbox:(id)fp12 toMailbox:(id)fp16 firstNewUid:(unsigned int)fp20;
- (id)internalDate;
- (BOOL)isSourceOfTemporaryUid:(unsigned int)fp8;
- (unsigned int)lastTemporaryUid;
- (id)mailboxName;
- (int)operationType;
- (void)serializeIntoData:(id)fp8;
- (void)setMessageId:(id)fp8 andInternalDate:(id)fp12 forMessageWithSourceUid:(unsigned int)fp16;
- (void)setUsesRealUids:(BOOL)fp8;
- (unsigned int)sourceUidForTemporaryUid:(unsigned int)fp8;
- (id)sourceUids;
- (unsigned int)uid;
- (id)uids;
- (BOOL)usesRealUids;

@end

