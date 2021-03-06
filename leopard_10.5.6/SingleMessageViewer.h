/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "MessageViewer.h"

#import "MVSelectionOwner-Protocol.h"

@class NSView, SpotlightBar;

@interface SingleMessageViewer : MessageViewer <MVSelectionOwner>
{
    NSView *_messageContentView;
    SpotlightBar *_spotlightBar;
    BOOL nibLoaded;
}

+ (id)viewerForMessage:(id)fp8 showAllHeaders:(BOOL)fp12 viewingState:(id)fp16;
+ (void)restoreFromDefaults;
+ (void)saveDefaultsOmittingViewer:(id)fp8;
- (void)_updateWindowTitle;
- (void)loadMessageWindowNib;
- (id)initForViewingMessage:(id)fp8 showAllHeaders:(BOOL)fp12 viewingState:(id)fp16 fromDefaults:(BOOL)fp20;
- (id)initWithSavedDefaults:(id)fp8;
- (void)dealloc;
- (id)_messageIDDictionary;
- (void)_adjustNewSingleViewerWindowFrame;
- (void)_setupFromDefaults;
- (void)showAndMakeKey:(BOOL)fp8;
- (void)_restoreViewer;
- (id)_saveDefaults;
- (void)takeOverAsSelectionOwner;
- (void)resignAsSelectionOwner;
- (id)selectedMessages;
- (void)messageFlagsDidChange:(id)fp8;
- (BOOL)_validateAction:(SEL)fp8 tag:(int)fp12;
- (void)messagesCompacted:(id)fp8;
- (void)setupToolbar;
- (void)_updateToolbarForResizing:(BOOL)fp8;
- (id)previousIdentifierForUpgradingToolbar:(id)fp8;
- (id)toolbar:(id)fp8 upgradedItemIdentifiers:(id)fp12;
- (BOOL)_isViewingMessage:(id)fp8;
- (BOOL)_selectionContainsMessagesWithReadStatusEqualTo:(BOOL)fp8;
- (BOOL)_selectionContainsMessagesWithFlaggedStatusEqualTo:(BOOL)fp8;
- (BOOL)_selectionContainsMessagesWithJunkMailLevelEqualTo:(int)fp8;
- (BOOL)_selectionContainsMessagesWithAttachments;
- (void)deleteMessages:(id)fp8;
- (void)deleteMessagesAllowingMoveToTrash:(BOOL)fp8;
- (void)replyMessage:(id)fp8;
- (void)replyAllMessage:(id)fp8;
- (void)replyToSender:(id)fp8;
- (void)replyToOriginalSender:(id)fp8;
- (void)forwardMessage:(id)fp8;
- (void)redirectMessage:(id)fp8;
- (BOOL)send:(id)fp8;
- (void)editorDidLoad:(id)fp8;
- (BOOL)replaceWithEditorForType:(int)fp8;
- (void)_changeFlag:(id)fp8 state:(BOOL)fp12 forMessages:(id)fp16 undoActionName:(id)fp20;
- (void)keyDown:(id)fp8;
- (id)selection;
- (void)selectMessages:(id)fp8;
- (id)currentDisplayedMessage;
- (id)messageStore;
- (BOOL)transferSelectionToMailbox:(id)fp8 deleteOriginals:(BOOL)fp12;
- (void)_showSpotlightBarWithSearchString:(id)fp8;
- (void)_hideSpotlightBar;
- (void)setSearchString:(id)fp8;
- (void)setShowRevealMessageLink:(BOOL)fp8;
- (void)revealMessage:(id)fp8;

@end

