/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class Message, NSString;

@interface AppleScriptHeaderRecord : NSObject
{
    NSString *_name;
    id _content;
    Message *_message;
}

- (id)content;
- (void)dealloc;
- (void)finalize;
- (id)message;
- (id)name;
- (id)objectSpecifier;
- (void)setContent:(id)fp8;
- (void)setMessage:(id)fp8;
- (void)setName:(id)fp8;

@end

