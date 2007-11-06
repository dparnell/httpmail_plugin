/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@class MessageContentController, NSMutableArray, NSPrintInfo, NSPrintOperation, NSString, NSWindow;

@interface MessagePrinter : NSObject
{
    MessageContentController *_contentController;
    NSMutableArray *_messages;
    unsigned int _messageIndex;
    NSString *_originalFilename;
    NSPrintInfo *_printInfo;
    NSPrintOperation *_printOperation;
    unsigned int _scalingBehavior;
    NSWindow *_onscreenWindow;
    NSWindow *_window;
}

+ (id)sharedPrintInfo;
+ (void)_setScalingBehaviorInDefaults:(unsigned int)fp8;
+ (unsigned int)_scalingBehaviorFromDefaults;
+ (void)initialize;
- (void)printMessages:(id)fp8 viewingState:(id)fp12 showDefaultHeaders:(BOOL)fp16 forWindow:(id)fp20;
- (id)_printInfo;
- (void)_setPrintInfo:(id)fp8;
- (unsigned int)scalingBehavior;
- (void)setScalingBehavior:(unsigned int)fp8;
- (void)_setPrintOperation:(id)fp8;
- (id)_printOperation;
- (id)init;
- (void)dealloc;
- (void)_releaseMessages;
- (void)_setMessages:(id)fp8;
- (void)_regularMessageIsReady:(id)fp8;
- (id)_currentMessage;
- (id)_printOperationFromContentController;
- (void)_printNextMessage;
- (void)_cleanUp;
- (unsigned int)_displayIDForWindow:(id)fp8;
- (void)_printInfoDidChange:(id)fp8;
- (struct _NSRect)_windowFrameForBehavior:(unsigned int)fp8 printInfo:(id)fp12;
- (void)_printOperationDidRun:(id)fp8 success:(BOOL)fp12 contextInfo:(id)fp16;
- (id)_messageTitleForMessage:(id)fp8;

@end

