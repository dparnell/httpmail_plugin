#import <cocoa/cocoa.h>

#import "mail-api-10.3.h"
#import "NSPreferences.h"

@interface MVMailBundle:NSObject
{
}

+ allBundles;
+ composeAccessoryViewOwners;
+ (void)registerBundle;
+ sharedInstance;
+ (BOOL)hasPreferencesPanel;
+ preferencesOwnerClassName;
+ preferencesPanelName;
+ (BOOL)hasComposeAccessoryViewOwner;
+ composeAccessoryViewOwnerClassName;
- (void)dealloc;
- (void)_registerBundleForNotifications;

@end


@interface AccountDetails:NSObject
{
    NSView *_detailView;
    NSButton *_enableAccountCheckbox;
    NSTextField *_directory;
    NSButton *_chooseDirectoryButton;
    NSTextField *_portNumberField;
    NSButton *_autoFetch;
    NSButton *_sslSwitch;
    NSPopUpButton *_authenticationPopup;
    NSPopUpButton *_sentMessagesAgePopup;
    NSPopUpButton *_junkAgePopup;
    NSPopUpButton *_trashAgePopup;
    NSButton *_trashCheckbox;
    MailAccount *_account;
    AuthScheme *_authScheme;
}

+ accountDetailsForAccountClassNamed:fp12;
+ accountDetailsNibName;
- (void)dealloc;
- (Class)accountClass;
- (void)setupAccountFromValuesInUI:fp12 forValidation:(char)fp16;
- (void)setupUIFromValuesInAccount:fp12;
- detailView;
- (void)setupAccountFromValuesInSpecialMailboxesUI:fp12;
- (void)setupSpecialMailboxesUI:fp12 fromValuesInAccount:fp16;
- (void)didDisplayTabViewItem:fp12;
- (void)openAccountPathDialog:fp12;
- (void)accountPathDialogDidEnd:fp12 returnCode:(int)fp16 contextInfo:(void *)fp20;
- accountPath;
- (void)setAccountPath:fp12;
- (char)validateValuesInUIOfWindow:fp12;
- (char)userWantsAccountActive;
- (void)sslChanged:fp12;
- (void)authenticationChanged:fp12;
- (char)allowsServerBasedSpecialMailboxes;
- (void)moveToTrashClicked:fp12;
- (void)accountDetailsSheetDidEnd:(int)fp12;

@end

@interface IMAPAccountDetails:AccountDetails
{
    NSButton *_compactWhenClosing;
    NSPopUpButton *_messageCaching;
    NSTextField *_serverPathPrefix;
    NSButton *_overaggressiveCaching;
    char warnedAboutCachingAndIndexing;
    NSButton *_keepDraftsOnServer;
    NSButton *_keepSentMessagesOnServer;
    NSButton *_keepTrashOnServer;
    NSButton *_keepJunkOnServer;
}

- (Class)accountClass;
- (char)allowsServerBasedSpecialMailboxes;
- (void)setupUIFromValuesInAccount:fp8;
- (void)setupAccountFromValuesInUI:fp8 forValidation:(char)fp12;
- (void)setupAccountFromValuesInSpecialMailboxesUI:fp8;
- (void)setUIElementsEnabled:(char)fp8;
- (BOOL)isAccountInformationDirty:(MailAccount*)account;
- (void)setupSpecialMailboxesUI:fp8 fromValuesInAccount:fp12;
- (void)didDisplayTabViewItem:fp8;
- (void)cachePolicyChanged:fp8;
- (void)moveToTrashClicked:fp8;

@end

@interface AccountPreferences:NSPreferencesModule
{
    NSMutableArray *_accounts;
    AccountDetails *_accountDetails;
    NSTabView *detailTabView;
    NSBox *accountDetailsBox;
    NSPanel *accountDetailPanel;
    NSTableView *accountsTable;
    NSButton *removeAccountButton;
    NSButton *editAccountButton;
    NSPopUpButton *accountTypePopup;
    NSTextField *accountTypeString;
    NSTextField *accountName;
    NSTextField *fullNameField;
    NSTextField *emailAddressField;
    NSTextField *username;
    NSTextField *hostname;
    NSTextField *password;
    NSPopUpButton *smtpAccountPopup;
    NSButton *deliveryOptionsButton;
    NSButton *removeDeliveryAccountButton;
    NSTableView *deliveryAccountsTable;
    NSPanel *editDeliveryAccountPanel;
    NSView *localSpecialMailboxesView;
    NSView *imapSpecialMailboxesView;
    NSView *outlookWebAccessView;
    NSTextField *outlookWebAccessServerName;
    MailAccount *_accountBeingEdited;
    MailAccount *_accountBeingValidated;
}

+ (void)addAccountType:fp12 className:fp16;
+ (char)_exchangeAccountExists;
- titleForIdentifier:fp12;
- (void)awakeFromNib;
- (void)accountsDidChange:fp12;
- (void)initializeFromDefaults;
- (void)_saveAccountInfo;
- (void)toggleAccountEnabled:fp12;
- (void)toggleIncludeWhenCheckingForNewMail:fp12;
- (char)validateMenuItem:fp12;
- (void)createNewAccount:fp12;
- (void)editAccount:fp12;
- (void)editMailAccount:fp12;
- (void)removeAccountSheetDidEnd:fp12 returnCode:(int)fp16 account:fp20;
- (void)removeAccount:fp12;
- (void)_reloadDeliveryAccountPopup:fp12;
- (void)_setupUIForAccountBeingEdited;
- (void)_runAccountDetailPanelForAccount:fp12;
- (void)_accountDetailSheetDidEnd:fp12 returnCode:(int)fp16 contextInfo:(void *)fp20;
- (void)tabView:fp12 didSelectTabViewItem:fp16;
- (void)_setupAccountFromValuesInUI:fp12 forValidation:(char)fp16;
- _accountClassNameOfSelectedItemInAccountTypePopup;
- (void)_updateAccountTypePopup;
- (void)okClicked:fp12;
- (void)cancelClicked:fp12;
- (void)accountTypeChanged:fp12;
- _accountsCurrentlyUsingDeliveryAccount:fp12;
- (void)changeDeliveryOptions:fp12;
- (void)addDeliveryAccount:fp12;
- (void)editDeliveryAccountList:fp12;
- (void)removeDeliveryAccount:fp12;
- (void)doneEditingDeliveryAccountList:fp12;
- (int)numberOfRowsInTableView:fp12;
- tableView:fp12 objectValueForTableColumn:fp16 row:(int)fp20;
- (void)tableViewSelectionDidChange:fp12;
- (char)tableView:fp12 writeRows:fp16 toPasteboard:fp20;
- (unsigned int)tableView:fp12 validateDrop:fp16 proposedRow:(int)fp20 proposedDropOperation:(int)fp24;
- (char)tableView:fp12 acceptDrop:fp16 row:(int)fp20 dropOperation:(int)fp24;

@end

@interface MailApp:NSApplication
{
    id selectionOwner;
    NSMenu *_mailboxesDrawerContextMenu;
    NSMenu *_messageViewerContextMenu;
    NSMenu *_composeAttachmentContextMenu;
    NSMenu *_viewAttachmentContextMenu;
    NSMenuItem *textEncodingMenuItem;
    id mailboxesController;
    NSSound *_newMailSound;
    NSSound *_noMailSound;
    NSSound *_fetchErrorSound;
    NSImage *unbadgedApplicationImage;
    NSPanel *_selectMailboxPanel;
    id _selectMailboxChooser;
    id _deliveryQueue;
    id _activityViewer;
    NSMutableArray *_terminationHandlers;
    int _autoLaunchHidden:1;
    int _mainThreadIsBusy:1;
    int _shouldPlayNoMailSound:1;
    int _shouldPlayFetchErrorSound:1;
    int _appHasFinishedLaunching:1;
    int _synchronizingAllAccounts:1;
    int _groupingByThreadDefaultsToOn:1;
    int _terminateReply:4;
    int _currentHandlerIndex:24;
    NSMutableSet *_accountsCurrentlySynchronizing;
    int numberOfAccountsEmptyingTrash;
    int currentPasswordPanelCount;
    NSMutableDictionary *_composeMessages;
}

+ (void)_forceClassInitialization;
- init;
- (void)awakeFromNib;
- (void)presencePreferenceChanged:fp12;
- (void)setAppImageForUnreadCount:(int)fp12;
- (void)_unreadCountChanged:fp12;
- (void)_accountInfoDidChange:fp12;
- (char)applicationOpenUntitledFile:fp12;
- (void)configurePerformanceLoggingDefaults;
- (void)_systemTimeChanged;
- (void)_midnightPassed;
- (void)_setupMidnightTimer;
- (void)_checkTimerAndFireDate:fp12;
- (void)sendEvent:fp12;
- (void)_setupMenus;
- (void)performDelayedInitialization;
- (void)applicationDidFinishLaunching:fp12;
- (void)_restoreMessagesFromDefaults;
- (void)_setupInitialState;
- (int)_loadBundlesFromPath:fp12;
- (void)_loadBundles;
- _mailboxBeingViewed;
- _accountBeingViewed;
- _selectedMailboxes;
- (char)validateToolbarItem:fp12;
- (char)validateMenuItem:fp12;
- (void)disconnectAllAccounts:fp12;
- (void)connectAllAccounts:fp12;
- (void)connectThisAccount:fp12;
- (void)disconnectThisAccount:fp12;
- (void)toggleAccountOnlineStatus:fp12;
- (void)performSynchronizationForAccounts:fp12;
- (void)synchronizeAccount:fp12;
- (void)_networkConfigurationChanged:fp12;
- (void)showInfoPanel:fp12;
- (void)showComposeWindow:fp12;
- (void)showViewerWindow:fp12;
- (void)showAddressPanel:fp12;
- (void)showAddressHistoryPanel:fp12;
- (void)showSearchPanel:fp12;
- (void)findNext:fp12;
- (void)findPrevious:fp12;
- (void)showActivityViewer:fp12;
- (void)showPreferencesPanel:fp12;
- (void)changeAddressDisplayMode:fp12;
- (void)importMailboxes:fp12;
- (void)showReleaseNotes:fp12;
- (void)alwaysSendWindowsFriendlyAttachments:fp12;
- (void)sendWindowsFriendlyAttachments:fp12;
- (void)insertOriginalAttachments:fp12;
- (void)_resetMenuItemWithTag:(int)fp12;
- _getMenuItemInMessageMenuWithTag:(int)fp12;
- (void)_synchronizeAccountListMenuWithTagIfNeeded:(int)fp12;
- (void)bringUpOnlineOfflineMenu:fp12;
- (void)bringUpSynchronizeAccountMenu:fp12;
- (void)bringUpEmptyTrashMenu:fp12;
- (void)bringUpGetNewMailMenu:fp12;
- (void)_removeAllItemsInAccountMenuWithTag:(int)fp12;
- (void)accountsChanged:fp12;
- (void)editAccount:fp12;
- (void)_emptyTrashInAccounts:fp12;
- (void)emptyTrashInAccount:fp12;
- (void)compactSelectedMailboxes:fp12;
- (void)toggleSmallIconsInDrawer:fp12;
- (void)showJunkMailInfoPanel;
- (void)showJunkMailInfoPanelIfNeeded;
- (void)_evaluateUsersJunkMailNeeds;
- (void)showToolbarItemForJunkMail:(char)fp12;
- (void)eraseJunkMail:fp12;
- (void)toggleThreadedMode:fp12;
- (char)groupingByThreadDefaultsToOn;
- (void)setGroupingByThreadDefaultsToOn:(char)fp12;
- (char)shouldAutoFetch;
- (void)setShouldAutoFetch:(char)fp12;
- (int)autoFetchFrequency;
- (void)setAutoFetchFrequency:(int)fp12;
- (void)_checkNewMail:(char)fp12;
- (void)checkNewMailInAccount:fp12;
- (void)checkNewMail:fp12;
- (void)checkNewMailInSelectedAccount:fp12;
- (void)autoFetchMail:fp12;
- (void)markAllMessagesAsReadInMailbox:fp12;
- (void)markAllAsRead:fp12;
- (void)backgroundFetchCompleted:fp12;
- (void)resetAutoFetchTimer;
- (void)fetchErrorHasOccurred;
- (char)application:fp12 openFile:fp16;
- (void)applicationDidUnhide:fp12;
- openStoreWithMailboxUid:fp12;
- openStoreWithMailboxUid:fp12 andMakeKey:(char)fp16;
- (Class)messageEditorClass;
- messageEditor;
- (void)addressManagerLoaded;
- activityViewer;
- textEncodingMenuItem;
- mailboxesDrawerContextMenu;
- messageViewerContextMenu;
- viewAttachmentContextMenu;
- composeAttachmentContextMenu;
- mailboxesController;
- (void)preferencesChanged:fp12;
- (void)handleGURLAppleEvent:fp12;
- (char)handleMailToURL:fp12;
- (char)handleClickOnURL:fp12;
- applicationVersion;
- frameworkVersion;
- (void)mailDocument:fp12;
- (void)mailAttributedString:fp12;
- (void)mailSelection:fp12 userData:fp16 error:(id *)fp20;
- (void)mailDocument:fp12 userData:fp16 error:(id *)fp20;
- (void)mailTo:fp12 userData:fp16 error:(id *)fp20;
- deliveryQueue;
- (void)setSelectionFrom:fp12;
- (void)resignSelectionFor:fp12;
- selection;
- selectionOwner;
- preferredReplyAddressBasedOnCurrentSelection;
- (char)applicationShouldHandleReopen:fp12 hasVisibleWindows:(char)fp16;
- (void)terminateNoConfirm;
- (void)cleanup;
- (void)_approveQuitIfFinished;
- (void)_cleanupFinished;
- (void)cleanUpAccount:fp12;
- (int)applicationShouldTerminate:fp12;
- (void)nowWouldBeAGoodTimeToTerminate:fp12;
- (void)applicationWillTerminate:fp12;
- (void)addTerminationHandler:fp12;
- (void)removeTerminationHandler:fp12;
- (void)handler:fp12 approvedQuit:(char)fp16;

@end

@interface MailApp(ApplescriptAccountPreferences)
- (void)_insertInAccounts:fp8 atIndex:(unsigned int)fp12;
- (void)insertInAccounts:fp8 atIndex:(unsigned int)fp12;
- (void)insertInAccounts:fp8;
- (void)insertInIToolsAccounts:fp8 atIndex:(unsigned int)fp12;
- (void)insertInIToolsAccounts:fp8;
- (void)insertInImapAccounts:fp8 atIndex:(unsigned int)fp12;
- (void)insertInImapAccounts:fp8;
- (void)insertInPopAccounts:fp8 atIndex:(unsigned int)fp12;
- (void)insertInPopAccounts:fp8;
- (void)removeFromAccountsAtIndex:(unsigned int)fp8;
- deliveryAccounts;
@end

@interface MailApp(MFUserAgent)
- (void)_runPasswordPanelInMainThreadWithInfo:(struct MailPasswordInfo *)fp8;
- queryUserForPasswordWithMessage:fp8 title:fp12 remember:(char *)fp16;
- (void)_runAlertPanelInMainThreadWithInfo:(struct MailAlertInfo *)fp8;
- (int)runAlertPanelWithTitle:fp8 defaultTitle:fp12 alternateTitle:fp16 otherTitle:fp20 message:fp24;
- (void)runNonModalAlertPanelForObject:fp8 withError:fp12;
- (void)dismissNonModalAlertPanelForObject:fp8;
- (int)informUserOfError:fp8;
- (char)queryUserForYesNoWithMessage:fp8 title:fp12 yesTitle:fp16 noTitle:fp20;
- (char)showCertificateTrustPanelForError:fp8 certificates:fp12;
- displayStringForMailbox:fp8;
- (char)queryUserIfNeededToCreateMailbox:fp8 orChooseNewMailbox:(id *)fp12;
- queryUserToSelectMailbox:fp8;
- (void)selectMailboxPanelDone:fp8;
- (void)queryUserForBigMessageAction:fp8 userResponse:(int *)fp12;
- (void)downloadBigMessage:fp8;
- (void)storeBeingInvalidated:fp8;
- (void)showThreadIsBusy;
- (void)doneBeingBusy;
- (char)shouldInvalidateMailbox:fp8;
- (char)isMainThreadBusy;
- sharedAttachmentContextMenu;
- (char)isTerminating;
- (char)wakingFromSleep;
- presenceOfEmail:fp8;
- (char)messageIsMemberOfNonJunkThread:fp8;
@end

@interface NonModalAlert:NSObject
{
    id _representedObject;
    NSPanel *_panel;
    NSTextField *_title;
    NSTextField *_message;
}

+ (void)runNonModalForObject:fp8 error:fp12;
+ (void)dismissNonModalAlertForObject:fp8;
- (void)dealloc;
- initWithError:fp8 representedObject:fp12;
- (void)show;
- representedObject;
- (void)okClicked:fp8;

@end

@interface NSObject(NonModalAlertPanel)
- (void)runNonModalAlertWithError:fp8;
- (void)dismissNonModalAlert;
@end

