/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import <Message/MessageBody.h>

@class NSMutableData;

@interface _OutgoingMessageBody : MessageBody
{
    NSMutableData *rawData;
}

- (void)dealloc;
- (void)finalize;
- (id)mutableData;
- (id)rawData;

@end

