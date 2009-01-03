/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import <Message/Account.h>

@class MFError, MailboxUid, NSString;

@interface MailAccount : Account
{
    NSString *_path;
    MailboxUid *_rootMailboxUid;
    struct {
        unsigned int cacheDirtyCount:16;
        unsigned int backgroundFetchInProgress:1;
        unsigned int synchronizationThreadIsRunning:1;
        unsigned int cacheHasBeenRead:1;
        unsigned int disableCacheWrite:1;
        unsigned int _UNUSED_:12;
    } _flags;
    MailboxUid *_inboxMailboxUid;
    MailboxUid *_draftsMailboxUid;
    MailboxUid *_sentMessagesMailboxUid;
    MailboxUid *_trashMailboxUid;
    MailboxUid *_junkMailboxUid;
    MailboxUid *_notesMailboxUid;
    MailboxUid *_notesSmartMailboxUid;
    MailboxUid *_todosMailboxUid;
    MFError *_lastConnectionError;
}

+ (void)initialize;
+ (BOOL)haveAccountsBeenConfigured;
+ (void)_addAccountToSortedPaths:(id)fp8;
+ (id)defaultToDoAccount;
+ (id)defaultNoteAccount;
+ (BOOL)isValidAccount:(id)fp8 messageType:(int)fp12;
+ (id)singleRemoteNoteAccount;
+ (id)noteAccountForMailboxUid:(id)fp8;
+ (id)accountForNote:(id)fp8 referringMessage:(id)fp12 messageType:(int)fp16;
+ (id)todoAccountFromNoteAccount:(id)fp8;
+ (id)noteAccountForNote:(id)fp8 referringMessage:(id)fp12;
+ (id)todoAccountForNote:(id)fp8 referringMessage:(id)fp12;
+ (id)mailAccounts;
+ (id)syncableMailAccounts;
+ (id)allCalDAVAccounts;
+ (void)setMailAccounts:(id)fp8;
+ (void)accountsWereSynced;
+ (BOOL)newMailBeenReceived;
+ (void)setNewMailBeenReceived:(BOOL)fp8;
+ (id)syncMailAccountWithDictionary:(id)fp8 somethingChanged:(char *)fp12 initialSync:(BOOL)fp16;
+ (void)_removeAccountFromSortedPaths:(id)fp8;
+ (id)activeAccounts;
+ (id)remoteAccounts;
+ (void)saveAccountInfoToDefaults;
+ (id)accountWithUniqueId:(id)fp8;
+ (id)existingAccountWithType:(id)fp8 hostname:(id)fp12 username:(id)fp16;
+ (id)allEmailAddressesIncludingFullUserName:(BOOL)fp8;
+ (void)updateAccountExistsForSigning;
+ (BOOL)accountExistsForSigning;
+ (id)_accountContainingEmailAddress:(id)fp8 matchingAddress:(id *)fp12 fullUserName:(id *)fp16;
+ (id)accountContainingEmailAddress:(id)fp8;
+ (id)accountForHeaders:(id)fp8 message:(id)fp12;
+ (id)accountUsingHeadersFromMessage:(id)fp8;
+ (id)accountThatMessageIsFrom:(id)fp8;
+ (id)addressesThatReceivedMessage:(id)fp8;
+ (id)accountThatReceivedMessage:(id)fp8 matchingEmailAddress:(id *)fp12 fullUserName:(id *)fp16;
+ (id)outboxMessageStore:(BOOL)fp8;
+ (id)specialMailboxUids;
+ (id)_specialMailboxUidsUsingSelector:(SEL)fp8;
+ (id)inboxMailboxUids;
+ (id)trashMailboxUids;
+ (id)outboxMailboxUids;
+ (id)sentMessagesMailboxUids;
+ (id)draftMailboxUids;
+ (id)junkMailboxUids;
+ (id)noteMailboxUids;
+ (id)allNoteMailboxUids;
+ (id)todosMailboxUids;
+ (id)allMailboxUids;
+ (id)accountWithPath:(id)fp8;
+ (id)newAccountWithPath:(id)fp8;
+ (id)createAccountWithDictionary:(id)fp8;
+ (id)defaultPathForAccountWithHostname:(id)fp8 username:(id)fp12;
+ (id)defaultAccountDirectory;
+ (id)defaultPathNameForAccount;
+ (id)defaultPathNameForAccountWithHostname:(id)fp8 username:(id)fp12;
+ (id)defaultDeliveryAccount;
+ (BOOL)isAnyAccountOffline;
+ (BOOL)isAnyAccountOnline;
+ (void)_setOnlineStateOfAllAccountsTo:(BOOL)fp8;
+ (void)disconnectAllAccounts;
+ (void)connectAllAccounts;
+ (void)saveStateForAllAccounts;
+ (void)_clearAllAccountBackgroundFetchInProgress;
+ (int)numberOfDaysToKeepLocalTrash;
+ (BOOL)allAccountsDeleteInPlace;
+ (void)synchronouslyEmptyMailboxUidType:(int)fp8 inAccounts:(id)fp12;
+ (void)resetAllSpecialMailboxes;
+ (id)mailboxUidForFileSystemPath:(id)fp8 create:(BOOL)fp12;
+ (void)deleteMailboxUidIfEmpty:(id)fp8;
+ (id)_accountForURL:(id)fp8 includeInactiveAccounts:(BOOL)fp12;
+ (id)_accountForURL:(id)fp8;
+ (id)infoForURL:(id)fp8;
+ (id)URLForInfo:(id)fp8;
+ (id)accountWithURLString:(id)fp8;
+ (id)accountWithURLString:(id)fp8 includeInactiveAccounts:(BOOL)fp12;
+ (id)mailboxUidForURL:(id)fp8 forceCreation:(BOOL)fp12;
+ (id)mailboxUidForURL:(id)fp8;
+ (id)mailboxUidForMailboxID:(unsigned int)fp8;
+ (void)renameMailboxesUsingDefaultSecurePorts;
- (BOOL)isValidAccountWithError:(id)fp8 accountBeingEdited:(id)fp12 userCanOverride:(char *)fp16;
- (BOOL)cheapStoreAtPathIsEmpty:(id)fp8;
- (id)init;
- (id)initWithPath:(id)fp8;
- (void)dealloc;
- (void)heal;
- (BOOL)isValid;
- (void)finalize;
- (void)_updateSpecialMailboxForType:(int)fp8 fromSyncedDictionary:(id)fp12;
- (void)updateFromSyncedDictionary:(id)fp8;
- (id)path;
- (void)setPath:(id)fp8;
- (id)tildeAbbreviatedPath;
- (id)applescriptFullUserName;
- (void)setApplescriptFullUserName:(id)fp8;
- (id)fullUserName;
- (void)setFullUserName:(id)fp8;
- (id)localizedDeliveryAccount;
- (id)smtpIdentifier;
- (id)deliveryAccount;
- (void)setDeliveryAccount:(id)fp8;
- (void)deliveryAccountWillBeRemoved:(id)fp8;
- (BOOL)deliveryAccountIsLocked;
- (void)setDeliveryAccountIsLocked:(BOOL)fp8;
- (BOOL)isDotMacAccount;
- (id)firstEmailAddress;
- (id)rawEmailAddresses;
- (id)emailAddresses;
- (id)applescriptEmailAddresses;
- (void)setApplescriptEmailAddresses:(id)fp8;
- (void)setEmailAddresses:(id)fp8;
- (id)emailAliases;
- (id)emailAliasesLastSyncDate;
- (void)setEmailAliases:(id)fp8 syncDate:(id)fp12;
- (BOOL)shouldAutoFetch;
- (void)setShouldAutoFetch:(BOOL)fp8;
- (BOOL)fileManager:(id)fp8 shouldProceedAfterError:(id)fp12;
- (void)_synchronouslyInvalidateAndDelete:(BOOL)fp8;
- (void)deleteAccount;
- (void)saveState;
- (void)doRoutineCleanup;
- (void)releaseAllConnections;
- (void)setIsOffline:(BOOL)fp8;
- (void)setIsWillingToGoOnline:(BOOL)fp8;
- (BOOL)canFetch;
- (id)defaultsDictionary;
- (void)nowWouldBeAGoodTimeToStartBackgroundSynchronization;
- (BOOL)canAppendMessages;
- (BOOL)canBeSynchronized;
- (void)synchronizeAllMailboxes;
- (void)fetchAsynchronouslyIsAuto:(BOOL)fp8;
- (void)fetchAsynchronously;
- (void)fetchSynchronously;
- (void)fetchSynchronouslyIsAuto:(id)fp8;
- (BOOL)isFetching;
- (void)newMailHasBeenReceived;
- (id)primaryMailboxUid;
- (id)rootMailboxUid;
- (BOOL)rootChildrenCanBePromoted;
- (id)draftsMailboxUidCreateIfNeeded:(BOOL)fp8;
- (id)junkMailboxUidCreateIfNeeded:(BOOL)fp8;
- (id)sentMessagesMailboxUidCreateIfNeeded:(BOOL)fp8;
- (id)trashMailboxUidCreateIfNeeded:(BOOL)fp8;
- (id)createNoteSmartMailboxUid;
- (id)smartNotesMailboxUidCreateIfNeeded:(BOOL)fp8;
- (void)setSmartNotesMailboxUid:(id)fp8;
- (id)simpleNotesMailboxUidCreateIfNeeded:(BOOL)fp8;
- (id)simpleOrSmartNotesMailboxUidCreateIfNeeded:(BOOL)fp8;
- (id)notesMailboxUidCreateIfNeeded:(BOOL)fp8;
- (id)todosMailboxUidCreateIfNeeded:(BOOL)fp8;
- (id)allMailboxUids;
- (void)setDraftsMailboxUid:(id)fp8;
- (void)setTrashMailboxUid:(id)fp8;
- (void)setJunkMailboxUid:(id)fp8;
- (void)setSentMessagesMailboxUid:(id)fp8;
- (void)setNotesMailboxUid:(id)fp8;
- (void)setToDosMailboxUid:(id)fp8;
- (void)deleteMessagesFromMailboxUid:(id)fp8 olderThanNumberOfDays:(unsigned int)fp12;
- (void)_setEmptyFrequency:(int)fp8 forKey:(id)fp12;
- (int)_emptyFrequencyForKey:(id)fp8 defaultValue:(id)fp12;
- (int)emptySentMessagesFrequency;
- (void)setEmptySentMessagesFrequency:(int)fp8;
- (int)emptyJunkFrequency;
- (void)setEmptyJunkFrequency:(int)fp8;
- (id)lastToDoCalendar;
- (void)setLastToDoCalendar:(id)fp8;
- (void)todoCalendarGroupTitle:(id *)fp8 groupID:(id *)fp12;
- (void)setToDoCalendarGroupTitle:(id)fp8 groupID:(id)fp12;
- (void)deleteToDoCalendarGroup;
- (int)emptyTrashFrequency;
- (void)setEmptyTrashFrequency:(int)fp8;
- (BOOL)shouldMoveDeletedMessagesToTrash;
- (void)setShouldMoveDeletedMessagesToTrash:(BOOL)fp8;
- (BOOL)canMoveDeletedMessagesToTrash;
- (BOOL)shouldStoreNotesInInbox;
- (void)setShouldStoreNotesInInbox:(BOOL)fp8;
- (void)emptySpecialMailboxesThatNeedToBeEmptiedAtQuit;
- (id)displayName;
- (id)displayNameForMailboxUid:(id)fp8;
- (BOOL)containsMailboxes;
- (BOOL)_resetSpecialMailboxes;
- (void)resetSpecialMailboxes;
- (id)mailboxPathExtension;
- (BOOL)canCreateNewMailboxes;
- (BOOL)newMailboxNameIsAcceptable:(id)fp8 reasonForFailure:(id *)fp12;
- (BOOL)canMailboxBeRenamed:(id)fp8;
- (BOOL)canMailboxBeDeleted:(id)fp8;
- (id)createMailboxWithParent:(id)fp8 name:(id)fp12;
- (id)createMailboxWithParent:(id)fp8 name:(id)fp12 displayName:(id)fp16;
- (BOOL)renameMailbox:(id)fp8 newName:(id)fp12 parent:(id)fp16;
- (BOOL)deleteMailbox:(id)fp8;
- (void)_resetAllMailboxURLs;
- (void)setUsername:(id)fp8;
- (void)setHostname:(id)fp8;
- (void)setPortNumber:(unsigned int)fp8;
- (void)accountInfoDidChange;
- (void)postUserInfoHasChangedForMailboxUid:(id)fp8 userInfo:(id)fp12;
- (void)setConnectionError:(id)fp8;
- (id)connectionError;
- (id)_guessedISPAccountDictionary;
- (id)storeForMailboxUid:(id)fp8;
- (Class)storeClass;
- (Class)todoStoreClass;
- (void)setUnreadCount:(unsigned int)fp8 forMailbox:(id)fp12;
- (BOOL)hasUnreadMail;
- (id)mailboxUidForRelativePath:(id)fp8 create:(BOOL)fp12;
- (id)valueInMailboxesWithName:(id)fp8;
- (id)objectSpecifierForMessageStore:(id)fp8;
- (id)objectSpecifierForMailboxUid:(id)fp8;
- (id)objectSpecifier;
- (id)URLString;
- (BOOL)synchronizesDataWithServer;
- (Class)reconciliationAgentClass;
- (BOOL)supportsNotes;
- (BOOL)supportsToDos;
- (BOOL)canStoreToDos;
- (id)todoCalendarsAccount;
- (BOOL)allowsCalendarCreation;
- (BOOL)isEditableByUser;
- (BOOL)canParticipateInRules;
- (BOOL)providesAccountInformation;
- (BOOL)isZeroConfiguration;
- (BOOL)isRemoteAccount;
- (BOOL)hasTrashMailbox;
- (BOOL)supportsAppleScript;
- (BOOL)isSourceOfToDosTruth;
- (id)currentToDosMailboxName;
- (void)setCurrentToDosMailboxName:(id)fp8;

@end

