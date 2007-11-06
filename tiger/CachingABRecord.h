/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSObject.h"

@class ABRecord, NSMutableArray, NSMutableDictionary;

@interface CachingABRecord : NSObject
{
    ABRecord *record;
    NSMutableDictionary *propertyValues;
    NSMutableArray *matchingEmails;
    CachingABRecord *associatedRecord;
}

- (id)_fullName;
- (void)addMatchingEmail:(id)fp8;
- (id)associatedRecord;
- (id)compoundName;
- (id)compoundNameAndEmail;
- (void)dealloc;
- (id)email;
- (id)emailAddresses;
- (BOOL)exactlyMatchesString:(id)fp8;
- (id)extension;
- (void)finalize;
- (id)firstAndMiddleNames;
- (id)firstName;
- (void)forwardInvocation:(id)fp8;
- (BOOL)hasEmailAddress:(id)fp8;
- (BOOL)hasHandles;
- (BOOL)hasRelatedAddressBookRecord;
- (id)initWithABRecord:(id)fp8;
- (BOOL)isEqual:(id)fp8;
- (BOOL)isGroup;
- (BOOL)isRecentRecord;
- (id)lastName;
- (id)lastNameAndExtension;
- (id)matchingEmails;
- (id)methodSignatureForSelector:(SEL)fp8;
- (id)middleName;
- (id)mostRecentDate;
- (id)record;
- (int)recordType;
- (BOOL)setValue:(id)fp8 forProperty:(id)fp12;
- (id)uniqueId;
- (id)valueForProperty:(id)fp8;

@end

