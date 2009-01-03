/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class ABLDAP_Manager, ABLDAP_Server, ActivityMonitor, NSControl, NSMutableArray, NSProgressIndicator, NSString, NSTableView, NSThread, NSTimer, NSWindow;

@interface OldCompletionController : NSObject
{
    NSControl *_editingField;
    NSWindow *_editingWindow;
    NSString *_currentPartialString;
    NSString *_previousString;
    NSWindow *_completionWindow;
    NSTableView *_completionTableView;
    id _selectedRecord;
    NSString *_selectedAddress;
    NSString *_completedAddress;
    NSMutableArray *_matchingRecords;
    NSMutableArray *_matchingAddresses;
    NSMutableArray *_ldapMatches;
    ABLDAP_Manager *_ldapManager;
    ABLDAP_Server *_dirServicesServer;
    NSTimer *_ldapTimer;
    NSThread *_dirServicesServerThread;
    NSTimer *_dirServicesServerTimer;
    NSProgressIndicator *progressIndicator;
    ActivityMonitor *completionMonitor;
    BOOL showListAsSoonAsPossible;
    BOOL ldapSearchIsComplete;
    BOOL ldapSearchIsPending;
    BOOL localSearchIsComplete;
    BOOL showingPartialLDAPSearchResults;
}

+ (void)initialize;
+ (void)_doCompletionWindowPlacement:(id)fp8;
- (id)init;
- (void)setProgressIndicatorVisible:(BOOL)fp8;
- (void)awakeFromNib;
- (void)_stopTimer;
- (void)_startTimer;
- (void)_disconnectAllLDAPConnections:(id)fp8;
- (void)userDidSelectText:(id)fp8;
- (void)_reset:(id)fp8;
- (id)selectedRecord;
- (id)completedAddress;
- (void)setCompletedAddress:(id)fp8;
- (void)textFieldDidAtomicizeAllAddresses:(id)fp8;
- (void)cancelAllCompletions;
- (void)cancelThisCompletion;
- (BOOL)_acceptCurrentCompletion;
- (void)selectTableViewRow:(id)fp8;
- (void)setEditingField:(id)fp8;
- (id)stringToComplete:(id)fp8;
- (void)_showSelectedLineInField;
- (void)_showSelectedLine;
- (void)_showCompletionListWindow:(unsigned int)fp8;
- (void)orderOutCompletionWindow:(id)fp8;
- (void)placementViewFrameChanged:(id)fp8;
- (void)_displayFilteredResultsShowList:(BOOL)fp8 showSelectedLine:(BOOL)fp12;
- (void)updateList:(id)fp8;
- (void)endUpdateList:(id)fp8;
- (void)appendLDAPResultsToMatchingRecords;
- (void)mergeLDAPMatchesIntoMatchingRecords;
- (void)completeStringUsingLDAP:(id)fp8;
- (void)completeString:(id)fp8;
- (void)addressBookSearchCompleted:(id)fp8;
- (void)forceListToPopup;
- (int)numberOfRowsInTableView:(id)fp8;
- (id)tableView:(id)fp8 objectValueForTableColumn:(id)fp12 row:(int)fp16;
- (BOOL)control:(id)fp8 textShouldEndEditing:(id)fp12;
- (void)controlTextDidChange:(id)fp8;
- (BOOL)shouldChangeTextInRange:(struct _NSRange)fp8 replacementString:(id)fp16;
- (void)tableViewSelectionDidChange:(id)fp8;
- (BOOL)control:(id)fp8 textView:(id)fp12 doCommandBySelector:(SEL)fp16;
- (BOOL)control:(id)fp8 textShouldBeginEditing:(id)fp12;
- (void)dealloc;

@end

