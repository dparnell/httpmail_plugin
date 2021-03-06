/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

#import "AccountStatusDataSourceDelegateProtocol.h"

@class AccountStatusDataSource, NSArrayController, NSMutableArray, NSMutableDictionary, NSPanel, NSTableColumn, NSTableView;

@interface SMTPSettings : NSObject <AccountStatusDataSourceDelegate>
{
    NSArrayController *deliveryAccountsController;
    NSPanel *panel;
    NSTableView *accountTable;
    NSTableColumn *conflictColumn;
    AccountStatusDataSource *_deliveryASDS;
    NSMutableArray *_accountsInConflict;
    NSMutableDictionary *_cachedAccountEmployment;
    NSMutableDictionary *_cachedAccountEmploymentStrings;
    BOOL _didRegisterForNotifications;
    NSMutableArray *_deliveryAccounts;
}

+ (void)initialize;
+ (id)sharedPanel;
- (id)init;
- (void)dealloc;
- (void)awakeFromNib;
- (void)observeValueForKeyPath:(id)fp8 ofObject:(id)fp12 change:(id)fp16 context:(void *)fp20;
- (void)runSheetRelativeToWindow:(id)fp8 selectedAccount:(id)fp12 didEndDelegate:(id)fp16;
- (void)sheetDidEnd:(id)fp8 returnCode:(int)fp12 contextInfo:(void *)fp16;
- (void)dismissPanel:(id)fp8;
- (void)_syncBindings;
- (BOOL)_validateAccounts;
- (void)_accountInfoDidChange:(id)fp8;
- (BOOL)_checkForConflicts;
- (void)_removeInvalidAccounts;
- (void)_recacheAccountEmployment;
- (void)_restoreMailAccountDefaultAccounts;
- (id)tableView:(id)fp8 objectValueForTableColumn:(id)fp12 row:(int)fp16;
- (id)deliveryAccounts;
- (void)setDeliveryAccounts:(id)fp8;

@end

