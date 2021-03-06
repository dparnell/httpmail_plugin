/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "SafeObserver.h"

@class Account, AccountStatus, NSArray, NSMutableDictionary, NSPopUpButton, NSTableView, NSTextView;

@interface AccountStatusDataSource : SafeObserver
{
    NSPopUpButton *_popUp;
    NSTableView *_table;
    NSTextView *_ispInfoField;
    NSMutableDictionary *_progressIndicators;
    unsigned int _accountFlags;
    BOOL _disabled;
    // Error parsing type: @"NSObject<AccountStatusDataSourceDelegate>", name: _delegate
    AccountStatus *_statusProvider;
    NSArray *_accounts;
    Account *_selectedAccount;
    BOOL _allowNone;
    BOOL _allowAddServer;
    BOOL _allowEditServerList;
    BOOL _allowConnectionDoctor;
    BOOL _omitStatus;
    BOOL _selectedAccountIsLocked;
    BOOL _delegateWantsTableDataSourceInvocations;
    BOOL _allowAccountLocking;
    BOOL _beConservative;
    BOOL _usesOfflineStatusString;
}

- (id)initWithDelegate:(id)fp8 forAccounts:(unsigned int)fp12;
- (void)dealloc;
- (void)setDelegate:(id)fp8;
- (void)_synchronizePopUpWithSelectedAccount;
- (void)observeValueForKeyPath:(id)fp8 ofObject:(id)fp12 change:(id)fp16 context:(void *)fp20;
- (id)displayStringWithOfflineStatus:(id)fp8 ofAccount:(id)fp12;
- (void)refresh;
- (void)enable;
- (void)disable;
- (void)configurePopUpButton:(id)fp8;
- (float)popUpSizeToFitWidth:(id)fp8;
- (int)numberOfItemsInMenu:(id)fp8;
- (unsigned int)menuItemIndexOfAccount:(id)fp8;
- (BOOL)menu:(id)fp8 updateItem:(id)fp12 atIndex:(int)fp16 shouldCancel:(BOOL)fp20;
- (id)_configureMenuItem:(id)fp8 forAccount:(id)fp12;
- (void)_popUpButtonWillPopUp:(id)fp8;
- (void)_selectAccount:(id)fp8;
- (void)showConnectionDoctor:(id)fp8;
- (void)addServer:(id)fp8;
- (void)editServerList:(id)fp8;
- (void)toggleAccountLock:(id)fp8;
- (void)configureTable:(id)fp8 ispInfoField:(id)fp12 handleDoubleClick:(BOOL)fp16 useOfflineStatusString:(BOOL)fp20;
- (void)tableViewWillBecomeVisible:(id)fp8;
- (void)tableViewWillHide:(id)fp8;
- (int)numberOfRowsInTableView:(id)fp8;
- (unsigned int)tableRowIndexOfAccount:(id)fp8;
- (id)tableView:(id)fp8 objectValueForTableColumn:(id)fp12 row:(int)fp16;
- (void)tableView:(id)fp8 willDisplayCell:(id)fp12 forTableColumn:(id)fp16 row:(int)fp20;
- (void)tableViewSelectionDidChange:(id)fp8;
- (void)_removeAllIndicators:(id)fp8;
- (void)_tableViewDoubleClickAction:(id)fp8;
- (void)_willRefreshStatusForAllAccounts:(id)fp8;
- (void)_didUpdateAccountStatus:(id)fp8;
- (void)_accountInfoDidChange:(id)fp8;
- (void)_reloadAccounts;
- (void)_addUI:(id)fp8;
- (void)_removeUI:(id)fp8;
- (void)_updateUI;
- (void)_updateUIWithAccountState:(id)fp8;
- (BOOL)beConservative;
- (void)setBeConservative:(BOOL)fp8;
- (BOOL)allowAccountLocking;
- (void)setAllowAccountLocking:(BOOL)fp8;
- (BOOL)delegateWantsTableDataSourceInvocations;
- (void)setDelegateWantsTableDataSourceInvocations:(BOOL)fp8;
- (BOOL)selectedAccountIsLocked;
- (void)setSelectedAccountIsLocked:(BOOL)fp8;
- (BOOL)omitStatus;
- (void)setOmitStatus:(BOOL)fp8;
- (BOOL)allowConnectionDoctor;
- (void)setAllowConnectionDoctor:(BOOL)fp8;
- (BOOL)allowEditServerList;
- (void)setAllowEditServerList:(BOOL)fp8;
- (BOOL)allowAddServer;
- (void)setAllowAddServer:(BOOL)fp8;
- (BOOL)allowNone;
- (void)setAllowNone:(BOOL)fp8;
- (id)selectedAccount;
- (void)setSelectedAccount:(id)fp8;
- (id)accounts;
- (void)setAccounts:(id)fp8;
- (id)statusProvider;
- (void)setStatusProvider:(id)fp8;

@end

