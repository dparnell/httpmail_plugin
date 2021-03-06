/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@class NSArray, NSDictionary, NSOpenPanel, NSPopUpButton, NSURL;

@interface DefaultWebAppPopUpController : NSObject
{
    NSPopUpButton *_defaultWebApp;
    NSOpenPanel *_selectAppPanel;
    NSDictionary *_webApp;
    int _webIndex;
    NSArray *_schemes;
    NSArray *_fileExtensions;
    unsigned int _OSType;
    NSURL *_sampleURL;
}

- (struct __CFURL *)urlForEntry:(id)fp8;
- (int)indexOfItemInPopUp:(id)fp8 closestToValue:(id)fp12;
- (void)setAppPopUp:(id)fp8 toValue:(id)fp12;
- (BOOL)handleApplicationPopUp:(id)fp8 withSheetDidEndSelector:(SEL)fp12;
- (BOOL)populateSchemeHandlerPopupWithURL:(id)fp8 forPopup:(id)fp12;
- (void)populateWebPopUpWithDefault;
- (id)dictionaryForScheme:(id)fp8;
- (void)setHandler:(id)fp8 forScheme:(id)fp12 saveAndRefresh:(BOOL)fp16;
- (void)setDefaultLSWeakBindingsForApp:(id)fp8;
- (void)setNewWebApplication;
- (void)webAppSheetDidEnd:(id)fp8 returnCode:(int)fp12 contextInfo:(void *)fp16;
- (void)webApplicationSelected:(id)fp8;
- (void)populatePopUp;
- (void)showDefaultInPopUp;
- (id)initWithPopUp:(id)fp8 schemes:(id)fp12 fileExtensions:(id)fp16 OSType:(unsigned long)fp20 sampleURL:(id)fp24;
- (void)dealloc;
- (void)menuNeedsUpdate:(id)fp8;
- (BOOL)menuHasKeyEquivalent:(id)fp8 forEvent:(id)fp12 target:(id *)fp16 action:(SEL *)fp20;

@end

