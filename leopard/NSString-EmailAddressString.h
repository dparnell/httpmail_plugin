/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSString.h"

@interface NSString (EmailAddressString)
+ (id)nameExtensions;
+ (id)nameExtensionsThatDoNotNeedCommas;
+ (id)partialSurnames;
+ (id)formattedAddressWithName:(id)fp8 email:(id)fp12 useQuotes:(BOOL)fp16;
- (id)uncommentedAddress;
- (id)uncommentedAddressRespectingGroups;
- (BOOL)isEmptyGroup;
- (id)addressComment;
- (void)firstName:(id *)fp8 middleName:(id *)fp12 lastName:(id *)fp16 extension:(id *)fp20;
- (BOOL)appearsToBeAnInitial;
- (id)addressList;
- (id)trimCommasSpacesQuotes;
- (id)componentsSeparatedByCommaRespectingQuotesAndParens;
- (id)componentsSeparatedByCharactersRespectingQuotesAndParens:(id)fp8;
- (id)searchStringComponents;
- (BOOL)isLegalEmailAddress;
- (id)addressDomain;
@end

