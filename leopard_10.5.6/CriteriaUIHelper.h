/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSObject.h"

@class CriterionView, NSButton, NSMutableArray, NSPanel, NSPopUpButton, NSScrollView, NSString, NSTableView, NSTextField;

@interface CriteriaUIHelper : NSObject
{
    NSMutableArray *criteriaViews;
    NSTextField *nameField;
    NSScrollView *criteriaContainer;
    NSPopUpButton *allCriteriaMustBeMetPopUp;
    NSButton *includeTrashCheckbox;
    NSButton *includeSentCheckbox;
    NSTextField *performActionLabel;
    NSScrollView *actionContainer;
    CriterionView *criterionView;
    NSPanel *headerListPanel;
    NSTableView *headerListTable;
    NSButton *addHeaderButton;
    BOOL isEditingHeader;
    BOOL criteriaWillBeUsedForMailboxes;
    BOOL includeNoJunkCriterion;
    id _objectWithCriteria;
    int searchArea;
    NSString *previousTitle;
}

+ (id)packageUserCriteria:(id)fp8 withNoJunk:(BOOL)fp12 noTrash:(BOOL)fp16 noSent:(BOOL)fp20 allUserCriteriaMustBeSatisfied:(BOOL)fp24;
+ (void)unpackUserCriteria:(id *)fp8 noJunkCriterion:(id *)fp12 noTrashCriterion:(id *)fp16 noSentCriterion:(id *)fp20 allCriteriaMustBeSatisfield:(char *)fp24 fromCriteria:(id)fp28;
+ (id)headerList;
- (BOOL)criteriaWillBeUsedForMailboxes;
- (void)setCriteriaWillBeUsedForMailboxes:(BOOL)fp8;
- (void)dealloc;
- (void)awakeFromNib;
- (id)newCriterion;
- (void)putCriteriaFromUIIntoObject:(id)fp8;
- (void)sentMessagesMailboxCriterionAdded;
- (void)trashMailboxCriterionAdded;
- (void)configureCriteriaForObject:(id)fp8;
- (void)addCriterion:(id)fp8;
- (id)createNewCriterionViewForSender:(id)fp8;
- (void)removeCriterion:(id)fp8;
- (void)removeView:(id)fp8 fromViews:(id)fp12 inContainer:(id)fp16;
- (void)userHasSelectedSenderInAddressBook:(char *)fp8 senderInAddressHistory:(char *)fp12;
- (void)editHeaderList;
- (void)configureAllCriterionMenus;
- (void)resetHeaderListForObjectsWithCriteria:(id)fp8;
- (void)_endEditingHeader;
- (void)headerListOkClicked:(id)fp8;
- (void)headerListCancelClicked:(id)fp8;
- (void)updateHeaderListUI;
- (void)_headerTableBeganEditing:(id)fp8;
- (void)_headerTableEndedEditing:(id)fp8;
- (void)addHeaderClicked:(id)fp8;
- (int)numberOfRowsInTableView:(id)fp8;
- (id)tableView:(id)fp8 objectValueForTableColumn:(id)fp12 row:(int)fp16;
- (void)_removeInvalidHeaders;
- (void)tableView:(id)fp8 setObjectValue:(id)fp12 forTableColumn:(id)fp16 row:(int)fp20;
- (void)tileViews:(id)fp8 inContainer:(id)fp12 withChangeAtRow:(int)fp16 removeIsEnabled:(BOOL)fp20;
- (void)connectNextKeyViewChain;
- (void)setSearchArea:(int)fp8;
- (id)previousTitle;
- (void)setPreviousTitle:(id)fp8;
- (int)searchArea;

@end

