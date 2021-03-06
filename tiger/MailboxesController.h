/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class MailboxUid, NSButton, NSMenuItem, NSMutableArray, NSMutableSet, NSPopUpButton, NSTextField, NSWindow;

@interface MailboxesController : NSObject
{
    NSMutableArray *_accountsWithChildren;
    NSWindow *_newMailboxPanel;
    NSTextField *_newMailboxField;
    NSTextField *_newMailboxMessage;
    NSButton *_newMailboxOKButton;
    NSPopUpButton *_accountPopup;
    NSMenuItem *_newMenuItem;
    id _currentMailboxSelectionOwner;
    BOOL _currentTransferIsCopy;
    MailboxUid *_selectedParent;
    MailboxUid *_currentTransferMailbox;
    BOOL smartMailboxesNeedSaving;
    BOOL isSavingSyncResults;
    int currentFileVersion;
    id _menuEnabler;
    SEL _menuEnablerSelector;
    NSMutableSet *rootMailboxMenus;
}

+ (id)filteredMailUserInfoDictionary:(id)fp8;
+ (id)iconForMailboxUid:(id)fp8 smallSize:(BOOL)fp12;
+ (id)mergeOldMailUserInfoDictionary:(id)fp8 withSyncChanges:(id)fp12;
- (void)_addItemsStartingWithMailbox:(id)fp8 toMenu:(id)fp12 withIndentationLevel:(int)fp16;
- (void)_addMailboxItemsToMenu:(id)fp8 startingFromMailbox:(id)fp12;
- (void)_addMailboxItemsToMenu:(id)fp8 startingFromMailbox:(id)fp12 includeSmartMailboxes:(BOOL)fp16;
- (void)_configureNewMailboxPanelForAccount:(id)fp8;
- (id)_menuItemForMailbox:(id)fp8;
- (void)_reloadAccountsWithChildren;
- (void)_removeAllItemsFromMenu:(id)fp8;
- (void)_setRootMailboxMenu:(id)fp8;
- (void)_synchronouslyCopyMailboxes:(id)fp8 toParent:(id)fp12 originalParent:(id)fp16;
- (void)_synchronouslyCreateNewMailboxWithName:(id)fp8 parent:(id)fp12;
- (void)_synchronouslyDeleteMailboxes:(id)fp8;
- (void)_synchronouslySetName:(id)fp8 andParent:(id)fp12 forMailboxes:(id)fp16;
- (void)accountPopupChanged:(id)fp8;
- (id)accountsWithChildren;
- (void)addMailboxItemsToMenu:(id)fp8 target:(id)fp12 action:(SEL)fp16;
- (void)addMailboxItemsToMenu:(id)fp8 target:(id)fp12 action:(SEL)fp16 includeSmartMailboxes:(BOOL)fp20;
- (void)addMailboxItemsToMenu:(id)fp8 target:(id)fp12 action:(SEL)fp16 startingAtMailbox:(id)fp20 showUnreadCounts:(BOOL)fp24;
- (void)addMailboxItemsToMenu:(id)fp8 target:(id)fp12 action:(SEL)fp16 startingAtMailbox:(id)fp20 showUnreadCounts:(BOOL)fp24 includeSmartMailboxes:(BOOL)fp28;
- (void)addSmartMailbox:(id)fp8 select:(BOOL)fp12;
- (void)addSmartMailboxFolder:(id)fp8;
- (void)awakeFromNib;
- (void)bringUpTransferMenu:(id)fp8;
- (void)cancelClicked:(id)fp8;
- (void)coalesceUnreadCountUpdate;
- (void)controlTextDidChange:(id)fp8;
- (BOOL)copyMailboxes:(id)fp8 toParentMailbox:(id)fp12;
- (BOOL)currentTransferDeletesOriginals;
- (id)currentTransferMailbox;
- (BOOL)dataWasSyncedVersion:(id)fp8 newData:(id)fp12 acceptedChanges:(id)fp16;
- (BOOL)dataWillBeSyncedVersion:(id *)fp8 data:(id *)fp12;
- (void)dealloc;
- (void)deleteMailbox:(id)fp8;
- (void)editSmartMailbox:(id)fp8;
- (void)exportMailbox:(id)fp8;
- (BOOL)fileManager:(id)fp8 shouldProceedAfterError:(id)fp12;
- (id)init;
- (void)libraryFlagsChanged:(id)fp8;
- (void)libraryMessagesAdded:(id)fp8;
- (id)loadDefaultSmartMailboxes;
- (void)mailboxListingDidChange:(id)fp8;
- (id)mailboxSelectionOwner;
- (id)mailboxSelectionOwnerFromSender:(id)fp8;
- (BOOL)menuHasKeyEquivalent:(id)fp8 forEvent:(id)fp12 target:(id *)fp16 action:(SEL *)fp20;
- (id)menuItemForMailbox:(id)fp8 target:(id)fp12 action:(SEL)fp16 showUnreadCounts:(BOOL)fp20;
- (void)menuNeedsUpdate:(id)fp8;
- (BOOL)moveAccount:(id)fp8 toAfterAccount:(id)fp12;
- (BOOL)moveMailboxes:(id)fp8 toParentMailbox:(id)fp12;
- (BOOL)moveOrCopy:(id)fp8 smartMailboxes:(id)fp12 toIndex:(unsigned int)fp16;
- (void)newFolder:(id)fp8;
- (void)newGroup:(id)fp8;
- (void)newMailbox:(id)fp8;
- (void)newMailboxSheetDidEnd:(id)fp8 returnCode:(int)fp12 contextInfo:(void *)fp16;
- (void)newSmartMailbox:(id)fp8;
- (void)nowWouldBeAGoodTimeToTerminate:(id)fp8;
- (void)okClicked:(id)fp8;
- (void)queueUnreadCountUpdate;
- (void)readDefaults;
- (id)readSmartMailboxesFromDisk;
- (void)reallyTearDownDynamicMenus;
- (BOOL)removeAccount:(id)fp8;
- (void)renameMailbox:(id)fp8;
- (void)resignMailboxSelectionOwnerFor:(id)fp8;
- (void)saveDefaults;
- (void)saveSmartMailboxes:(id)fp8;
- (void)setCopyContextMenuItem:(id)fp8;
- (void)setCopyMenuItem:(id)fp8;
- (void)setCurrentTransferMailbox:(id)fp8 deletedOriginals:(BOOL)fp12;
- (void)setMailboxSelectionOwnerFrom:(id)fp8;
- (void)setMenuEnabler:(id)fp8 selector:(SEL)fp12;
- (void)setMoveContextMenuItem:(id)fp8;
- (void)setMoveMenuItem:(id)fp8;
- (void)setSpecialMailbox:(id)fp8;
- (void)smartMailboxWasEdited:(id)fp8;
- (id)smartMailboxes;
- (id)smartMailboxesDictionaryRepresentations;
- (id)smartMailboxesDictionaryRepresentationsFilterSyncData:(BOOL)fp8;
- (id)smartMailboxesFromDictionaryRepresentations:(id)fp8;
- (id)smartMailboxesFromDictionaryRepresentations:(id)fp8 andMergeOldUserInfoFromMailboxes:(BOOL)fp12;
- (id)smartMailboxesPath;
- (void)startUnreadCountUpdateWithSequenceNumbers:(id)fp8;
- (void)syncSmartMailboxes;
- (void)tearDownDynamicMenus:(id)fp8;
- (void)tentativelyAddSmartMailbox:(id)fp8;
- (void)updateUnreadCountsForSequenceNumber:(id)fp8 librarySequenceNumber:(id)fp12;
- (void)userEditedMailboxName:(id)fp8;
- (BOOL)validateMenuItem:(id)fp8;
- (void)writeSmartMailboxesToDisk;

@end

