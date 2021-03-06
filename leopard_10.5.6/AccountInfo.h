/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class AccountSummary, IMAPMailboxes, MailAccount, NSMutableSet, NSPopUpButton, NSTabView, NSTabViewItem, NSView, NSWindow, Quota, SpecialMailboxes;

@interface AccountInfo : NSObject
{
    NSWindow *_window;
    NSView *_topView;
    NSTabView *_tabView;
    NSPopUpButton *_accountPopup;
    NSTabViewItem *_mailboxListTab;
    AccountSummary *_summary;
    SpecialMailboxes *_specialMailboxes;
    NSView *_specialMailboxesView;
    Quota *_quota;
    IMAPMailboxes *_mailboxes;
    MailAccount *_account;
    NSMutableSet *_tabViewItemsThatHaveBeenSetup;
    struct _NSRect _oldFrame;
    struct _NSRect _newFrame;
}

+ (void)showForAccount:(id)fp8 withTab:(id)fp12;
- (id)initWithMailAccount:(id)fp8;
- (void)dealloc;
- (void)_configureAccountPopupSelectingAccount:(id)fp8;
- (id)_selectedAccount;
- (void)_setAccount:(id)fp8 setupSelectedTab:(BOOL)fp12;
- (void)_setupTabViewItem:(id)fp8 oldTabViewItem:(id)fp12;
- (void)_commitSpecialMailboxesChanges;
- (void)_accountsDidChange:(id)fp8;
- (void)_specialMailboxesDidChange:(id)fp8;
- (void)_showWithTab:(id)fp8;
- (void)accountPopupChanged:(id)fp8;
- (void)tabView:(id)fp8 willSelectTabViewItem:(id)fp12;
- (void)tabView:(id)fp8 didSelectTabViewItem:(id)fp12;
- (void)windowWillClose:(id)fp8;

@end

