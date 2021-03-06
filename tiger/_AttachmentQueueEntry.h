/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class NSString, NSTextAttachment, NSURL, NSWindow;

@interface _AttachmentQueueEntry : NSObject
{
    NSWindow *window;
    NSTextAttachment *attachment;
    int reason;
    NSString *attachDir;
    union {
        NSURL *applicationURL;
        NSString *savePath;
    } opSpecific;
}

+ (id)newWithWindow:(id)fp8 attachment:(id)fp12 reason:(int)fp16 opSpecific:(id)fp20 attachmentDirectory:(id)fp24;
- (void)dealloc;
- (BOOL)isEqual:(id)fp8;

@end

