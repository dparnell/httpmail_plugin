/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class DeliveryAccount, NSButton, NSPopUpButton, NSSecureTextField, NSTextField;

@interface SMTPSettings : NSObject
{
    NSTextField *hostnameField;
    NSPopUpButton *authPopup;
    NSButton *sslSwitch;
    NSTextField *usernameField;
    NSSecureTextField *passwordField;
    NSTextField *portNumberField;
    NSButton *okButton;
    NSTextField *domainLabel;
    NSTextField *domainField;
    DeliveryAccount *_account;
}

- (void)_updateAuthenticationUIAnimatingPanelResize:(BOOL)fp8;
- (id)account;
- (void)authenticationChanged:(id)fp8;
- (void)controlTextDidChange:(id)fp8;
- (void)dealloc;
- (void)dismissPanel:(id)fp8;
- (void)runSheetRelativeToWindow:(id)fp8 didEndDelegate:(id)fp12;
- (void)setAccount:(id)fp8;
- (void)sheetDidEnd:(id)fp8 returnCode:(int)fp12 contextInfo:(void *)fp16;

@end

