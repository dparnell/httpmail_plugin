/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class NSButton, NSMenu, NSMutableArray, NSNumberFormatter, NSPanel, NSPopUpButton, NSScrollView, NSTableView, NSTextField;

@interface CriteriaUIHelper : NSObject
{
    NSMutableArray *criteriaViews;
    NSMutableArray *criteriaGuesses;
    NSTextField *nameField;
    NSScrollView *criteriaContainer;
    NSPopUpButton *allCriteriaMustBeMetPopUp;
    NSButton *includeTrashCheckbox;
    NSButton *includeSentCheckbox;
    NSTextField *performActionLabel;
    NSScrollView *actionContainer;
    NSPopUpButton *smartMailboxesCriterionPopUp;
    NSNumberFormatter *smartMailboxesNumberFormatter;
    id loadedView;
    NSMenu *sizeQualifierMenu;
    NSMenu *dateQualifierMenu;
    NSMenu *mailboxesQualifierMenu;
    id expressionNumberView;
    id expressionDateView;
    NSMutableArray *headerList;
    NSMenu *qualifierMenu;
    NSMenu *accountOrGroupMenu;
    struct _NSRect defaultCriterionPopupFrame;
    struct _NSRect defaultQualifierPopupFrame;
    struct _NSRect defaultExpressionFieldFrame;
    NSPanel *headerListPanel;
    NSTableView *headerListTable;
    NSButton *addHeaderButton;
    NSButton *removeHeaderButton;
    BOOL isEditingHeader;
    BOOL criteriaWillBeUsedForMailboxes;
    BOOL includeNoJunkCriterion;
    id _objectWithCriteria;
}

+ (id)noJunkCriterion;
+ (id)noSentCriterion;
+ (id)noTrashCriterion;
+ (id)packageUserCriteria:(id)fp8 withNoJunk:(BOOL)fp12 noTrash:(BOOL)fp16 noSent:(BOOL)fp20 allUserCriteriaMustBeSatisfied:(BOOL)fp24;
+ (void)unpackUserCriteria:(id *)fp8 noJunkCriterion:(id *)fp12 noTrashCriterion:(id *)fp16 noSentCriterion:(id *)fp20 allCriteriaMustBeSatisfield:(char *)fp24 fromCriteria:(id)fp28;
- (void)_endEditingHeader;
- (void)_fixupLocalizedCriteriaInPopUp:(id)fp8;
- (void)_headerTableBeganEditing:(id)fp8;
- (void)_headerTableEndedEditing:(id)fp8;
- (void)_removeInvalidHeaders;
- (void)addCriterion:(id)fp8;
- (void)addHeaderClicked:(id)fp8;
- (void)awakeFromNib;
- (void)configureAllCriterionMenus;
- (void)configureCriteriaForObject:(id)fp8;
- (void)configureCriterionPopupMenu:(id)fp8;
- (void)configureCriterionView:(id)fp8;
- (void)configureDateQualifierExpressionViewsInView:(id)fp8;
- (void)configureQualifierPopupForCriterionPopupInRow:(int)fp8;
- (void)connectNextKeyViewChain;
- (void)criterionPopupChanged:(id)fp8;
- (void)criterionPopupWillPopup:(id)fp8;
- (id)dateStringFromTextField:(id)fp8 atEndOfDay:(BOOL)fp12;
- (void)dealloc;
- (void)headerListCancelClicked:(id)fp8;
- (void)headerListOkClicked:(id)fp8;
- (void)layOutUnitsAndDateFieldsInCriterionView:(id)fp8;
- (int)numberOfRowsInTableView:(id)fp8;
- (void)putCriteriaFromUIIntoObject:(id)fp8;
- (void)qualifierPopupChanged:(id)fp8;
- (void)removeCriterion:(id)fp8;
- (void)removeHeaderClicked:(id)fp8;
- (void)removeView:(id)fp8 fromViews:(id)fp12 inContainer:(id)fp16;
- (void)reorderSubviewsOfCriterionView:(id)fp8;
- (void)resetHeaderListForObjectsWithCriteria:(id)fp8;
- (void)setCriteriaWillBeUsedForMailboxes:(BOOL)fp8;
- (id)specificationKeyForView:(id)fp8;
- (id)subcriteriaForRelativeDatesFrom:(int)fp8 to:(int)fp12 units:(int)fp16 criterionType:(int)fp20;
- (id)subviewForString:(id)fp8 inView:(id)fp12;
- (id)tableView:(id)fp8 objectValueForTableColumn:(id)fp12 row:(int)fp16;
- (void)tableView:(id)fp8 setObjectValue:(id)fp12 forTableColumn:(id)fp16 row:(int)fp20;
- (void)tileViews:(id)fp8 inContainer:(id)fp12 withChangeAtRow:(int)fp16 removeIsEnabled:(BOOL)fp20;
- (void)updateHeaderListUI;

@end

