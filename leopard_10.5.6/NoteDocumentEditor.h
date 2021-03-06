/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "DocumentEditor.h"

@class MailDocumentEditor;

@interface NoteDocumentEditor : DocumentEditor
{
    MailDocumentEditor *_mailEditor;
    id _webViewFrameLoadDelegate;
    id _webViewPolicyDelegate;
    id _webViewUIDelegate;
    id _webViewDownloadDelegate;
    id _webViewResourceLoadDelegate;
    struct {
        unsigned int isFirstView:1;
        unsigned int isLastView:1;
        unsigned int isPaperless:1;
        unsigned int isPaused:1;
        unsigned int isClosed:1;
        unsigned int preventClose:1;
        unsigned int otherEditorHasChanges:1;
    } _noteFlags;
}

+ (BOOL)usesCustomScroller;
+ (int)documentType;
+ (id)documentEditors;
+ (id)documentWebPreferences;
+ (void)restoreDraftMessage:(id)fp8 withSavedState:(id)fp12;
+ (id)createEditorWithSettings:(id)fp8;
+ (id)createEditorWithEditor:(id)fp8;
+ (id)editorForNote:(id)fp8;
+ (id)editorWithSettings:(id)fp8;
- (BOOL)otherEditorHasChanges;
- (void)setOtherEditorHasChanges:(BOOL)fp8;
- (BOOL)isFirstView;
- (void)setIsFirstView:(BOOL)fp8;
- (BOOL)isLastView;
- (void)setIsLastView:(BOOL)fp8;
- (BOOL)isPaperless;
- (void)setIsPaperless:(BOOL)fp8;
- (BOOL)isPaused;
- (void)setIsPaused:(BOOL)fp8;
- (BOOL)isClosed;
- (void)setIsClosed:(BOOL)fp8;
- (BOOL)preventClose;
- (void)setPreventClose:(BOOL)fp8;
- (BOOL)isSelectionEditable;
- (BOOL)displayToDoMessageReference;
- (void)showPrintPanel:(id)fp8;
- (void)printOperationDidRun:(id)fp8 success:(BOOL)fp12 contextInfo:(void *)fp16;
- (id)initWithType:(int)fp8 settings:(id)fp12 backEnd:(id)fp16;
- (id)loadInterfaceOperation;
- (void)loadNotePaper;
- (void)finishLoadingEditor;
- (BOOL)windowShouldClose:(id)fp8;
- (void)didLoadNotePaper;
- (BOOL)load;
- (id)documentModifiedNotification;
- (id)editorID;
- (void)documentClosed:(id)fp8;
- (void)documentModified:(id)fp8;
- (void)beginDocumentMove;
- (void)endDocumentMove;
- (id)loadInitialDocumentOperation;
- (id)mailEditor;
- (void)setMailEditor:(id)fp8;
- (void)dealloc;
- (id)shouldSaveTitle;
- (id)shouldSaveDescription;
- (id)shouldSaveHelptag;
- (BOOL)validateAction:(SEL)fp8 tag:(int)fp12;
- (BOOL)validateMenuItem:(id)fp8;
- (BOOL)canSave;
- (BOOL)hasChanges;
- (void)pause;
- (void)resume;
- (void)makePaperbacked;
- (void)addTitleAndFooter;
- (void)webViewDidChange:(id)fp8;
- (void)backupWebViewDelegates;
- (void)restoreWebViewDelegates;
- (id)resource;
- (id)_frameSaveName;
- (id)contentWebFrame;
- (void)composePrefsChanged;
- (void)reportSaveFailure:(id)fp8;
- (void)_mailAccountsDidChange;
- (Class)backEndClass;
- (int)editorSharedNib;
- (id)toolbarIdentifier;
- (void)editorDidLoad:(id)fp8;
- (void)editorFailedLoad:(id)fp8;
- (void)show;
- (void)forceClose;
- (void)mailAttachmentsAdded:(id)fp8;
- (void)backEndDidLoadInitialContent:(id)fp8;
- (void)themeWebFrameScrollers:(id)fp8;
- (void)send:(id)fp8;
- (BOOL)_sendButtonShouldBeEnabled;

@end

