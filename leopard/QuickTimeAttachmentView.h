/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSView.h"

@class MailTextAttachment, NSURL;

@interface QuickTimeAttachmentView : NSView
{
    NSURL *_url;
    id _qtMovieView;
    unsigned int _isInteractive:1;
    MailTextAttachment *_attachment;
}

+ (void)initialize;
+ (id)viewForFileWrapper:(id)fp8;
- (void)setURL:(id)fp8;
- (id)URL;
- (void)setAttachment:(id)fp8;
- (void)webPlugInStart;
- (void)viewWillMoveToSuperview:(id)fp8;
- (id)menuForEventDelegate:(id)fp8;
- (id)menuForEvent:(id)fp8;
- (void)dealloc;
- (void)setFrame:(struct _NSRect)fp8;
- (void)mouseDraggedDelegate:(id)fp8;
- (void)mouseDragged:(id)fp8;

@end

