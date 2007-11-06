#import <Cocoa/Cocoa.h>

@protocol NSPreferencesModule
- (void)moduleWasInstalled;
- (void)moduleWillBeRemoved;
- (void)didChange;
- (void)initializeFromDefaults;
- (void)willBeDisplayed;
- (void)saveChanges;
- (char)hasChangesPending;
- imageForPreferenceNamed:fp12;
- viewForPreferenceNamed:fp12;
@end

@interface NSPreferencesModule:NSObject <NSPreferencesModule>
{
    NSBox *_preferencesView;
    struct _NSSize _minSize;
    char _hasChanges;
    void *_reserved;
}

+ sharedInstance;
- (void)dealloc;
- init;
- preferencesNibName;
- (void)setPreferencesView:fp12;
- viewForPreferenceNamed:fp12;
- imageForPreferenceNamed:fp12;
- titleForIdentifier:fp12;
- (char)hasChangesPending;
- (void)saveChanges;
- (void)willBeDisplayed;
- (void)initializeFromDefaults;
- (void)didChange;
- (struct _NSSize)minSize;
- (void)moduleWillBeRemoved;
- (void)moduleWasInstalled;
- (char)isResizable;

@end

@interface NSPreferences:NSObject
{
    NSWindow *_preferencesPanel;
    NSBox *_preferenceBox;
    NSMatrix *_moduleMatrix;
    NSButtonCell *_okButton;
    NSButtonCell *_cancelButton;
    NSButtonCell *_applyButton;
    NSMutableArray *_preferenceTitles;
    NSMutableArray *_preferenceModules;
    NSMutableDictionary *_masterPreferenceViews;
    NSMutableDictionary *_currentSessionPreferenceViews;
    NSBox *_originalContentView;    
    char _isModal;
    float _constrainedWidth;
    id _currentModule;
    void *_reserved;
}

+ sharedPreferences;
+ (void)setDefaultPreferencesClass:(Class)fp8;
+ (Class)defaultPreferencesClass;
- init;
- (void)dealloc;
- (void)addPreferenceNamed:fp8 owner:fp12;
- (void)_setupToolbar;
- (void)_setupUI;
- (struct _NSSize)preferencesContentSize;
- (void)showPreferencesPanel;
- (void)showPreferencesPanelForOwner:fp8;
- (int)showModalPreferencesPanelForOwner:fp8;
- (int)showModalPreferencesPanel;
- (void)ok:fp8;
- (void)cancel:fp8;
- (void)apply:fp8;
- (void)_selectModuleOwner:fp8;
- windowTitle;
- (void)confirmCloseSheetIsDone:fp8 returnCode:(int)fp12 contextInfo:(void *)fp16;
- (char)windowShouldClose:fp8;
- (void)windowDidResize:fp8;
- (NSSize)windowWillResize:fp8 toSize:(NSSize)fp12;
- (char)usesButtons;
- _itemIdentifierForModule:fp8;
- (void)toolbarItemClicked:fp8;
- toolbar:fp8 itemForItemIdentifier:fp12 willBeInsertedIntoToolbar:(char)fp16;
- toolbarDefaultItemIdentifiers:fp8;
- toolbarAllowedItemIdentifiers:fp8;
- toolbarSelectableItemIdentifiers:fp8;

@end
