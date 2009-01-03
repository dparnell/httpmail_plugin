/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "DocumentEditor.h"

@interface DocumentEditor (DocumentEditorToolbar)
- (BOOL)validateToolbarItem:(id)fp8;
- (void)setupToolbar;
- (id)toolbarIdentifier;
- (void)_synchronizeChangeReplyItem:(id)fp8 messageType:(int)fp12;
- (void)toggleReplyType:(int)fp8;
- (void)updateSendButtonStateInToolbar;
- (void)toolbarWillAddItem:(id)fp8;
- (void)configureSegmentedItem:(id)fp8 withDictionary:(id)fp12 forSegment:(int)fp16;
- (id)previousIdentifierForUpgradingToolbar:(id)fp8;
- (id)toolbar:(id)fp8 upgradedItemIdentifiers:(id)fp12;
- (id)toolbar:(id)fp8 itemForItemIdentifier:(id)fp12 willBeInsertedIntoToolbar:(BOOL)fp16;
- (id)toolbarDefaultItemIdentifiers:(id)fp8;
- (id)toolbarAllowedItemIdentifiers:(id)fp8;
- (id)menuForListsItem;
@end

