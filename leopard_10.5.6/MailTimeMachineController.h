/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class MessageViewer;

@interface MailTimeMachineController : NSObject
{
    MessageViewer *_messageViewer;
    BOOL _savingTOC;
    struct OpaqueEventHandlerRef *_helperAppEventHandler;
    struct ProcessSerialNumber _helperAppPSN;
    struct _NSRect _mailFrame;
}

+ (id)sharedController;
- (id)init;
- (void)registerTimeMachineHandlers;
- (void)unregisterTimeMachineHandlers;
- (void)handleAppleEvent:(id)fp8;
- (void)nowWouldBeAGoodTimeToTerminate:(id)fp8;
- (void)_approvedQuit;
- (void)_saveTableOfContents;
- (void)_thread_saveTableOfContents:(id)fp8;
- (void)_threadedSaveTableOfContentsEnded:(id)fp8;
- (BOOL)_timingOutSaveTableOfContents;
- (void)_threadedSaveTableOfContentsWithEndedSelector:(SEL)fp8;
- (void)_threadedSaveTableOfContents;
- (id)_formattedAddressForAddress:(id)fp8;
- (id)_mailTimeMachineDescriptionForMessage:(id)fp8 withColumns:(id)fp12 andMall:(id)fp16 selected:(BOOL)fp20;
- (void)_launchTimeMachineHelperApp;
- (void)_startWatchingHelperApp;
- (void)_stopWatchingHelperApp;
- (void)_enterTimeMachineMode;
- (void)_prepareExitTimeMachineModeWithDisplayState:(id)fp8;
- (void)_exitTimeMachineModeWithDisplayState:(id)fp8;

@end

