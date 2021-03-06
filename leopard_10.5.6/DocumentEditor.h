/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class ComposeBackEnd, EditingMessageWebView, EditingWebMessageController, HeadersEditor, LoadingOverlay, NSDictionary, NSMutableDictionary, NSOperation, NSOperationQueue, NSToolbar, NSWindow, WebViewEditor;

@interface DocumentEditor : NSObject
{
    WebViewEditor *webViewEditor;
    HeadersEditor *headersEditor;
    NSWindow *_window;
    EditingMessageWebView *composeWebView;
    ComposeBackEnd *_backEnd;
    NSToolbar *_toolbar;
    NSMutableDictionary *_toolbarItems;
    EditingWebMessageController *webMessageController;
    LoadingOverlay *loadingOverlay;
    NSDictionary *settings;
    struct {
        unsigned int userSavedMessage:1;
        unsigned int userWantsToCloseWindow:1;
        unsigned int userKnowsSaveFailed:1;
        unsigned int registeredForNotifications:1;
        unsigned int alwaysSave:1;
        unsigned int userCanApplyStationery:1;
        unsigned int autoShowEditor:1;
        unsigned int isLoaded:1;
        unsigned int isAutoSaving:1;
    } _flags;
    int _messageType;
    struct _NSPoint _originalCascadePoint;
    NSMutableDictionary *_bodiesByAttachmentURL;
    NSOperationQueue *operationQueue;
    NSOperation *loadInterfaceOperation;
    NSOperation *showInterfaceOperation;
    NSOperation *prepareContentOperation;
    NSOperation *loadInitialDocumentOperation;
    NSOperation *finishLoadingEditorOperation;
    id _loadDelegate;
    double _lastSaveTime;
}

+ (void)initialize;
+ (id)autoSaveTimer;
+ (void)setAutosaveTimer:(id)fp8;
+ (id)_documentEditors;
+ (id)documentEditors;
+ (id)typedDocumentEditors;
+ (void)registerDocumentEditor:(id)fp8;
+ (void)unregisterDocumentEditor:(id)fp8;
+ (int)documentType;
+ (id)documentWebPreferences;
+ (id)existingEditorForMessage:(id)fp8 editorClass:(Class)fp12;
+ (id)editorsForDocumentID:(id)fp8 editorClass:(Class)fp12;
+ (id)existingEditorForMessage:(id)fp8;
+ (void)saveDefaults;
+ (void)restoreFromDefaults;
+ (void)showEditorWithSavedState:(id)fp8;
+ (void)setNeedsAutosave;
+ (void)autoSaveTimerFired;
- (id)documentID;
- (BOOL)isEditingDocumentID:(id)fp8;
- (id)description;
- (id)initWithType:(int)fp8 settings:(id)fp12 backEnd:(id)fp16;
- (BOOL)isLoaded;
- (void)setLoaded:(BOOL)fp8;
- (BOOL)isAutoSaving;
- (BOOL)load;
- (id)loadInterfaceOperation;
- (id)showInterfaceOperation;
- (id)prepareContentOperation;
- (id)loadInitialDocumentOperation;
- (void)loadInitialDocument;
- (id)finishLoadingEditorOperation;
- (BOOL)isFinishedLoading;
- (void)markFinishedLoading;
- (void)performOperationAfterLoad:(id)fp8;
- (void)finishLoadingEditor;
- (void)setShowInterfaceOperation:(id)fp8;
- (void)setLoadInterfaceOperation:(id)fp8;
- (void)setPrepareContentOperation:(id)fp8;
- (void)setLoadInitialDocumentOperation:(id)fp8;
- (void)setFinishLoadingEditorOperation:(id)fp8;
- (Class)backEndClass;
- (void)release;
- (void)dealloc;
- (BOOL)loadEditorNib;
- (id)operationQueue;
- (void)setOperationQueue:(id)fp8;
- (int)editorSharedNib;
- (void)show;
- (void)setHeaders:(id)fp8;
- (id)backEnd;
- (void)setBackEnd:(id)fp8;
- (id)webViewEditor;
- (id)headersEditor;
- (id)webMessageDocument;
- (id)toolbar;
- (id)window;
- (BOOL)autoShowEditor;
- (void)setAutoShowEditor:(BOOL)fp8;
- (BOOL)userCanApplyStationery;
- (void)setUserCanApplyStationery:(BOOL)fp8;
- (BOOL)wantsToClose;
- (void)setWantsToClose:(BOOL)fp8;
- (void)readDefaultsFromDictionary:(id)fp8;
- (void)writeDefaultsToDictionary:(id)fp8;
- (void)saveState;
- (void)_appendDefaultsToArray:(id)fp8;
- (id)_frameSaveName;
- (void)prepareContent;
- (void)backEndDidLoadInitialContent:(id)fp8;
- (id)webArchiveFromSettings:(id)fp8;
- (void)continueLoadingInitialContent;
- (void)postDocumentEditorDidFinishSetup;
- (void)_registerForNotificationsIfNeeded;
- (void)_setupSpellingAndGrammarChecking;
- (id)windowWillReturnFieldEditor:(id)fp8 toObject:(id)fp12;
- (void)backEnd:(id)fp8 didBeginBackgroundLoadActivity:(id)fp12;
- (void)loadingOverlayDidEnd:(id)fp8 returnCode:(int)fp12;
- (BOOL)autoSave;
- (BOOL)canSave;
- (BOOL)shouldSave;
- (void)saveMessageDueToUserAction:(BOOL)fp8;
- (void)backEnd:(id)fp8 willCreateMessageWithHeaders:(id)fp12;
- (BOOL)backEnd:(id)fp8 shouldSaveMessage:(id)fp12;
- (void)setUserSavedMessage:(BOOL)fp8;
- (BOOL)hasChanges;
- (void)reportSaveFailure:(id)fp8;
- (id)associatedMessage;
- (void)backEnd:(id)fp8 didUpdateMessage:(id)fp12;
- (void)backEndDidSaveMessage:(id)fp8 result:(int)fp12;
- (void)failedToSaveDraftSheetClosed:(id)fp8 returnCode:(int)fp12 contextInfo:(void *)fp16;
- (void)backEndDidChange:(id)fp8;
- (void)webViewDidChange:(id)fp8;
- (void)updateWindowContent;
- (void)updateUIAfterAppleScriptModification:(id)fp8;
- (void)composePrefsChanged;
- (void)mailAttachmentsAdded:(id)fp8;
- (void)openPanelSheetDidEnd:(id)fp8 returnCode:(int)fp12 contextInfo:(void *)fp16;
- (id)mimeBodyForAttachmentWithURL:(id)fp8;
- (BOOL)validateAction:(SEL)fp8 tag:(int)fp12;
- (BOOL)validateMenuItem:(id)fp8;
- (void)makeRichText:(id)fp8;
- (void)makePlainText:(id)fp8;
- (void)toggleRich:(id)fp8;
- (void)insertNumberedList:(id)fp8;
- (void)insertBulletedList:(id)fp8;
- (void)convertToNumberedList:(id)fp8;
- (void)convertToBulletedList:(id)fp8;
- (void)increaseListNestingLevel:(id)fp8;
- (void)decreaseListNestingLevel:(id)fp8;
- (void)saveDocument:(id)fp8;
- (void)saveChangedDocument:(id)fp8;
- (void)saveMessageToDrafts:(id)fp8;
- (void)performClose:(id)fp8;
- (void)messageSizeDidChange:(id)fp8;
- (void)insertFile:(id)fp8;
- (void)removeAttachments:(id)fp8;
- (void)createToDo:(id)fp8;
- (void)changeTextEncoding:(id)fp8;
- (void)showPrintPanel:(id)fp8;
- (void)searchIndex:(id)fp8;
- (void)changeSpellCheckingBehavior:(id)fp8;
- (void)toggleCheckGrammarWithSpelling:(id)fp8;
- (void)showAddressPanel:(id)fp8;
- (void)windowDidResize:(id)fp8;
- (void)windowDidMove:(id)fp8;
- (id)shouldSaveTitle;
- (id)shouldSaveDescription;
- (id)shouldSaveHelptag;
- (void)beginDocumentMove;
- (void)endDocumentMove;
- (void)documentsWillBeginTransfer:(id)fp8;
- (void)documentsDidEndTransfer:(id)fp8;
- (BOOL)windowShouldClose:(id)fp8;
- (void)forceClose;
- (void)closeConfirmSheetDidEnd:(id)fp8 returnCode:(int)fp12 forSave:(void *)fp16;
- (void)nowWouldBeAGoodTimeToTerminate:(id)fp8;
- (double)lastSaveTime;
- (void)setLastSaveTime:(double)fp8;
- (id)loadDelegate;
- (void)setLoadDelegate:(id)fp8;
- (id)settings;
- (void)setSettings:(id)fp8;

@end

