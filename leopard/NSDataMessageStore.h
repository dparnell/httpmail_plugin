/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "MessageStore.h"

@class NSData;

@interface NSDataMessageStore : MessageStore
{
    NSData *_data;
}

- (id)initWithData:(id)fp8;
- (void)dealloc;
- (void)finalize;
- (id)storePath;
- (void)writeUpdatedMessageDataToDisk;
- (id)message;
- (id)headerDataForMessage:(id)fp8;
- (id)bodyDataForMessage:(id)fp8;
- (id)_cachedBodyForMessage:(id)fp8 valueIfNotPresent:(id)fp12;
- (id)_cachedHeadersForMessage:(id)fp8 valueIfNotPresent:(id)fp12;

@end

