/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

#import "MessageContentDisplayProtocol.h"

@class LoadingOverlay, MessageTilingView, NSImageView, NSProgressIndicator, NSTimer, TextMessageDisplay;

@interface FadingMessageDisplay : NSObject <MessageContentDisplay>
{
    NSTimer *_fadeTimer;
    int _fadeStepCounter;
    TextMessageDisplay *_textMessageDisplay;
    NSImageView *_snapshotView;
    MessageTilingView *_originalView;
    LoadingOverlay *_loadingOverlay;
    NSProgressIndicator *_progressIndicator;
}

+ (id)copyDocumentForMessage:(id)fp8 viewingState:(id)fp12;
- (void)dealloc;
- (void)showMessageProgress;
- (void)loadingOverlayDidEnd:(id)fp8 returnCode:(int)fp12;
- (void)fadeOneNotch:(id)fp8;
- (id)contentView;
- (id)textView;
- (id)copySnapshotOfRect:(struct _NSRect)fp8 inView:(id)fp24;
- (void)display:(id)fp8 inContainerView:(id)fp12 replacingView:(id)fp16 invokeWhenDisplayChanged:(id)fp20;
- (void)prepareToRemoveView;
- (id)delegate;
- (void)setDelegate:(id)fp8;
- (id)selectedTextRepresentation;
- (void)setSelectedTextRepresentation:(id)fp8;
- (id)selectedText;
- (id)selectedWebArchive;
- (id)attachmentsInSelection;
- (id)webArchiveBaseURL:(id *)fp8;
- (void)highlightSearchText:(id)fp8;
- (void)adjustFontSizeBy:(int)fp8 viewingState:(id)fp12;
- (void)setTextMessageDisplay:(id)fp8;
- (id)findTarget;
- (struct __CFDictionary *)stringsForURLification;
- (void)updateURLMatches:(id)fp8 viewingState:(id)fp12;
- (void)detectDataInMessage:(id)fp8 usingContext:(id)fp12;

@end

