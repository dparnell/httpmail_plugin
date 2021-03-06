/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

#import "SyncableDataOwnerProtocol.h"

@class MessageStore, NSConditionLock, NSLock, NSMutableArray;

@interface MessageRouter : NSObject <SyncableDataOwner>
{
    MessageStore *_store;
    NSMutableArray *_queuedMessages;
    NSConditionLock *_queuedMessagesFull;
    NSConditionLock *_queuedMessagesEmpty;
    NSLock *_queuedMessagesRouting;
    unsigned int _bytesInQueue;
    unsigned int _queueSize;
    BOOL _routingThreadShouldQuit;
    unsigned int _numMessagesRoutedSoFar;
    unsigned int _numMessagesToBeRouted;
    BOOL _isUserAction;
}

+ (id)writeRulesTimer;
+ (void)setWriteRulesTimer:(id)fp8;
+ (void)scheduleWriteRules;
+ (void)unScheduleWriteRules;
+ (void)observeValueForKeyPath:(id)fp8 ofObject:(id)fp12 change:(id)fp16 context:(void *)fp20;
+ (void)initialize;
+ (void)_updateICalRule:(BOOL)fp8;
+ (void)_setupAddInvitationDefault;
+ (void)_iCalSettingChangedFromICal:(id)fp8;
+ (BOOL)_hasColorRules;
+ (int)colorChangeCounter;
+ (void)setColorChangeCounter:(int)fp8;
+ (void)enqueueColorRulesDidChange;
+ (BOOL)_colorRuleExistsAfterRule:(id)fp8;
+ (BOOL)colorsUpdateDynamically;
+ (void)ruleAffectingColorsDidChange:(id)fp8;
+ (void)ruleDidChange:(id)fp8;
+ (void)mailboxWillBeRenamedOrInvalidated;
+ (void)_mailboxBecameInvalid:(id)fp8;
+ (void)_mailboxWasRenamed:(id)fp8;
+ (id)defaultAppleEmailAddresses;
+ (id)_defaultSortRules;
+ (id)sortRulesPath;
+ (id)oldSortRulesPath;
+ (id)iCalRule;
+ (BOOL)_setICalRule:(id)fp8;
+ (id)_sortRulesFromDictionaryRepresentations:(id)fp8 junkRule:(id *)fp12 iCalRule:(id *)fp16;
+ (id)_sortRuleDictionaryRepresentations;
+ (void)_setupSortRules;
+ (id)_readRulesFromDiskOldStyle;
+ (id)_readRulesFromDisk;
+ (void)writeRulesToDiskInBackground;
+ (void)synchronouslyWriteRulesToDisk;
+ (id)rules;
+ (unsigned int)numberOfRules;
+ (id)ruleAtIndex:(int)fp8;
+ (void)removeRuleAtIndex:(int)fp8;
+ (void)insertRule:(id)fp8 atIndex:(int)fp12;
+ (void)addRule:(id)fp8;
+ (void)removeRule:(id)fp8;
+ (void)tryToReconnectAutoDeactivatedRules;
+ (void)loadDestinationMailboxes;
+ (void)_mailboxListingChanged:(id)fp8;
+ (id)headersRequiredForRouting;
+ (void)headersRequiredForRoutingDidChange;
+ (void)putRulesThatWantsToHandleMessage:(id)fp8 intoArray:(id)fp12 colorRulesOnly:(BOOL)fp16;
+ (id)colorForMessage:(id)fp8 highlightTextUsingColor:(char *)fp12;
+ (int)junkMailBehavior;
+ (void)setJunkMailBehavior:(int)fp8;
+ (void)evaluateJunkMailBehaviorFromRules;
+ (void)reevaluateJunkMessagesInMailboxes:(id)fp8;
+ (id)junkMailRuleForBehavior:(int)fp8 abCriterion:(BOOL)fp12 ahCriterion:(BOOL)fp16 fnCriterion:(BOOL)fp20;
+ (id)junkMailRule;
+ (void)setJunkMailRule:(id)fp8;
+ (id)userJunkMailRule;
+ (id)defaultJunkMailRule;
+ (BOOL)junkMailEvaluationAfterRules;
+ (void)setJunkMailEvaluationAfterRules:(BOOL)fp8;
+ (BOOL)junkMailTrustHeaders;
+ (void)setJunkMailTrustHeaders:(BOOL)fp8;
+ (id)junkMailHeaderFlags;
+ (void)_applyRulesToMailboxUids:(id)fp8;
+ (void)applyRulesAsynchronouslyToMailboxUids:(id)fp8;
+ (BOOL)addInvitationsToICalAutomatically;
+ (BOOL)_addICalRule;
+ (void)setAddInvitationsToICalAutomatically:(BOOL)fp8;
+ (void)addInvitationsToICalFromMessages:(id)fp8;
+ (void)installNewRulesFromPlist:(id)fp8;
- (BOOL)_routeMessagesIndividually;
- (id)routeMessages:(id)fp8 fromStores:(id)fp12;
- (void)asynchronouslyRouteMessages:(id)fp8;
- (void)routeQueuedMessages;
- (void)waitForRoutingToFinish;
- (void)setStore:(id)fp8;
- (void)setEstimatedNumberOfMessagesToRoute:(unsigned int)fp8;
- (void)dealloc;
- (void)finalize;
- (void)setIsUserAction:(BOOL)fp8;
- (BOOL)dataWillBeSyncedVersion:(id *)fp8 data:(id *)fp12 type:(id)fp16;
- (BOOL)dataWasSyncedVersion:(id)fp8 newData:(id)fp12 acceptedChanges:(id)fp16;
- (id)newRulesArrayWithJunkAndICalRules:(id)fp8;

@end

