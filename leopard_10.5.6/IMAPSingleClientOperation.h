/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import <Message/IMAPClientOperation.h>

@class MFError, NSMutableArray;

@interface IMAPSingleClientOperation : IMAPClientOperation
{
    NSMutableArray *_untaggedResponses;
    MFError *_error;
    unsigned int _sequenceNumber;
    unsigned int _sessionNumber;
    BOOL _isComplete;
}

- (void)dealloc;
- (int)composition;
- (BOOL)handlesAllUntaggedResponses;
- (void)setSequenceNumber:(unsigned int)fp8;
- (void)cleanupAfterCompletion;
- (id)debugCommandString;
- (id)createCommandDataForLiteralPlus:(BOOL)fp8;
- (id)tag;
- (id)createCommandString;
- (BOOL)isComplete;
- (void)setIsComplete:(BOOL)fp8;
- (unsigned int)sessionNumber;
- (void)setSessionNumber:(unsigned int)fp8;
- (unsigned int)sequenceNumber;
- (id)error;
- (void)setError:(id)fp8;
- (id)untaggedResponses;
- (void)setUntaggedResponses:(id)fp8;

@end

