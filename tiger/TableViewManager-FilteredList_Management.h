/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "TableViewManager.h"

@interface TableViewManager (FilteredList_Management)
- (BOOL)_allMailboxes:(id)fp8 areOfTypes:(int *)fp12 typeCount:(unsigned int)fp16;
- (void)_animateThreadCollapsing:(int)fp8 threadRow:(int)fp12 clickedRow:(int)fp16;
- (float)_animateThreadOpening:(id)fp8 threadMessageCount:(int)fp12 threadRow:(int)fp16 rowToBeSelected:(int)fp20;
- (struct _NSSize)_calculateTruncationAmountUsingRowHeight:(float)fp8 collapseOrExpandAmount:(float)fp12 invisibleThreadAmountAbove:(float)fp16 invisibleThreadAmountBelow:(float)fp20;
- (id)_createBackgroundImage;
- (id)_createHiliteImage;
- (id)_createSnapshotOfRect:(struct _NSRect)fp8 styleMask:(unsigned int)fp24 backing:(int)fp28 defer:(BOOL)fp32;
- (id)_createSnapshotOfRow:(int)fp8 styleMask:(unsigned int)fp12 backing:(int)fp16 defer:(BOOL)fp20;
- (BOOL)_criterionIsLastViewedDate:(id)fp8;
- (double)_getAnimationDuration:(int)fp8;
- (int)_indexOfMemberToSelectWhenOpeningThread:(id)fp8;
- (BOOL)_isRowVisible:(int)fp8;
- (void)_recordVisibleState:(struct visible_state *)fp8 deletedAreGoingAway:(BOOL)fp12 considerPinToEnd:(BOOL)fp16;
- (BOOL)_restoreVisibleState:(struct visible_state *)fp8 forceSelToVisible:(BOOL)fp12;
- (void)_saveScrollAndSelection:(BOOL)fp8;
- (void)_scrollToHappyPlace;
- (void)_setScrollAndSelectionForThreadOpenedOrClosed:(id)fp8 flag:(BOOL)fp12 clickedRow:(int)fp16 rowToSelectInOpeningThread:(int)fp20;
- (void)addRanks;
- (BOOL)allMailboxes:(id)fp8 areOfType:(int)fp12;
- (BOOL)allMailboxesAreOutgoing:(id)fp8;
- (BOOL)allMailboxesAreViewingHistorySmartMailboxes:(id)fp8;
- (void)clearSearch;
- (void)clearTrackingRects;
- (void)dumpVisibleState;
- (id)filteredMessages;
- (int)indexOfLastReadMessage;
- (int)indexOfTopmostVisibleMessageMustBeSelected:(BOOL)fp8 okayIfDeleted:(BOOL)fp12;
- (BOOL)isFocused;
- (BOOL)isShowingSearchResults;
- (BOOL)isSortedAscending;
- (BOOL)isSortedByDateReceived;
- (BOOL)isSortedByRank;
- (BOOL)isSortedChronologically;
- (BOOL)mailboxIsViewingHistorySmartMailbox:(id)fp8;
- (void)mallStructureWillChange:(id)fp8;
- (void)messageFlagsChanged:(id)fp8;
- (void)messagesCompacted:(id)fp8;
- (id)openThreadIDs;
- (id)persistentVisibleStateCreateIfNecessary:(BOOL)fp8;
- (void)removeRanks;
- (void)restoreLocationColumnIfAppropriate;
- (BOOL)restoreScrollAndSelection;
- (void)saveScrollAndSelection;
- (void)searchFinished:(id)fp8;
- (void)searchForString:(id)fp8 in:(int)fp12 withOptions:(int)fp16;
- (BOOL)selectMessageWithIDIfExists:(id)fp8;
- (id)selectedMessageIDs;
- (void)setFocusedMessages:(id)fp8;
- (void)setIsSortedAscending:(BOOL)fp8;
- (void)setMailboxUids:(id)fp8;
- (void)setSelectedMessageIDs:(id)fp8 openThreadIDs:(id)fp12;
- (void)setSortColumn:(int)fp8 ascending:(BOOL)fp12;
- (int)sortColumn;
- (int)state;
- (void)storeStructureChanged:(id)fp8;
- (void)tableView:(id)fp8 willMoveToWindow:(id)fp12;
- (void)tableViewDidMoveToWindow:(id)fp8;
- (void)updateTrackingRects;
@end

