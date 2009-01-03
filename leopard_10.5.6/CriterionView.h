/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "ColorBackgroundView.h"

#import "MailboxesChooserCycleDelegate-Protocol.h"

@class CriteriaUIHelper, MailboxUid, NSButton, NSDatePicker, NSMenu, NSPopUpButton, NSString, NSTextField, NSView;

@interface CriterionView : ColorBackgroundView <MailboxesChooserCycleDelegate>
{
    CriteriaUIHelper *owner;
    NSButton *removeButton;
    NSButton *addButton;
    NSView *headerCriteriaView;
    NSView *simpleCriteriaView;
    NSView *accountOrGroupView;
    NSView *mailboxesView;
    NSView *daysOldDatesView;
    NSView *simpleDatesView;
    NSView *daysAgoDatesView;
    NSView *inThelastDaysDatesView;
    NSView *daysAgoRangeDatesView;
    NSView *beforeAfterDatesView;
    NSView *dateRangeDatesView;
    NSView *messageTypeView;
    NSView *textToDoCriteriaView;
    NSView *simpleToDoCriteriaView;
    NSView *toDoCalendarView;
    NSView *toDoDaysAgoView;
    NSView *toDoInTheLastDaysView;
    NSView *toDoDateRangeView;
    NSView *toDoExactDateView;
    NSView *toDoMailboxesView;
    NSView *toDoSimpleDateView;
    NSView *currentView;
    NSPopUpButton *criterionPopUp;
    NSPopUpButton *qualifierPopUp;
    NSTextField *expressionStringField;
    NSTextField *expressionNumberField;
    NSTextField *expressionOtherNumberField;
    NSDatePicker *dateFieldPicker;
    NSDatePicker *otherDateFieldPicker;
    NSPopUpButton *unitsPopUp;
    NSMenu *criterionMenu;
    NSMenu *dateQualifierMenu;
    struct _NSRect defaultCriterionPopupFrame;
    struct _NSRect defaultQualifierPopupFrame;
    struct _NSRect defaultExpressionFieldFrame;
    BOOL isSmartMailboxCriterion;
    NSString *expressionGuess;
    MailboxUid *mailboxBeingEdited;
    int _criterionType;
    int _criterionTypeForOtherArea;
}

- (void)dealloc;
- (int)criterionType;
- (void)setCriterionType:(int)fp8;
- (id)mailboxBeingEdited;
- (void)awakeFromNib;
- (void)setIsSmartMailboxCriterion:(BOOL)fp8 mailbox:(id)fp12;
- (id)menuUsingInfo:(struct menuItemInfo *)fp8 length:(int)fp12;
- (void)configureForCriterion:(id)fp8;
- (id)criterion;
- (void)_setEnglishStringsForPopUpMenuHeaderItems:(id)fp8;
- (void)configureViewForQualifierTag:(int)fp8 criterion:(id)fp12;
- (void)insertBestGuessForExpressionField;
- (id)subcriteriaForRelativeDatesFrom:(int)fp8 to:(int)fp12 units:(int)fp16 criterionType:(int)fp20;
- (id)timeSince1970StringFromDatePicker:(id)fp8 atEndOfDay:(BOOL)fp12;
- (void)putHeaderCriteriaInPopUpMenu;
- (void)populateQualifierPopup;
- (void)qualifierPopupChanged:(id)fp8;
- (void)criterionPopupWillPopup:(id)fp8;
- (void)criterionPopupChanged:(id)fp8;
- (void)makeRemoveButtonEnabled:(BOOL)fp8;
- (void)setExpressionGuess:(id)fp8;
- (void)_mailboxCriterionPopUpChangedSelection:(id)fp8;
- (void)ownerSearchAreaChanged:(id)fp8;

@end

