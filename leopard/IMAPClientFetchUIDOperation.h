/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import <Message/IMAPClientFetchOperation.h>

@class NSIndexSet;

@interface IMAPClientFetchUIDOperation : IMAPClientFetchOperation
{
    NSIndexSet *_UIDs;
}

- (void)dealloc;
- (id)init;
- (id)initWithUIDs:(id)fp8;
- (const char *)commandTypeCString;
- (id)_createMessageSetCommandString;
- (id)UIDs;
- (void)setUIDs:(id)fp8;

@end

