/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import <Message/Criterion.h>

@interface Criterion (LibraryAdditions)
- (BOOL)isExpressibleInTigerSchema;
- (id)criterionExpressionForEqualRelativeDates:(CDAnonymousStruct1 *)fp8 depth:(unsigned int)fp12 enclosingSmartMailboxes:(id)fp16;
- (id)criterionValueForNotEqualRelativeDates:(int *)fp8;
- (id)criterionForSQL;
- (id)SQLExpressionWithTables:(unsigned int *)fp8 baseTable:(unsigned int)fp12;
- (unsigned int)bestBaseTable;
@end
