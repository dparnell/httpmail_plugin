#import <cocoa/cocoa.h>

@class MailAccount;
@class AuthScheme;
@class MessageStore;
@class MailboxUid;
@class MessageHeaders;

@interface Account:NSObject
{
    NSMutableDictionary *_info;
    int _isOffline:1;
    int _willingToGoOnline:1;
    int _autosynchronizingEnabled:1;
    int _ignoreSSLCertificates:1;
    int _promptedToIgnoreSSLCertificates:1;
}

+ (void)initialize;
+ (char)haveAccountsBeenConfigured;
+ readAccountsUsingDefaultsKey:fp8;
+ (void)saveAccounts:fp8 usingDefaultsKey:fp12;
+ (void)saveAccountInfoToDefaults;
+ createAccountWithDictionary:fp8;
+ accountTypeString;
+ (char)allObjectsInArrayAreOffline:fp8;
- init;
- (void)dealloc;
- (void)setAutosynchronizingEnabled:(char)fp8;
- (void)_queueAccountInfoDidChange;
- accountInfo;
- (void)_setAccountInfo:fp8;
- (void)setAccountInfo:fp8;
- defaultsDictionary;
- (char)isActive;
- (void)setIsActive:(char)fp8;
- (BOOL)canGoOffline;
- (char)isOffline;
- (void)setIsOffline:(char)fp8;
- (char)isWillingToGoOnline;
- (void)setIsWillingToGoOnline:(char)fp8;
- displayName;
- (void)setDisplayName:fp8;
- username;
- (void)setUsername:fp8;
- hostname;
- (void)setHostname:fp8;
- (void)setPasswordInKeychain:fp8;
- (void)_removePasswordInKeychain;
- (void)setTemporaryPassword:fp8;
- (void)setPassword:fp8;
- passwordFromStoredUserInfo;
- passwordFromKeychain;
- password;
- promptUserForPasswordWithMessage:fp8;
- promptUserIfNeededForPasswordWithMessage:fp8;
- (unsigned int)portNumber;
- (unsigned int)defaultPortNumber;
- (unsigned int)defaultSecurePortNumber;
- (void)setPortNumber:(unsigned int)fp8;
- serviceName;
- secureServiceName;
- (void)releaseAllConnections;
- (void)validateConnections;
- (char)usesSSL;
- (void)setUsesSSL:(char)fp8;
- sslProtocolVersion;
- (void)setSSLProtocolVersion:fp8;
- (void)accountInfoDidChange;
- securityProtocol;
- (void)setSecurityProcol:fp8;
- preferredAuthScheme;
- (void)setPreferredAuthScheme:fp8;
- saslProfileName;
- (Class)connectionClass;
- (BOOL)requiresAuthentication;
- authenticatedConnection;
- (char)_shouldTryDirectSSLConnectionOnPort:(unsigned int)fp8;
- (char)_shouldRetryConnectionWithoutCertificateCheckingAfterError:fp8;
- (char)_connectAndAuthenticate:fp8;
- (char)_ignoreSSLCertificates;
- (void)_setIgnoreSSLCertificates:(char)fp8;

@end

@interface Account(Applescript)
- (int)accountType;
- (void)setAccountPassword:fp8;
- accountPassword;
- (void)setServerName:fp8;
- serverName;
- (void)setLoginName:fp8;
- loginName;
- (void)setAccountName:fp8;
- accountName;
- (int)customAuthentication;
- (void)setCustomAuthentication:(int)fp8;
@end

@interface MailAccount:Account
{
    NSString *_path;
    MailboxUid *_rootMailboxUid;
    int _flags;
    MailboxUid *_inboxMailboxUid;
    MailboxUid *_draftsMailboxUid;
    MailboxUid *_sentMessagesMailboxUid;
    MailboxUid *_trashMailboxUid;
    MailboxUid *_junkMailboxUid;
    id *_lastConnectionError;
}

+ (void)initialize;
+ (char)mailboxListingNotificationAreEnabled;
+ (void)disableMailboxListingNotifications;
+ (void)enableMailboxListingNotifications;
+ (char)haveAccountsBeenConfigured;
+ (void)_addAccountToSortedPaths:fp8;
+ mailAccounts;
+ (void)setMailAccounts:fp8;
+ (void)_removeAccountFromSortedPaths:fp8;
+ activeAccounts;
+ (void)saveAccountInfoToDefaults;
+ allEmailAddressesIncludingFullUserName:(char)fp8;
+ _accountContainingEmailAddress:fp8 matchingAddress:(id *)fp12 fullUserName:(id *)fp16;
+ accountContainingEmailAddress:fp8;
+ accountThatMessageIsFrom:fp8;
+ accountThatReceivedMessage:fp8 matchingEmailAddress:(id *)fp12 fullUserName:(id *)fp16;
+ outboxMessageStore:(char)fp8;
+ specialMailboxUids;
+ _specialMailboxUidsUsingSelector:(SEL)fp8;
+ inboxMailboxUids;
+ trashMailboxUids;
+ outboxMailboxUids;
+ sentMessagesMailboxUids;
+ draftMailboxUids;
+ junkMailboxUids;
+ allMailboxUids;
+ accountWithPath:fp8;
+ newAccountWithPath:fp8;
+ createAccountWithDictionary:fp8;
+ defaultPathForAccountWithHostname:fp8 username:fp12;
+ defaultAccountDirectory;
+ defaultPathNameForAccountWithHostname:fp8 username:fp12;
+ defaultDeliveryAccount;
+ (char)isAnyAccountOffline;
+ (char)isAnyAccountOnline;
+ (void)_setOnlineStateOfAllAccountsTo:(char)fp8;
+ (void)disconnectAllAccounts;
+ (void)connectAllAccounts;
+ (void)saveStateForAllAccounts;
+ (int)numberOfDaysToKeepLocalTrash;
+ (char)allAccountsDeleteInPlace;
+ (void)synchronouslyEmptyMailboxUidType:(int)fp8 inAccounts:fp12;
+ (void)resetAllSpecialMailboxes;
+ mailboxUidForFileSystemPath:fp8 create:(char)fp12;
+ (void)deleteMailboxUidIfEmpty:fp8;
- (void)synchronizeMailboxListAfterImport;
- (char)isValidAccountWithError:fp8 accountBeingEdited:fp12 userCanOverride:(char *)fp16;
- (char)cheapStoreAtPathIsEmpty:fp8;
- init;
- initWithPath:fp8;
- (void)dealloc;
- path;
- (void)setPath:fp8;
- tildeAbbreviatedPath;
- applescriptFullUserName;
- (void)setApplescriptFullUserName:fp8;
- fullUserName;
- (void)setFullUserName:fp8;
- deliveryAccount;
- (void)setDeliveryAccount:fp8;
- (void)deliveryAccountWillBeRemoved:fp8;
- firstEmailAddress;
- rawEmailAddresses;
- emailAddresses;
- applescriptEmailAddresses;
- (void)setApplescriptEmailAddresses:fp8;
- (void)setEmailAddresses:fp8;
- (char)shouldAutoFetch;
- (void)setShouldAutoFetch:(char)fp8;
- (char)fileManager:fp8 shouldProceedAfterError:fp12;
- (void)_synchronouslyInvalidateAndDelete:(char)fp8;
- (void)deleteAccount;
- (void)saveState;
- (void)releaseAllConnections;
- (void)setIsOffline:(char)fp8;
- (void)setIsWillingToGoOnline:(char)fp8;
- (BOOL)canFetch;
- defaultsDictionary;
- (void)nowWouldBeAGoodTimeToStartBackgroundSynchronization;
- (char)canAppendMessages;
- (char)canBeSynchronized;
- (void)synchronizeAllMailboxes;
- (void)fetchAsynchronously;
- (void)fetchSynchronously;
- (char)isFetching;
- (void)newMailHasBeenReceived;
- primaryMailboxUid;
- rootMailboxUid;
- draftsMailboxUidCreateIfNeeded:(char)fp8;
- junkMailboxUidCreateIfNeeded:(char)fp8;
- sentMessagesMailboxUidCreateIfNeeded:(char)fp8;
- trashMailboxUidCreateIfNeeded:(char)fp8;
- allMailboxUids;
- (void)setDraftsMailboxUid:fp8;
- (void)setTrashMailboxUid:fp8;
- (void)setJunkMailboxUid:fp8;
- (void)setSentMessagesMailboxUid:fp8;
- (void)deleteMessagesFromMailboxUid:(MailboxUid*)mailbox olderThanNumberOfDays:(unsigned int)fp12 compact:(BOOL)fp16;
- (void)_setEmptyFrequency:(int)fp8 forKey:fp12;
- (int)_emptyFrequencyForKey:fp8 defaultValue:fp12;
- (int)emptySentMessagesFrequency;
- (void)setEmptySentMessagesFrequency:(int)fp8;
- (int)emptyJunkFrequency;
- (void)setEmptyJunkFrequency:(int)fp8;
- (int)emptyTrashFrequency;
- (void)setEmptyTrashFrequency:(int)fp8;
- (char)shouldMoveDeletedMessagesToTrash;
- (void)setShouldMoveDeletedMessagesToTrash:(char)fp8;
- (void)emptySpecialMailboxesThatNeedToBeEmptiedAtQuit;
- displayName;
- displayNameForMailboxUid:fp8;
- (BOOL)containsMailboxes;
- (void)resetSpecialMailboxes;
- mailboxPathExtension;
- (char)canCreateNewMailboxes;
- (char)newMailboxNameIsAcceptable:fp8 reasonForFailure:(id *)fp12;
- (char)canMailboxBeRenamed:fp8;
- (char)canMailboxBeDeleted:fp8;
- createMailboxWithParent:fp8 name:fp12;
- (char)renameMailbox:fp8 newName:fp12 parent:fp16;
- (char)deleteMailbox:fp8;
- (void)accountInfoDidChange;
- (void)postUserInfoHasChangedForMailboxUid:fp8 userInfo:fp12;
- (void)setConnectionError:fp8;
- connectionError;
- storeForMailboxUid:fp8;
- (Class)storeClass;
- (void)setUnreadCount:(unsigned int)fp8 forMailbox:fp12;
- (char)hasUnreadMail;
- mailboxUidForRelativePath:fp8 create:(char)fp12;
- valueInMailboxesWithName:fp8;
- objectSpecifierForMessageStore:fp8;
- objectSpecifierForMailboxUid:fp8;
- objectSpecifier;

@end

@interface MailAccount(Internal)
+ _accountWithPath:fp8;
+ (void)_postMailAccountsHaveChanged;
+ (void)_setOutboxMailboxUid:fp8;
+ _outboxMailboxUid;
- (char)_setPath:fp8;
- (void)setIsActive:(char)fp8;
- (void)_postMailAccountsHaveChangedIfNeeded;
- _pathComponentForUidName:fp8;
- _uidNameForPathComponent:fp8;
- (void)_readCustomInfoFromMailboxCache:fp8;
- (void)_writeCustomInfoToMailboxCache:fp8;
- _copyMailboxUidWithParent:fp8 name:fp12 attributes:(unsigned int)fp16 existingMailboxUid:fp20;
- (void)_synchronouslyLoadListingForParent:fp8;
- (void)_loadMailboxListingIntoCache:fp8 attributes:(unsigned int)fp12 parent:fp16;
- (char)_usesMailboxCache;
- (void)_synchronizeMailboxListWithFileSystem;
- (void)_loadEntriesFromFileSystemPath:fp8 parent:fp12;
- (void)_writeMailboxCacheWithPrejudice:(char)fp8;
- _insertMailbox:fp8 intoParent:fp12 withName:fp16;
- (void)_setChildren:fp8 forMailboxUid:fp12;
- (char)_deleteMailbox:fp8;
- description;
- (void)_fetchSynchronouslyIfNeeded;
- (void)_backgroundFetchCompleted;
- (void)_emptySpecialMailboxesIfNeeded;
- (void)_emptySpecialMailboxesIfNeededForQuit:(char)fp8;
- _defaultSpecialMailboxNameForType:(int)fp8;
- (void)_assignSpecialMailboxToAppropriateIvar:fp8 forType:(int)fp12;
- (void)_setSpecialMailboxName:fp8 forType:(int)fp12;
- (void)_setSpecialMailbox:fp8 forType:(int)fp12;
- _specialMailboxNameForType:(int)fp8;
- _specialMailboxUidWithType:(int)fp8 create:(char)fp12;
- (char)_shouldLogDeleteActivity;
@end

@interface MailAccount(ScriptingSupport)
- indicesOfObjectsByEvaluatingObjectSpecifier:fp8;
- mailboxes;
- (void)replaceInMailboxes:fp8 atIndex:(unsigned int)fp12;
- (void)insertInMailboxes:fp8 atIndex:(unsigned int)fp12;
- (void)insertInMailboxes:fp8;
- (void)removeFromMailboxesAtIndex:(unsigned int)fp8;
- (char)emptyTrashOnQuit;
- (void)setEmptyTrashOnQuit:(char)fp8;
- (char)emptySentMessagesOnQuit;
- (void)setEmptySentMessagesOnQuit:(char)fp8;
- (char)emptyJunkOnQuit;
- (void)setEmptyJunkOnQuit:(char)fp8;
@end

@interface MailboxUid:NSObject
{
    id _accountOrPathComponent;
    unsigned int _attributes;
    void *_tree;
    NSString *pendingNameChange;
}

+ specialMailboxUids;
- (void)_postInvalidNotificationIfNeeded;
- (void)dealloc;
- init;
- initWithAccount:fp8;
- initWithName:fp8 attributes:(unsigned int)fp12;
- displayName;
- (void)setPendingNameChange:fp8;
- name;
- (void)setName:fp8;
- (unsigned int)attributes;
- (void)setAttributes:(unsigned int)fp8;
- (unsigned int)unreadCount;
- (void)setUnreadCount:(unsigned int)fp8;
- (char)hasChildren;
- (unsigned int)numberOfGenericChildren;
- (unsigned int)numberOfChildren;
- childAtIndex:(unsigned int)fp8;
- (unsigned int)indexOfChild:fp8;
- childWithName:fp8;
- mutableCopyOfChildren;
- (char)setChildren:fp8;
- parent;
- (void)setParent:fp8;
- (void)setRepresentedAccount:fp8;
- representedAccount;
- account;
- applescriptAccount;
- (char)isValid;
- (void)invalidate;
- (char)isContainer;
- (char)isStore;
- (char)isSpecialMailboxUid;
- accountRelativePath;
- fullPath;
- tildeAbbreviatedPath;
- pathRelativeToMailbox:fp8;
- (int)compareWithMailboxUid:fp8;
- (int)indexToInsertChildMailboxUid:fp8;
- (char)isDescendantOfMailbox:fp8;
- depthFirstEnumerator;
- description;
- (int)type;
- (void)setType:(int)fp8;
- _loadUserInfo;
- userInfoObjectForKey:fp8;
- (void)setUserInfoObject:fp8 forKey:fp12;
- (char)userInfoBoolForKey:fp8;
- (void)setUserInfoBool:(char)fp8 forKey:fp12;
- (void)saveUserInfo;

@end

@interface MessageStore:NSObject
{
    int _flags;
    MailboxUid *_mailboxUid;
    MailAccount *_account;
    id *_index;
    NSMutableArray *_allMessages;
    NSMutableArray *_messagesToBeAddedToIndex;
    NSMutableArray *_messagesToBeRemovedFromIndex;
    unsigned int _allMessagesSize;
    unsigned int _deletedMessagesSize;
    unsigned int _deletedMessageCount;
    unsigned int _unreadMessageCount;
    id _updateIndexMonitor;
    int _state;
    id *_headerDataCache;
    id *_headerCache;
    id *_bodyDataCache;
    id *_bodyCache;
    NSTimer *_timer;
    NSMutableSet *_uniqueStrings;
    double timeOfLastAutosaveOperation;
}

+ (void)initialize;
+ (unsigned int)numberOfCurrentlyOpenStores;
+ descriptionOfOpenStores;
+ currentlyAvailableStoreForUid:fp8;
+ currentlyAvailableStoresForAccount:fp8;
+ registerAvailableStore:fp8;
+ (void)removeStoreFromCache:fp8;
+ (char)createEmptyStoreIfNeededForPath:fp8;
+ (char)createEmptyStoreForPath:fp8;
+ (char)storeAtPathIsWritable:fp8;
+ (char)cheapStoreAtPathIsEmpty:fp8;
+ (int)copyMessages:fp8 toMailboxUid:fp12 shouldDelete:(char)fp16;
- (void)release;
- initWithMailboxUid:fp8 readOnly:(char)fp12;
- copyWithZone:(struct _NSZone *)fp8;
- (void)dealloc;
- (void)openAsynchronouslyUpdatingIndex:(char)fp8 andOtherMetadata:(char)fp12;
- (void)openAsynchronously;
- (void)openSynchronously;
- (void)openSynchronouslyUpdatingIndex:(char)fp8 andOtherMetadata:(char)fp12;
- (void)updateMetadataAsynchronously;
- (void)updateMetadata;
- (void)didOpen;
- (void)writeUpdatedMessageDataToDisk;
- (void)invalidateSavingChanges:(char)fp8;
- account;
- mailboxUid;
- (char)isOpened;
- storePathRelativeToAccount;
- displayName;
- (const STR)displayNameForLogging;
- (char)isReadOnly;
- description;
- (char)isTrash;
- (char)isDrafts;
- (void)messageFlagsDidChange:fp8 flags:fp12;
- (void)structureDidChange;
- (void)messagesWereAdded:fp8;
- (void)messagesWereCompacted:fp8;
- (void)updateUserInfoToLatestValues;
- (unsigned int)totalMessageSize;
- (void)deletedCount:(unsigned int *)fp8 andSize:(unsigned int *)fp12;
- (unsigned int)totalCount;
- (unsigned int)unreadCount;
- (unsigned int)indexOfMessage:fp8;
- copyOfAllMessages;
- mutableCopyOfAllMessages;
- (void)addMessagesToAllMessages:fp8;
- (void)addMessageToAllMessages:fp8;
- _defaultRouterDestination;
- routeMessages:fp8;
- finishRoutingMessages:fp8 routed:fp12;
- (char)canRebuild;
- (void)rebuildTableOfContentsAsynchronously;
- (char)canCompact;
- (void)doCompact;
- (void)deleteMessagesOlderThanNumberOfDays:(int)fp8 compact:(char)fp12;
- (void)deleteMessages:fp8 moveToTrash:(char)fp12;
- (void)undeleteMessages:fp8;
- (void)deleteLastMessageWithHeader:fp8 forHeaderKey:fp12 compactWhenDone:(char)fp16;
- (char)allowsAppend;
- (int)undoAppendOfMessageIDs:fp8;
- (int)appendMessages:fp8 unsuccessfulOnes:fp12 newMessageIDs:fp16;
- (int)appendMessages:fp8 unsuccessfulOnes:fp12;
- messageWithValue:fp8 forHeader:fp12 options:(unsigned int)fp16;
- messageForMessageID:fp8;
- (void)_setHeaderDataInCache:fp8 forMessage:fp12;
- headerDataForMessage:fp8;
- bodyDataForMessage:fp8;
- fullBodyDataForMessage:fp8;
- bodyForMessage:fp8 fetchIfNotAvailable:(char)fp12;
- headersForMessage:fp8;
- dataForMimePart:fp8;
- (char)hasCachedDataForMimePart:fp8;
- uniquedString:fp8;
- colorForMessage:fp8;
- (char)_shouldChangeComponentMessageFlags;
- setFlagsFromDictionary:fp8 forMessages:fp12;
- setFlagsFromDictionary:fp8 forMessage:fp12;
- (void)setFlag:fp8 state:(char)fp12 forMessages:fp16;
- (void)setColor:fp8 highlightTextOnly:(char)fp12 forMessages:fp16;
- (void)messageColorsNeedToBeReevaluated;
- (void)startSynchronization;
- performBruteForceSearchWithString:fp8 options:(int)fp12;
- (STR)createSerialNumberStringFrom:(STR)fp8 colorCode:(unsigned short)fp12;
- _getSerialNumberString;
- (void)setNumberOfAttachments:(unsigned int)fp8 isSigned:(char)fp12 isEncrypted:(char)fp16 forMessage:fp20;
- (void)updateNumberOfAttachmentsForMessages:fp8;
- (void)updateMessageColorsSynchronouslyForMessages:fp8;
- (void)updateMessageColorsAsynchronouslyForMessages:fp8;
- (void)setJunkMailLevel:(int)fp8 forMessages:fp12;
- (void)setJunkMailLevel:(int)fp8 forMessages:fp12 trainJunkMailDatabase:(char)fp16;
- status;
- (void)fetchSynchronously;
- (char)setPreferredEncoding:(unsigned long)fp8 forMessage:fp12;
- (void)suggestSortOrder:fp8 ascending:(char)fp12;
- sortOrder;
- (char)isSortedAscending;

@end

@interface MessageStore(MessageFrameworkOnly)
+ (void)_autosaveMessageStore:(void *)fp8;
- (void)_cancelAutosave;
- (void)_setNeedsAutosave;
- _fetchHeaderDataForMessage:fp8;
- _fetchBodyDataForMessage:fp8 andHeaderDataIfReadilyAvailable:(id *)fp12;
- _fetchBodyForMessage:fp8;
- (char)_shouldCallCompactWhenClosing;
- (void)_compactMessageAtIndex:(unsigned int)fp8;
- (char)_isReadyToBeInvalidated;
- (void)_saveChanges;
- (void)_invalidate;
- (void)_invalidateInBackground;
- (void)_countUnreadAndDeleted;
- (void)_cleanUpStaleAttachments;
- _lockFilePath;
- (char)_acquireLockFile:fp8;
- (void)_removeLockFile:fp8;
- (void)_flushAllMessageData;
- (void)_rebuildTableOfContentsSynchronously;
- _setOrGetBody:fp8 forMessage:fp12;
- (void)updateMessageColorsSynchronouslyForMessages:fp8 postingNotification:(char)fp12;
@end

@interface NSDataMessageStore:MessageStore
{
    NSData *_data;
}

- initWithData:fp8;
- (void)dealloc;
- storePath;
- headerDataForMessage:fp8;
- bodyDataForMessage:fp8;
- _setOrGetBody:fp8 forMessage:fp12;

@end

@interface DeliveryAccount:Account
{
}

+ deliveryAccounts;
+ (void)setDeliveryAccounts:fp8;
+ (void)addDeliveryAccount:fp8;
+ (void)removeDeliveryAccount:fp8;
+ (void)saveAccountInfoToDefaults;
+ accountWithIdentifier:fp8;
+ accountWithHostname:fp8 username:fp12;
+ newDefaultInstance;
- (Class)deliveryClass;
- identifier;
- (char)shouldUseAuthentication;
- (void)setShouldUseAuthentication:(char)fp8;

@end

@interface AuthScheme:NSObject
{
}

+ (void)initialize;
+ knownSchemes;
+ (void)registerSchemeClass:(Class)fp8;
+ schemeWithName:fp8;
- retain;
- (unsigned int)retainCount;
- (void)release;
- (Class)connectionClassForAccount:fp8;
- (Class)authenticatorClassForAccount:fp8;
- (unsigned int)defaultPortForAccount:fp8;
- authenticatorForAccount:fp8 connection:fp12;
- (BOOL)requiresPassword;
- name;
- humanReadableName;

@end

@interface Connection:NSObject
{
    id _securityLayer;
    id *_socket;
    STR _buffer;
    int _bufferRemainingBytes;
    unsigned int _bufferStart;
    unsigned int _bufferLength;
    NSData *_logData;
}

+ (void)initialize;
+ (char)logAllSocketActivity;
+ (void)setLogAllSocketActivity:(char)fp8;
+ logActivityOnPorts;
+ (void)setLogActivityOnPorts:fp8;
+ logActivityOnHosts;
+ (void)setLogActivityOnHosts:fp8;
- (void)dealloc;
- (char)connectUsingAccount:fp8;
- (char)authenticateUsingAccount:fp8;
- capabilities;
- authenticationMechanisms;
- (char)writeData:fp8 dontLogBytesInRange:(struct _NSRange)fp12;
- (char)writeData:fp8;
- (char)readLineIntoData:fp8;
- (char)readBytesIntoData:fp8 desiredLength:(unsigned int)fp12;
- (char)authenticateUsingAccount:fp8 authenticator:fp12;
- (char)startTLSForAccount:fp8;
- (char)isValid;
- (void)disconnect;
- (void *)_socket;

@end

@interface SMTPConnection:Connection
{
    int _lastResponseCode:31;
    int _hideLoggedData:1;
    id _lastResponse;
    NSMutableArray *_serviceExtensions;
    NSMutableData *_mdata;
    NSString *_domainName;
    int _originalSocketTimeout;
    int _lastCommandTimestamp;
}

+ (void)initialize;
- init;
- (void)dealloc;
- (int)state;
- lastResponse;
- (unsigned int)lastResponseCode;
- domainName;
- (void)setDomainName:fp8;
- (unsigned long long)maximumMessageBytes;
- authenticationMechanisms;
- (char)authenticateUsingAccount:fp8;
- (char)authenticateUsingAccount:fp8 authenticator:fp12;
- (char)connectUsingAccount:fp8;
- (int)mailFrom:fp8;
- (int)rcptTo:fp8;
- (int)noop;
- (int)sendData:fp8;
- (int)quit;
- (long)timeLastCommandWasSent;

@end

@interface SMTPConnection(PrivateCommands)
- (int)_sendCommand:(const STR)fp8 length:(unsigned int)fp12 argument:fp16 trailer:(const unsigned char)fp20;
- (int)_getReply;
- (void)_readResponseRange:(struct _NSRange *)fp8 isContinuation:(char *)fp12;
- (char)_connectUsingAccount:fp8;
- (int)_doHandshakeUsingAccount:fp8;
- (char)_hasParameter:fp8 forKeyword:fp12;
@end

@interface SMTPAccount:DeliveryAccount
{
    SMTPConnection *_connection;
    NSTimer *_timer;
    double _lastTimerSetDate;
}

+ accountTypeString;
+ newDefaultInstance;
- (Class)deliveryClass;
- (unsigned int)defaultPortNumber;
- serviceName;
- saslProfileName;
- (Class)connectionClass;
- preferredAuthScheme;
- (void)setPreferredAuthScheme:fp8;
- authenticatedConnection;
- (void)checkInConnection:fp8;
- (void)setTimer;
- (void)connectionExpired:fp8;
- (void)disconnect:fp8;
- (char)_shouldTryDirectSSLConnectionOnPort:(unsigned int)fp8;
- (void)releaseAllConnections;
- (void)setPasswordInKeychain:fp8;
- passwordFromKeychain;
- (void)dealloc;

@end

@interface SMTPAccount(Applescript)
- displayName;
- objectSpecifier;
@end

@interface Message:NSObject
{
    MessageStore *_store;
    unsigned int _messageFlags;
    int _flags;
    unsigned int _preferredEncoding;
    NSString *_senderAddressComment;
    unsigned int _dateSentInterval;
    unsigned int _dateReceivedInterval;
    NSString *_subject;
    unsigned char _subjectPrefixLength;
    NSString *_to;
    NSString *_sender;
    NSData *_messageIDHeaderDigest;
    NSData *_inReplyToHeaderDigest;
}

+ (void)initialize;
+ verboseVersion;
+ frameworkVersion;
+ (void)setUserAgent:fp8;
+ userAgent;
+ messageWithRFC822Data:fp8;
+ _filenameFromSubject:fp8 inDirectory:fp12 ofType:fp16;
+ makeUniqueAttachmentNamed:fp8 inDirectory:fp12;
+ makeUniqueAttachmentNamed:fp8 withExtension:fp12 inDirectory:fp16;
- init;
- copyWithZone:(struct _NSZone *)fp8;
- messageStore;
- (void)setMessageStore:fp8;
- headers;
- (unsigned long)messageFlags;
- (void)setMessageFlags:(unsigned long)fp8;
- messageBody;
- messageBodyIfAvailable;
- messageDataIncludingFromSpace:(char)fp8;
- (char)colorHasBeenEvaluated;
- color;
- (void)setColor:fp8;
- (void)setColorHasBeenEvaluated:(char)fp8;
- (void)dealloc;
- (unsigned int)messageSize;
- attributedString;
- preferredEmailAddressToReplyWith;
- messageID;
- messageIDHeaderDigest;
- (void)unlockedSetMessageIDHeaderDigest:fp8;
- (void)setMessageIDHeaderDigest:fp8;
- _messageIDHeaderDigestIvar;
- (char)needsMessageIDHeader;
- inReplyToHeaderDigest;
- (void)unlockedSetInReplyToHeaderDigest:fp8;
- (void)setInReplyToHeaderDigest:fp8;
- _inReplyToHeaderDigestIvar;
- (int)compareByNumberWithMessage:fp8;
- (char)isMessageContentsLocallyAvailable;
- headersForIndexingIncludingFullNames:(char)fp8;
- headersForIndexing;
- headersForJunk;
- stringForIndexingGettingHeadersIfAvailable:(id *)fp8 forJunk:(char)fp12;
- stringForIndexingGettingHeadersIfAvailable:(id *)fp8;
- stringForIndexing;
- stringForJunk;
- (unsigned int)numberOfAttachments;
- (int)junkMailLevel;
- (unsigned long)preferredEncoding;
- (void)setPreferredEncoding:(unsigned long)fp8;
- rawSourceFromHeaders:fp8 body:fp12;
- (char)_doesDateAppearToBeSane:fp8;
- _dateFromReceivedHeadersInHeaders:fp8;
- _dateFromDateHeaderInHeaders:fp8;
- (void)_setDateReceivedFromHeaders:fp8;
- (void)_setDateSentFromHeaders:fp8;
- (void)loadCachedHeaderValuesFromHeaders:fp8;
- subjectAndPrefixLength:(unsigned int *)fp8;
- subjectNotIncludingReAndFwdPrefix;
- subject;
- (void)setSubject:fp8;
- dateReceived;
- dateSent;
- (void)setDateReceivedTimeIntervalSince1970:(double)fp8;
- (double)dateReceivedAsTimeIntervalSince1970;
- (char)needsDateReceived;
- (double)dateSentAsTimeIntervalSince1970;
- (void)setDateSentTimeIntervalSince1970:(double)fp8;
- sender;
- (void)setSender:fp8;
- senderAddressComment;
- to;
- (void)setTo:fp8;
- (void)setMessageInfo:fp8 to:fp12 sender:fp16 dateReceivedTimeIntervalSince1970:(double)fp20 dateSentTimeIntervalSince1970:(double)fp28 messageIDHeaderDigest:fp36 inReplyToHeaderDigest:fp40;
- (void)setMessageInfoFromMessage:fp8;

@end

@interface Message(ScriptingSupport)
- objectSpecifier;
- (void)_setAppleScriptFlag:fp8 state:(char)fp12;
- (char)isRead;
- (void)setIsRead:(char)fp8;
- (char)wasRepliedTo;
- (void)setWasRepliedTo:(char)fp8;
- (char)wasForwarded;
- (void)setWasForwarded:(char)fp8;
- (char)wasRedirected;
- (void)setWasRedirected:(char)fp8;
- (char)isJunk;
- (void)setIsJunk:(char)fp8;
- (char)isDeleted;
- (void)setIsDeleted:(char)fp8;
- (char)isFlagged;
- (void)setIsFlagged:(char)fp8;
- replyTo;
- scriptedMessageSize;
- content;
- (void)_addRecipientsForKey:fp8 toArray:fp12;
- recipients;
- toRecipients;
- ccRecipients;
- bccRecipients;
- container;
- (void)setContainer:fp8;
- messageIDHeader;
- rawSource;
- allHeaders;
- (int)actionColorMessage;
- (void)setBackgroundColor:(int)fp8;
- appleScriptHeaders;
@end

@interface MessageBody:NSObject
{
    Message *_message;
    NSString *_attachPath;
}

+ defaultAttachmentDirectory;
+ (void)setDefaultAttachmentDirectory:fp8;
- rawData;
- attributedString;
- (char)isHTML;
- (char)isRich;
- (void)dealloc;
- stringForIndexing;
- (void)setMessage:fp8;
- message;
- (void)setAttachmentDirectory:fp8;
- attachmentDirectory;
- (void)calculateNumberOfAttachmentsIfNeeded;
- attachments;
- textHtmlPart;

@end

@interface MessageHeaders:NSObject <NSCopying>
{
    NSData *_data;
    unsigned int _preferredEncoding;
}

+ localizedHeaders;
+ localizedHeadersFromEnglishHeaders:fp8;
+ englishHeadersFromLocalizedHeaders:fp8;
- initWithHeaderData:fp8 encoding:(unsigned long)fp12;
- copyWithZone:(struct _NSZone *)fp8;
- (void)dealloc;
- mutableCopy;
- headerData;
- (unsigned long)preferredEncoding;
- (void)setPreferredEncoding:(unsigned long)fp8;
- (char)_isStructuredHeaderKey:fp8;
- attributedStringShowingHeaderDetailLevel:(int)fp8;
- headersDictionaryWithHeaderDetailLevel:(int)fp8;
- allHeaderKeys;
- (void)_setCapitalizedKey:fp8 forKey:fp12;
- _capitalizedKeyForKey:fp8;
- _headerValueForKey:fp8;
- (char)hasHeaderForKey:fp8;
- headersForKey:fp8;
- firstHeaderForKey:fp8;
- _decodeHeaderKeysFromData:fp8;
- isoLatin1CharsetHint;
- (void)_appendAddressList:fp8 toData:fp12;
- encodedHeaders;
- encodedHeadersIncludingFromSpace:(char)fp8;
- (void)appendHeaderData:fp8 andRecipients:fp12;
- _encodedHeadersIncludingFromSpace:(char)fp8;

@end

@interface MessageFlags:NSObject <NSCoding>
{
    unsigned int realFlags;
}

- initWithCoder:fp12;
- (void)encodeWithCoder:fp12;

@end

@interface NSCoder(MFMessageFlags)
- (unsigned int)decodeMessageFlags;
@end

@interface MutableMessageHeaders:MessageHeaders
{
    NSMutableDictionary *_headersAdded;
    NSMutableArray *_headersRemoved;
}

- mutableCopy;
- (void)dealloc;
- allHeaderKeys;
- (char)hasHeaderForKey:fp8;
- _headerValueForKey:fp8;
- (void)removeHeaderForKey:fp8;
- (void)setHeader:fp8 forKey:fp12;
- (void)appendFromSpaceIfMissing;
- (void)_appendHeaderKey:fp8 value:fp12 toData:fp16;
- (void)_appendAddedHeaderKey:fp8 value:fp12 toData:fp16;
- _encodedHeadersIncludingFromSpace:(char)fp8;
- (void)setAddressList:fp8 forKey:fp12;

@end

@interface NetworkController:NSObject
{
    id  _store;
    NSString *_domainName;
    int _waitingForDialToFinish:1;
    int _checkedNetwork:1;
    int _isNetworkUp:1;
    NSTimer *_notificationTimer;
}

+ sharedInstance;
- (void)dealloc;
- init;
- (char)isNetworkUp;
- domainName;
- (char)isHostReachable:fp12;

@end

@interface NetworkController(Private)
- (void)_postNotification:fp12;
- (void)_postNetworkChangeNotification:fp12;
- (void)_triggerDialForHostname:fp12;
@end

@interface TableOfContents:NSObject
{
    char _isValid;
    NSMutableArray *_messages;
    NSString *_path;
    NSData *_data;
    unsigned int _pos;
    int _header;
    NSMutableDictionary *_messageIDMap;
    char _isDirty;
}

- (void)_checkHeader;
- (void)_getMessageSummaries;
- (char)loadCacheFromFile;
- tocHeaderData;
- cachedData;
- (void)setTimeStamp:(int)fp12;
- init;
- initWithPath:fp12;
- (void)dealloc;
- (char)isDirty;
- (char)isValid;
- storePath;
- (void)rebuildCacheFromMessages:fp12;
- (char)flushCache;
- (unsigned int)count;
- cachedHeadersAtIndex:(unsigned int)fp12;
- messages;
- (void)removeMessage:fp12;
- (void)_addMessageToMap:fp12;
- (void)addMessage:fp12;
- addMessage:fp12 withRange:(struct _NSRange)fp16;
- description;
- (void)setPath:fp12;
- path;
- (char)flushToFile;
- messageForMessageID:fp12;

@end

@interface TOCMessage:Message
{
    struct _NSRange _mboxRange;
    NSString *_attachments;
    NSString *_messageID;
}

+ messageIDForSender:fp8 subject:fp12 dateAsTimeInterval:(double)fp16;
- initWithMessage:fp8;
- (void)dealloc;
- (unsigned int)loadCachedInfoFromBytes:(const STR)fp8 length:(unsigned int)fp12 isDirty:(char *)fp16 usingUniqueStrings:fp20;
- cachedData;
- (struct _NSRange)mboxRange;
- (void)setMboxRange:(struct _NSRange)fp8;
- attachment;
- messageID;
- (int)compareByNumberWithMessage:fp8;
- (unsigned int)messageSize;
- description;

@end

@interface NeXTMbox:MessageStore
{
    NSData *_mboxData;
    TableOfContents *_toc;
    char _haveUpdatedMetadata;
}

+ (char)storeExistsForPath:fp12;
+ (char)createEmptyStoreForPath:fp12;
+ (char)storeAtPathIsWritable:fp12;
+ (char)cheapStoreAtPathIsEmpty:fp12;
- initWithMailboxUid:fp12 readOnly:(char)fp16;
- (void)dealloc;
- (void)openSynchronouslyUpdatingIndex:(char)fp12 andOtherMetadata:(char)fp16;
- (void)updateMetadata;
- _lockFilePath;
- (void)_invalidate;
- (void)writeUpdatedMessageDataToDisk;
- (void)_rebuildTableOfContentsSynchronously;
- (void)_flushAllMessageData;
- (void)_resetAllMessages;
- messageForMessageID:fp12;
- _TOCMessageForMessage:fp12;
- (unsigned int)flagsForMessage:fp12;
- _fetchHeaderDataForMessage:fp12;
- _fetchBodyDataForMessage:fp12 andHeaderDataIfReadilyAvailable:(id *)fp16;
- (char)canCompact;
- (void)doCompact;
- (void)_deleteAttachments:fp12;
- _processNeXTMailAttachmentHeaders:fp12;
- (char)_appendMessage:fp12 toFile:fp16 andTableOfContents:fp20;
- (int)_appendMessages:fp12 unsuccessfulOnes:fp16 mboxName:fp20 tableOfContents:fp24;
- (char)allowsAppend;
- (int)appendMessages:fp12 unsuccessfulOnes:fp16;
- (void)_incorporateMailFromIncoming;
- (int)_writeMessagesToIncomingMail:fp12 unsuccessfulOnes:fp16;
- (char)indexIsValid;

@end

@interface ActivityMonitor:NSObject
{
    NSPort *_cancelPort;
    NSString *_taskName;
    NSString *_statusMessage;
    NSString *_descriptionString;
    double _percentDone;
    int _key:13;
    int _canCancel:1;
    int _shouldCancel:1;
    int _isActive:1;
    int _priority:8;
    int _changeCount:8;
    id _delegate;
    id _target;
}

+ currentMonitor;
- init;
- (void)dealloc;
- (char)isActive;
- (void)setDelegate:fp12;
- (void)postActivityStarting;
- (void)handlePortMessage:fp12;
- (void)postActivityFinished;
- (void)_didChange;
- (int)changeCount;
- (void)setStatusMessage:fp12;
- (void)setStatusMessage:fp12 percentDone:(double)fp40;
- statusMessage;
- (void)setPercentDone:(double)fp40;
- (double)percentDone;
- (unsigned char)priority;
- (void)setPriority:(unsigned char)fp12;
- description;
- taskName;
- (void)setTaskName:fp12;
- (void)setActivityTarget:fp12;
- activityTarget;
- (char)canBeCancelled;
- (void)setCanBeCancelled:(char)fp12;
- (char)shouldCancel;
- (void)setShouldCancel:(char)fp12;
- (void)cancel;
- (int)acquireExclusiveAccessKey;
- (void)relinquishExclusiveAccessKey:(int)fp12;
- (void)setStatusMessage:fp12 percentDone:(double)fp40 withKey:(int)fp24;
- (void)setStatusMessage:fp12 withKey:(int)fp16;
- (void)setPercentDone:(double)fp40 withKey:(int)fp20;

@end

@interface NSMutableData(NSDataUtils)
- (void)appendCString:(const STR)fp12;
- (void)appendByte:(char)fp12;
- (void)convertNetworkLineEndingsToUnix;
@end

@interface LocalAccount:MailAccount
{
}

+ localAccount;
+ accountTypeString;
- initWithPath:fp12;
- (Class)storeClass;
- mailboxPathExtension;
- primaryMailboxUid;
- (void)setPath:fp12;
- displayName;
- (void)setHostname:fp12;
- (void)setUsername:fp12;
- password:(char)fp12;
- (void)setPassword:fp12;
- (char)canFetch;
- (char)shouldAutoFetch;
- (char)isOffline;
- (void)setIsOffline:(char)fp12;
- (void)_synchronouslyLoadListingForParent:fp12;
- _copyMailboxUidWithParent:fp12 name:fp16 attributes:(unsigned int)fp20 existingMailboxUid:fp24;
- createMailboxWithParent:fp12 name:fp16 reasonForFailure:(id *)fp20;
- (char)renameMailbox:fp12 newName:fp16 parent:fp20 reasonForFailure:(id *)fp24;

@end

@interface MailDelivery:NSObject
{
    id _delegate;
    Message *_message;
    MailAccount *_archiveAccount;
    DeliveryAccount *_account;
    int _askForReadReceipt:1;
    int _threaded:1;
    int _status:4;
    int __UNUSED__:25;
}

+ newWithMessage:fp12;
+ (char)deliverMessage:fp12 askForReadReceipt:(char)fp16;
+ (char)deliverMessage:fp12;
+ (char)returnMessageToSender:fp12;
- initWithMessage:fp12;
- (void)dealloc;
- message;
- delegate;
- (void)setDelegate:fp12;
- archiveAccount;
- (void)setArchiveAccount:fp12;
- account;
- (void)setAccount:fp12;
- (char)askForReadReceipt;
- (void)setAskForReadReceipt:(char)fp12;
- (int)deliveryStatus;
- (void)deliverAsynchronously;
- (int)deliverSynchronously;
- (int)deliverSynchronouslySpecifyingReasonForFailure:(id *)fp12;
- (void)prepareToDeliver;
- (void)deliverMessageData:fp12 toRecipients:fp16;

@end

@interface POPAccount:MailAccount
{
    id *_fetcher;
    ActivityMonitor *_fetchMonitor;
    char _fetcherNeedsReset;
    char _deletingSeenMessages;
    char _hasDoneBackgroundSynchronization;
}

+ accountTypeString;
- init;
- (void)dealloc;
- (char)_configureFetcherObject;
- (void)fetchSynchronously;
- (void)resetFetcher;
- (void)releaseAllConnections;
- (char)canGoOffline;
- (void)setIsOffline:(char)fp8;
- (void)_readCustomInfoFromMailboxCache:fp8;
- (unsigned int)defaultPortNumber;
- (unsigned int)defaultSecurePortNumber;
- serviceName;
- secureServiceName;
- saslProfileName;
- (char)requiresAuthentication;
- (Class)storeClass;
- (Class)connectionClass;
- storeForMailboxUid:fp8;
- mailboxPathExtension;
- primaryMailboxUid;
- (char)usedToBeConfiguredForLocalINBOX;
- (char)canCreateNewMailboxes;
- (char)canMailboxBeRenamed:fp8;
- (char)_setPath:fp8;
- (char)deleteMessagesOnServer;
- (void)setDeleteMessagesOnServer:(char)fp8;
- (int)bigMessageWarningSize;
- (void)setBigMessageWarningSize:(int)fp8;
- (void)setMessageDeletionPolicy:(int)fp8;
- (void)setDelayedMessageDeletionInterval:(unsigned int)fp8;
- (int)messageDeletionPolicy;
- (unsigned int)delayedMessageDeletionInterval;
- (char)deletingSeenMessages;
- (void)deleteSeenMessagesNow;
- (void)insertInMailboxes:fp8 atIndex:(unsigned int)fp12;

@end

@interface POPAccount(Applescript)
- (char)deleteMessagesWhenMovedFromInbox;
- (void)setDeleteMessagesWhenMovedFromInbox:(char)fp8;
- mailboxes;
- objectSpecifierForMailboxUid:fp8;
- valueInMailboxesWithName:fp8;
- storeForMailboxUid:fp8;
@end

@interface IMAPAccount:MailAccount
{
    NSString *_separatorChar;
    NSArray* _lastKnownCapabilities;
    NSArray* _cachedConnections;
    NSArray* _mailboxesToSynchronize;
    int _readBufferSize:31;
    int _lastConnectionFailed:1;
    id _offlineCache;
}

+ accountTypeString;
- (void)_readCustomInfoFromMailboxCache:fp8;
- (void)_writeCustomInfoToMailboxCache:fp8;
- (void)dealloc;
- (void)saveState;
- (Class)storeClass;
- mailboxPathExtension;
- (void)setDisplayName:fp8;
- (unsigned int)defaultPortNumber;
- (unsigned int)defaultSecurePortNumber;
- serviceName;
- secureServiceName;
- saslProfileName;
- (BOOL)requiresAuthentication;
- (Class)connectionClass;
- (char)compactWhenClosingMailboxes;
- (void)setCompactWhenClosingMailboxes:(char)fp8;
- (void)setCachePolicy:(int)fp8;
- (int)cachePolicy;
- (char)cachesAllMailboxes;
- (void)setCachesAllMailboxes:(char)fp8;
- (char)storeDraftsOnServer;
- (void)setStoreDraftsOnServer:(char)fp8;
- (char)storeJunkOnServer;
- (void)setStoreJunkOnServer:(char)fp8;
- (char)storeSentMessagesOnServer;
- (void)setStoreSentMessagesOnServer:(char)fp8;
- (char)storeTrashOnServer;
- (void)setStoreTrashOnServer:(char)fp8;
- primaryMailboxUid;
- (void)handleAlertResponse:fp8;
- (unsigned int)readBufferSize;
- (void)setReadBufferSize:(unsigned int)fp8;
- (void)_synchronizeMailboxesSynchronously;
- (void)synchronizeAllMailboxes;
- (void)_checkForNewMessagesInStore:fp8 unreadCountDelta:(unsigned int)fp12;
- (unsigned int)minimumPartialDownloadSize;
- (char)allowsPartialDownloads;
- (void)setAllowsPartialDownloads:(char)fp8;
- (char)connectAndAuthenticate:fp8;
- connectionForStore:fp8 delegate:fp12 options:(int)fp16;
- (void)handleOpenMailboxError:fp8;
- (void)checkInConnection:fp8;
- (void)unselectMailbox:fp8;
- (void)filterMailboxList:fp8 forMailbox:fp12 options:(int)fp16;
- (void)_releaseAllConnectionsAndCallSuper:(char)fp8;
- (void)releaseAllConnections;
- (void)_validateConnections;
- (void)validateConnections;
- (void)connectionDidDisconnect:fp8;
- (char)connection:fp8 shouldHandleUntaggedResponse:fp12 forCommand:(int)fp16;
- (void)connection:fp8 didReceiveResponse:fp12 forCommand:(int)fp16;
- (BOOL)canGoOffline;
- (void)setIsOffline:(char)fp8;
- (void)fetchSynchronously;
- separatorChar;
- lastKnownCapabilities;
- _listingForMailboxUid:fp8 listAllChildren:(char)fp12;
- createMailboxWithParent:fp8 name:fp12;
- (char)_deleteMailbox:fp8;
- (void)_setSpecialMailbox:fp8 forType:(int)fp12;
- _specialMailboxNameForType:(int)fp8;
- (char)_isMailboxTypeStoredLocally:(int)fp8;
- _localMailboxNameForType:(int)fp8 usingDisplayName:fp12;
- (void)_renameLocalSpecialMailboxesToName:fp8;
- _specialMailboxUidWithType:(int)fp8 create:(char)fp12;
- (char)canBeSynchronized;
- (void)nowWouldBeAGoodTimeToStartBackgroundSynchronization;
- (void)_fetchUnreadCountsForMailboxUid:fp8 recursively:(char)fp12 connection:fp16;
- (void)_synchronizeAccountWithServer;
- _copyMailboxUidWithParent:fp8 name:fp12 attributes:(unsigned int)fp16 existingMailboxUid:fp20;
- (void)_synchronouslyLoadListingForParent:fp8;
- (char)renameMailbox:fp8 newName:fp12 parent:fp16;
- (void)insertInMailboxes:fp8 atIndex:(unsigned int)fp12;
- _pathComponentForUidName:fp8;
- _uidNameForPathComponent:fp8;
- _nameForMailboxUid:fp8;
- _mailboxUidForName:fp8;
- (char)canMailboxBeDeleted:fp8;
- serverPathPrefix;
- (void)setServerPathPrefix:fp8;
- (void)deleteMessagesFromMailboxUid:(MailboxUid*)mailbox olderThanNumberOfDays:(unsigned int)olderthan compact:(BOOL)shouldCompat;
- (char)_canEmptyMessagesFromMailboxUid:fp8;
- offlineCache;

@end

@interface MFError:NSError
{
    NSMutableDictionary *_moreUserInfo;
}

+ errorWithDomain:fp8 code:(long)fp12 localizedDescription:fp16;
+ errorWithDomain:fp8 code:(long)fp12 localizedDescription:fp16 title:fp20 helpTag:fp24 userInfo:fp28;
+ errorWithException:fp8;
- (void)setUserInfoObject:fp8 forKey:fp12;
- userInfo;
- moreInfo;
- helpAnchor;
- shortDescription;
- (void)setLocalizedDescription:fp8;
- (void)setMoreInfo:fp8;
- (void)setHelpTag:fp8;
- (void)setShortDescription:fp8;
- (char)alertShowHelp:fp8;
- (void)dealloc;

@end

@interface NSError(MessageAdditions)
- (char)isUserCancelledError;
- (char)shouldBeReportedToUser;
- moreInfo;
- helpAnchor;
- shortDescription;
@end

@interface SASLAuthenticator:NSObject
{
    void *_context;
    AuthScheme *_authScheme;
    Account *_account;
    int _authenticationState;
}

- initWithAuthScheme:fp8 account:fp12 connection:fp16;
- (void)dealloc;
- authScheme;
- account;
- saslName;
- responseForServerData:fp8;
- (int)authenticationState;
- (void)setAuthenticationState:(int)fp8;
- (char)justSentPlainTextPassword;
- securityLayer;
- localAddress;
- remoteAddress;
- (char)isUsingSSL;

@end

@interface PlainAuthenticator:SASLAuthenticator
{
}

- saslName;
- responseForServerData:fp8;
- (char)justSentPlainTextPassword;

@end
