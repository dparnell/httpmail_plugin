/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class MailboxUid, NSPopUpButton;

@interface MailboxesChooser : NSObject
{
    NSPopUpButton *popUpButton;
    MailboxUid *_selectedMailbox;
    MailboxUid *_targetMailboxForCycleChecks;
    BOOL includeSmartMailboxes;
    id _realTarget;
    SEL _realAction;
}

- (void)_cancelMenuTracking:(id)fp8;
- (void)_ensureSelectionIsValid:(id)fp8;
- (void)_mailboxWasRenamed:(id)fp8;
- (void)_popUpPressed:(id)fp8;
- (void)awakeFromNib;
- (void)cellWillPopUp:(id)fp8;
- (void)dealloc;
- (void)disableCyclicItemsInMenu:(id)fp8;
- (void)disableCyclicMailboxesInItems:(id)fp8;
- (id)popUpButton;
- (void)reset;
- (id)selectedMailbox;
- (void)setIncludesSmartMailboxes:(BOOL)fp8;
- (void)setPopUpButton:(id)fp8;
- (void)setSelectedMailbox:(id)fp8;
- (void)setShouldCheckCyclesToSmartMailbox:(id)fp8;

@end

