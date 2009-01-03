/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class NSMutableArray;

@interface IMAPCommandPipeline : NSObject
{
    unsigned int _chunkSize;
    unsigned int _expectedSize;
    BOOL _isSending;
    BOOL _isFull;
    NSMutableArray *_fetchUnits;
    double _startedSendingTime;
}

- (void)dealloc;
- (void)addFetchCommandForUid:(unsigned long)fp8 fetchItem:(id)fp12 expectedLength:(unsigned long)fp16;
- (void)_removeFetchUnitMatchingResponse:(id)fp8;
- (id)failureResponsesFromSendingCommandsWithGateway:(id)fp8 responseHandler:(id)fp12 highPriority:(BOOL)fp16;
- (void)observeValueForKeyPath:(id)fp8 ofObject:(id)fp12 change:(id)fp16 context:(void *)fp20;
- (double)startedSendingTime;
- (void)setStartedSendingTime:(double)fp8;
- (id)fetchUnits;
- (void)setFetchUnits:(id)fp8;
- (BOOL)isFull;
- (void)setIsFull:(BOOL)fp8;
- (BOOL)isSending;
- (void)setIsSending:(BOOL)fp8;
- (unsigned long)expectedSize;
- (void)setExpectedSize:(unsigned long)fp8;
- (unsigned long)chunkSize;
- (void)setChunkSize:(unsigned long)fp8;

@end

