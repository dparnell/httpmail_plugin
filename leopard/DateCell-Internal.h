/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "DateCell.h"

@interface DateCell (Internal)
- (void)_generalInit;
- (void)setLastFont:(id)fp8;
- (float)_widthOfStringWithTimeFormat:(id)fp8 withDatePrefix:(id)fp12;
- (float)_widthOfLongestDateStringWithLevel:(int)fp8 format:(id)fp12;
- (void)_saveWidthsToDefaults;
- (BOOL)_readWidthsFromDefaults;
- (void)_updateDateColumnDetailLevelWidths;
- (void)_updateDateColumnDetailLevels;
@end

