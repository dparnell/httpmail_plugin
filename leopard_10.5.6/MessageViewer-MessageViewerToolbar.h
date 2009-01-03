/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "MessageViewer.h"

@interface MessageViewer (MessageViewerToolbar)
- (void)setupToolbar;
- (BOOL)validateToolbarItem:(id)fp8;
- (id)previousIdentifierForUpgradingToolbar:(id)fp8;
- (id)toolbar:(id)fp8 upgradedItemIdentifiers:(id)fp12;
- (void)configureSegmentedItem:(id)fp8 withDictionary:(id)fp12 forSegment:(int)fp16;
- (id)toolbar:(id)fp8 itemForItemIdentifier:(id)fp12 willBeInsertedIntoToolbar:(BOOL)fp16;
- (void)setupSearchView:(BOOL)fp8;
- (void)_handleCancelSearchButton:(id)fp8;
- (id)toolbarDefaultItemIdentifiers:(id)fp8;
- (id)toolbarAllowedItemIdentifiers:(id)fp8;
- (void)_reallyUpdateToolbar;
- (void)_updateToolbarForResizing:(BOOL)fp8;
- (void)toolbarDidRemoveItem:(id)fp8;
- (void)toolbarWillAddItem:(id)fp8;
- (void)toolbarDidMoveItem:(id)fp8;
- (void)toolbarDidReplaceAllItems:(id)fp8;
- (void)_mailboxesViewFrameChanged;
- (void)_mailboxesViewDidEndLiveResize;
@end

