/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSPreferencesModule.h"

@class ColorBackgroundView, EditingMessageWebView, EditingWebMessageController, MailAccount, NSButton, NSPopUpButton, NSString, NSTableView, NSTextField, WebArchive;

@interface SignaturePreferences : NSPreferencesModule
{
    NSTableView *_signaturesTable;
    NSTableView *_accountsTable;
    NSPopUpButton *_selectPopup;
    ColorBackgroundView *_webViewBackground;
    EditingMessageWebView *_webView;
    EditingWebMessageController *_controller;
    NSButton *_textRichnessButton;
    NSTextField *_textRichnessMessageField;
    NSButton *_removeButton;
    NSButton *_placeSignatureAboveQuote;
    unsigned int _addingNewSignature:1;
    unsigned int _appIsTerminating:1;
    unsigned int _loadedInitialHTML:1;
    MailAccount *_selectedAccount;
    MailAccount *_allSignaturesAccount;
    NSString *defaultFontName;
    WebArchive *savedWebArchive;
    BOOL _currentSignatureHasChanges;
}

- (void)dealloc;
- (id)titleForIdentifier:(id)fp8;
- (id)windowTitle;
- (id)imageForPreferenceNamed:(id)fp8;
- (void)_validateButtonState;
- (void)defaultSignatureChanged:(id)fp8;
- (void)initializeFromDefaults;
- (void)setSelectedAccount:(id)fp8;
- (void)saveChanges;
- (void)nowWouldBeAGoodTimeToTerminate:(id)fp8;
- (void)willBeDisplayed;
- (void)moduleWasInstalled;
- (BOOL)moduleCanBeRemoved;
- (void)moduleWillBeRemoved;
- (BOOL)preferencesWindowShouldClose;
- (void)registerForNotifications;
- (void)unregisterForNotifications;
- (void)accountsDidChange:(id)fp8;
- (void)awakeFromNib;
- (void)determineDefaultFontName;
- (void)defaultFontMayHaveChanged:(id)fp8;
- (void)createSignature:(id)fp8;
- (id)defaultSignatureContentForSelectedAccount;
- (BOOL)endEditingOfSignatureOkayToReload:(BOOL)fp8 needsToReload:(char *)fp12;
- (void)removeSignatureSheetDidEnd:(id)fp8 returnCode:(int)fp12 contextInfo:(void *)fp16;
- (void)deleteKey:(id)fp8;
- (void)removeSignature:(id)fp8;
- (BOOL)allowsRichText;
- (void)changeSignatureRichness:(id)fp8;
- (BOOL)dataWillBeSynced;
- (void)dataWasSynced;
- (void)webViewDidChangeTypingStyle:(id)fp8;
- (void)webViewDidChange:(id)fp8;
- (void)_updatePopup;
- (BOOL)validateMenuItem:(id)fp8;
- (void)placeSignatureAboveQuotedText:(id)fp8;
- (BOOL)_validateValuesInUI;
- (void)_updateWebView;
- (void)webView:(id)fp8 didFinishLoadForFrame:(id)fp12;
- (BOOL)webView:(id)fp8 shouldInsertNode:(id)fp12 replacingDOMRange:(id)fp16 givenAction:(int)fp20;
- (id)webView:(id)fp8 shouldReplaceSelectionWithWebArchive:(id)fp12 givenAction:(int)fp16;
- (void)webView:(id)fp8 didAddMailAttachment:(id)fp12;
- (void)webView:(id)fp8 didFailLoadWithError:(id)fp12 forFrame:(id)fp16;
- (void)webView:(id)fp8 didFailProvisionalLoadWithError:(id)fp12 forFrame:(id)fp16;
- (id)webArchiveForEditedSignature;
- (void)displaySelectedSignatureDetails;
- (int)numberOfRowsInTableView:(id)fp8;
- (void)tableView:(id)fp8 willDisplayCell:(id)fp12 forTableColumn:(id)fp16 row:(int)fp20;
- (id)truncatingAttributes;
- (id)tableView:(id)fp8 objectValueForTableColumn:(id)fp12 row:(int)fp16;
- (void)tableView:(id)fp8 setObjectValue:(id)fp12 forTableColumn:(id)fp16 row:(int)fp20;
- (BOOL)control:(id)fp8 textView:(id)fp12 doCommandBySelector:(SEL)fp16;
- (BOOL)selectionShouldChangeInTableView:(id)fp8;
- (void)tableViewSelectionDidChange:(id)fp8;
- (BOOL)tableView:(id)fp8 writeRows:(id)fp12 toPasteboard:(id)fp16;
- (unsigned int)tableView:(id)fp8 validateDrop:(id)fp12 proposedRow:(int)fp16 proposedDropOperation:(unsigned int)fp20;
- (BOOL)tableView:(id)fp8 acceptDrop:(id)fp12 row:(int)fp16 dropOperation:(unsigned int)fp20;
- (float)splitView:(id)fp8 constrainMinCoordinate:(float)fp12 ofSubviewAt:(int)fp16;
- (float)splitView:(id)fp8 constrainMaxCoordinate:(float)fp12 ofSubviewAt:(int)fp16;
- (void)splitView:(id)fp8 resizeSubviewsWithOldSize:(struct _NSSize)fp12;

@end

