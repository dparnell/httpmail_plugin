/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "MessageStore.h"

@class NSData;

@interface NSDataMessageStore : MessageStore
{
    NSData *_data;
}

- (id)_cachedBodyForMessage:(id)fp8 valueIfNotPresent:(id)fp12;
- (id)_cachedHeadersForMessage:(id)fp8 valueIfNotPresent:(id)fp12;
- (id)bodyDataForMessage:(id)fp8;
- (void)dealloc;
- (void)finalize;
- (id)headerDataForMessage:(id)fp8;
- (id)initWithData:(id)fp8;
- (id)message;
- (id)storePath;
- (void)writeUpdatedMessageDataToDisk;

@end

