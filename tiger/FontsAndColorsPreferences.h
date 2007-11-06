/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSPreferencesModule.h"

@class NSArray, NSButton, NSComboBox, NSPopUpButton, NSTextView;

@interface FontsAndColorsPreferences : NSPreferencesModule
{
    NSPopUpButton *listFontPopup;
    NSComboBox *listFontSizePopup;
    NSPopUpButton *messageFontPopup;
    NSComboBox *messageFontSizePopup;
    NSPopUpButton *fixedPitchFontPopup;
    NSComboBox *fixedPitchFontSizePopup;
    NSButton *fixedPitchSwitch;
    NSPopUpButton *colorPopupOne;
    NSPopUpButton *colorPopupTwo;
    NSPopUpButton *colorPopupThree;
    NSPopUpButton *lastColorPopupSelected;
    NSButton *colorQuotesButton;
    NSTextView *exampleTextView;
    NSArray *colorList;
    BOOL colorizeIncomingMail;
}

- (void)_setColor:(id)fp8 forPopup:(id)fp12;
- (void)_setFontMenuForPopup:(id)fp8 fixedPitchOnly:(BOOL)fp12;
- (void)_setOtherColor:(id)fp8 forPopup:(id)fp12;
- (void)_setTitle:(id)fp8 forComboBox:(id)fp12;
- (BOOL)_setTitle:(id)fp8 forPopup:(id)fp12;
- (void)_updateColorList;
- (void)_updateExampleColors;
- (void)awakeFromNib;
- (void)colorPicked:(id)fp8;
- (void)colorPopupChanged:(id)fp8;
- (void)colorQuotesButtonClicked:(id)fp8;
- (void)fixedPitchFontChanged:(id)fp8;
- (void)fontPopupChanged:(id)fp8;
- (void)initializeFromDefaults;
- (BOOL)isResizable;
- (void)listFontChanged:(id)fp8;
- (void)listFontSizeChanged:(id)fp8;
- (void)messageFontChanged:(id)fp8;
- (void)setFixedPitchFont:(id)fp8 size:(float)fp12;
- (void)setMessageFont:(id)fp8 size:(float)fp12;
- (id)titleForIdentifier:(id)fp8;
- (void)useFixedPitchFontClicked:(id)fp8;
- (id)windowTitle;

@end

