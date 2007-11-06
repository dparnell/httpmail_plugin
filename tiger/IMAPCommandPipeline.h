/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class NSMutableArray;

@interface IMAPCommandPipeline : NSObject
{
    unsigned int _chunkSize;
    unsigned int _expectedSize;
    unsigned int _full:1;
    unsigned int _sending:1;
    NSMutableArray *_fetchUnits;
}

- (void)_removeFetchUnitMatchingResponse:(id)fp8;
- (void)addFetchCommandForUid:(unsigned long)fp8 fetchItem:(id)fp12 expectedLength:(unsigned long)fp16;
- (unsigned long)chunkSize;
- (void)dealloc;
- (unsigned long)expectedSize;
- (id)failureResponsesFromSendingCommandsWithConnection:(id)fp8;
- (BOOL)isFull;
- (BOOL)isSending;
- (void)setChunkSize:(unsigned long)fp8;
- (void)setFull:(BOOL)fp8;

@end

