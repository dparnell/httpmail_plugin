/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "AccountDetails.h"

@class ActivityMonitor, NSButton, NSPopUpButton, NSTextField;

@interface POPAccountDetails : AccountDetails
{
    NSButton *_deleteMessagesOnServer;
    NSTextField *_bigMessageWarningSize;
    NSButton *_removeSeenMessagesButton;
    NSPopUpButton *_removeIntervalPopup;
    ActivityMonitor *_deleteMessagesMonitor;
    BOOL _deleteObserverActive;
}

- (void)_confirmDeleteSheetDidEnd:(id)fp8 returnValue:(int)fp12 sender:(id)fp16;
- (void)_deleteServerMessagesCompleted:(id)fp8;
- (void)_deleteServerMessagesStarted:(id)fp8;
- (int)_popDeletionPolicyFromUI;
- (Class)accountClass;
- (void)deleteSeenMessagesNow:(id)fp8;
- (void)deleteSeenMessagesSheetDidEnd:(id)fp8 returnCode:(int)fp12 contextInfo:(void *)fp16;
- (id)init;
- (BOOL)isAccountInformationDirty:(id)fp8;
- (void)removeMessagesButtonClicked:(id)fp8;
- (void)setUIElementsEnabled:(BOOL)fp8;
- (void)setupAccountFromValuesInUI:(id)fp8 forValidation:(BOOL)fp12;
- (void)setupUIFromValuesInAccount:(id)fp8;
- (void)warnIfDeleteMessages:(id)fp8;

@end

