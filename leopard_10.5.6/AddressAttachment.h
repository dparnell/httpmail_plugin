/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "NSTextAttachment.h"

@class NSFont, NSString;

@interface AddressAttachment : NSTextAttachment
{
    NSString *address;
    NSString *name;
    int type;
    id addressBookRecord;
    BOOL isInitializing;
    BOOL suppressNotifications;
    BOOL isSenderAddress;
    BOOL isOriginalSenderAddress;
    BOOL knownToHaveNoRecord;
    BOOL shouldDisplayFullAddress;
    NSFont *preferredFont;
}

+ (void)initialize;
+ (void)getRecordsForAddresses:(id)fp8;
+ (id)attributesForType:(int)fp8;
+ (void)resetAttributes;
+ (BOOL)addressIsExternal:(id)fp8;
+ (id)colorForExternalDomain;
+ (int)addressDisplayMode;
+ (void)setAddressDisplayMode:(int)fp8;
- (id)initWithAddress:(id)fp8 record:(id)fp12 type:(int)fp16;
- (id)initWithAddress:(id)fp8 record:(id)fp12 type:(int)fp16 showComma:(BOOL)fp20;
- (id)initWithFileWrapper:(id)fp8;
- (id)copyWithZone:(struct _NSZone *)fp8;
- (void)dealloc;
- (void)adjustFontSizeBy:(int)fp8;
- (id)drawingAttributes;
- (BOOL)isInitializing;
- (void)setAddress:(id)fp8;
- (id)address;
- (id)pasteboardString;
- (id)nonemptyAddress;
- (void)setName:(id)fp8;
- (id)name;
- (id)formattedAddress;
- (id)quotedFormattedAddress;
- (id)nameOrAddressForDisplay;
- (id)addressDomain;
- (void)writeToPasteboard:(id)fp8;
- (id)vCardString;
- (id)vCardRepresentation;
- (id)dictionaryRepresentation;
- (BOOL)hasToolTip;
- (id)toolTip;
- (int)type;
- (void)addressDisplayModeChanged:(id)fp8;
- (void)setAddressBookRecord:(id)fp8;
- (id)addressBookRecord;
- (void)removeAddressBookRecord;
- (void)setKnownToHaveNoRecord:(BOOL)fp8;
- (BOOL)knownToHaveNoRecord;
- (BOOL)isInAddressBook;
- (BOOL)isSenderAddress;
- (void)setIsSenderAddress;
- (BOOL)isOriginalSenderAddress;
- (void)setIsOriginalSenderAddress;
- (void)domainForMatchingDidChange;
- (BOOL)isSelected;
- (void)setIsSelected:(BOOL)fp8;
- (void)setRightSideHasSelectedText:(BOOL)fp8;
- (void)setRightSideHasSelectedAtom:(BOOL)fp8;
- (void)setLeftSideHasSelection:(BOOL)fp8;
- (id)attachmentCell;
- (void)onlinePresenceChanged:(id)fp8;
- (void)antialiasingSettingsChanged:(id)fp8;

@end
