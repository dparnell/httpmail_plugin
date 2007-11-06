/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSSpellChecker.h"

@interface ComposeSpellChecker : NSSpellChecker
{
}

- (void)setPostCompletedNotification:(BOOL)fp8 forSpellDocumentWithTag:(int)fp12;
- (int)currentSpellDocumentTag;
- (void)_mail_postingTimerFired:(id)fp8;
- (void)_mail_spellPanelDidClose:(id)fp8;
- (struct _NSRange)checkSpellingOfString:(id)fp8 startingAt:(int)fp12 language:(id)fp16 wrap:(BOOL)fp20 inSpellDocumentWithTag:(int)fp24 wordCount:(int *)fp28;
- (id)spellingPanel;
- (void)closeSpellDocumentWithTag:(int)fp8;

@end

