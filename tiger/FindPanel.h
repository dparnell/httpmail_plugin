/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class NSButton, NSMatrix, NSString, NSTextField;

@interface FindPanel : NSObject
{
    NSButton *findNextButton;
    NSTextField *findTextField;
    NSButton *ignoreCaseButton;
    NSMatrix *replaceAllScopeMatrix;
    NSTextField *replaceTextField;
    NSTextField *statusField;
    NSString *findString;
    BOOL lastFindWasSuccessful;
}

+ (id)sharedInstance;
- (void)_appDidActivate;
- (void)dealloc;
- (void)findNext:(id)fp8;
- (void)findNextAndOrderFindPanelOut:(id)fp8;
- (id)findPanel;
- (void)findPrevious:(id)fp8;
- (id)findString;
- (void)ignoreCaseButtonClicked:(id)fp8;
- (id)init;
- (void)orderFrontFindPanel:(id)fp8;
- (void)replace:(id)fp8;
- (void)replaceAll:(id)fp8;
- (void)replaceAndFind:(id)fp8;
- (void)setFindString:(id)fp8;
- (void)setFindString:(id)fp8 writeToPasteboard:(BOOL)fp12;

@end

