/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "Assistant.h"

@class AccountSetupValidator, AccountSummary, AuthScheme, MailAccount, NSArray, NSAttributedString, NSDictionary, NSMutableArray, NSNumber, NSPopUpButton, NSString, NSTabView, NSView, SMTPAccount;

@interface AccountSetupAssistant : Assistant
{
    NSView *_topView;
    NSTabView *_tabView;
    NSView *_summaryContainerView;
    NSPopUpButton *_incomingTypePopUp;
    NSPopUpButton *_incomingAuthPopUp;
    NSPopUpButton *_outgoingAuthPopUp;
    NSView *_firstKeyViewForBasicInformation;
    NSView *_firstKeyViewForIncomingServer;
    NSView *_firstKeyViewForIncomingSecurity;
    NSView *_firstKeyViewForOutgoingServer;
    NSView *_firstKeyViewForOutgoingSecurity;
    NSView *_lastKeyViewForBasicInformation;
    NSView *_lastKeyViewForIncomingServer;
    NSView *_lastKeyViewForIncomingSecurity;
    NSView *_lastKeyViewForOutgoingServer;
    NSView *_lastKeyViewForOutgoingSecurity;
    NSView *_firstResponderForBasicInformation;
    NSView *_firstResponderForIncomingServer;
    BOOL _canUseSimplifiedSetup;
    BOOL _shouldUseSimplifiedSetup;
    BOOL _canGoBack;
    NSString *_nextButtonTitle;
    int _selectedTab;
    NSMutableArray *_previousTabs;
    NSDictionary *_receivingAccountInfo;
    NSDictionary *_deliveryAccountLookup;
    NSArray *_deliveryAccountKeys;
    MailAccount *_receivingAccount;
    SMTPAccount *_deliveryAccount;
    AccountSummary *_summary;
    AccountSetupValidator *_validator;
    int _receivingValidationStatus;
    int _deliveryValidationStatus;
    NSString *_windowTitle;
    NSString *_firstPaneTitle;
    NSString *_firstPaneDescription;
    NSView *_simplifiedAccountSetupCheckBoxSection;
    NSString *_name;
    NSString *_emailAddress;
    NSString *_password;
    BOOL _isEmailAddressValid;
    int _incomingAccountClassIndex;
    NSString *_incomingDescription;
    NSString *_incomingMailServer;
    NSString *_incomingUserName;
    NSString *_incomingOutlookServer;
    NSNumber *_incomingPortNumber;
    BOOL _isIncomingMailServerValid;
    BOOL _isIncomingUserNameValid;
    BOOL _isIncomingOutlookServerValid;
    BOOL _hideIncomingOutlookServer;
    BOOL _hideExchange;
    BOOL _hideDotMac;
    BOOL _incomingAuthUseSSL;
    AuthScheme *_incomingAuthScheme;
    NSString *_incomingAuthDomainName;
    NSString *_outgoingDescription;
    NSString *_outgoingMailServer;
    BOOL _outgoingUseOnly;
    BOOL _outgoingUseAuthentication;
    NSString *_outgoingUserName;
    NSString *_outgoingPassword;
    NSNumber *_outgoingPortNumber;
    BOOL _isOutgoingMailServerValid;
    BOOL _outgoingAuthUseSSL;
    AuthScheme *_outgoingAuthScheme;
    NSString *_outgoingAuthDomainName;
    NSAttributedString *_statusMessage;
    BOOL _showStatusAlert;
    BOOL _takeAccountOnline;
}

- (id)initWithAssistentManager:(id)fp8 isForStartup:(BOOL)fp12;
- (void)dealloc;
- (id)_usernameForEmailAddress:(id)fp8 ispAccount:(id)fp12;
- (void)_syncBindings;
- (void)_setupLegacyStuff;
- (void)_animateSimplifiedSetupCheckBox;
- (id)_statusMessageAttributes;
- (id)_statusMessageWithString:(id)fp8;
- (void)_clearPropertyValues;
- (void)_loadDefaultPropertyValues;
- (void)_loadPropertiesFromReceivingInfo:(id)fp8;
- (void)_loadPropertiesFromDeliveryInfo:(id)fp8 reset:(BOOL)fp12;
- (void)_updateAccountsFromPropertiesAtTab:(int)fp8;
- (BOOL)_shouldSkip:(int)fp8;
- (void)start;
- (void)stop;
- (void)goForward;
- (void)goBackward;
- (BOOL)shouldStop;
- (void)_pushTab:(int)fp8;
- (int)_popTab;
- (void)setupKeyViewLoop;
- (BOOL)_validateTab:(int)fp8;
- (void)_registerObservers;
- (void)_unregisterObservers;
- (void)observeValueForKeyPath:(id)fp8 ofObject:(id)fp12 change:(id)fp16 context:(void *)fp20;
- (BOOL)validateOutgoingMailServer:(id *)fp8 error:(id *)fp12;
- (void)_updateNextButtonTitle;
- (void)_updateDeliveryAccountLookupFromInfos:(id)fp8;
- (void)_updateAccountInfoFromEmailAddress;
- (void)_validateReceivingAccount;
- (void)_validateDeliveryAccount;
- (void)_clearValidator;
- (void)_extractSecuritySettingsFromValidator:(id)fp8;
- (void)validator:(id)fp8 didChangeState:(int)fp12;
- (void)validatorDidFail:(id)fp8;
- (void)validatorDidFinish:(id)fp8;
- (void)_addNewAccount;
- (BOOL)takeAccountOnline;
- (void)setTakeAccountOnline:(BOOL)fp8;
- (BOOL)showStatusAlert;
- (void)setShowStatusAlert:(BOOL)fp8;
- (id)statusMessage;
- (void)setStatusMessage:(id)fp8;
- (id)outgoingAuthDomainName;
- (void)setOutgoingAuthDomainName:(id)fp8;
- (id)outgoingAuthScheme;
- (void)setOutgoingAuthScheme:(id)fp8;
- (BOOL)outgoingAuthUseSSL;
- (void)setOutgoingAuthUseSSL:(BOOL)fp8;
- (BOOL)isOutgoingMailServerValid;
- (void)setIsOutgoingMailServerValid:(BOOL)fp8;
- (id)outgoingPortNumber;
- (void)setOutgoingPortNumber:(id)fp8;
- (id)outgoingPassword;
- (void)setOutgoingPassword:(id)fp8;
- (id)outgoingUserName;
- (void)setOutgoingUserName:(id)fp8;
- (BOOL)outgoingUseAuthentication;
- (void)setOutgoingUseAuthentication:(BOOL)fp8;
- (BOOL)outgoingUseOnly;
- (void)setOutgoingUseOnly:(BOOL)fp8;
- (id)outgoingMailServer;
- (void)setOutgoingMailServer:(id)fp8;
- (id)outgoingDescription;
- (void)setOutgoingDescription:(id)fp8;
- (id)incomingAuthDomainName;
- (void)setIncomingAuthDomainName:(id)fp8;
- (id)incomingAuthScheme;
- (void)setIncomingAuthScheme:(id)fp8;
- (BOOL)incomingAuthUseSSL;
- (void)setIncomingAuthUseSSL:(BOOL)fp8;
- (BOOL)hideDotMac;
- (void)setHideDotMac:(BOOL)fp8;
- (BOOL)hideExchange;
- (void)setHideExchange:(BOOL)fp8;
- (BOOL)hideIncomingOutlookServer;
- (void)setHideIncomingOutlookServer:(BOOL)fp8;
- (BOOL)isIncomingOutlookServerValid;
- (void)setIsIncomingOutlookServerValid:(BOOL)fp8;
- (BOOL)isIncomingUserNameValid;
- (void)setIsIncomingUserNameValid:(BOOL)fp8;
- (BOOL)isIncomingMailServerValid;
- (void)setIsIncomingMailServerValid:(BOOL)fp8;
- (id)incomingPortNumber;
- (void)setIncomingPortNumber:(id)fp8;
- (id)incomingOutlookServer;
- (void)setIncomingOutlookServer:(id)fp8;
- (id)incomingUserName;
- (void)setIncomingUserName:(id)fp8;
- (id)incomingMailServer;
- (void)setIncomingMailServer:(id)fp8;
- (id)incomingDescription;
- (void)setIncomingDescription:(id)fp8;
- (int)incomingAccountClassIndex;
- (void)setIncomingAccountClassIndex:(int)fp8;
- (BOOL)isEmailAddressValid;
- (void)setIsEmailAddressValid:(BOOL)fp8;
- (id)password;
- (void)setPassword:(id)fp8;
- (id)emailAddress;
- (void)setEmailAddress:(id)fp8;
- (id)name;
- (void)setName:(id)fp8;
- (id)firstPaneDescription;
- (void)setFirstPaneDescription:(id)fp8;
- (id)firstPaneTitle;
- (void)setFirstPaneTitle:(id)fp8;
- (id)windowTitle;
- (void)setWindowTitle:(id)fp8;
- (int)deliveryValidationStatus;
- (void)setDeliveryValidationStatus:(int)fp8;
- (int)receivingValidationStatus;
- (void)setReceivingValidationStatus:(int)fp8;
- (id)validator;
- (void)setValidator:(id)fp8;
- (id)summary;
- (void)setSummary:(id)fp8;
- (id)deliveryAccount;
- (void)setDeliveryAccount:(id)fp8;
- (id)receivingAccount;
- (void)setReceivingAccount:(id)fp8;
- (id)deliveryAccountKeys;
- (void)setDeliveryAccountKeys:(id)fp8;
- (id)deliveryAccountLookup;
- (void)setDeliveryAccountLookup:(id)fp8;
- (id)receivingAccountInfo;
- (void)setReceivingAccountInfo:(id)fp8;
- (id)previousTabs;
- (void)setPreviousTabs:(id)fp8;
- (int)selectedTab;
- (void)setSelectedTab:(int)fp8;
- (id)nextButtonTitle;
- (void)setNextButtonTitle:(id)fp8;
- (BOOL)canGoBack;
- (void)setCanGoBack:(BOOL)fp8;
- (BOOL)shouldUseSimplifiedSetup;
- (void)setShouldUseSimplifiedSetup:(BOOL)fp8;
- (BOOL)canUseSimplifiedSetup;
- (void)setCanUseSimplifiedSetup:(BOOL)fp8;

@end

