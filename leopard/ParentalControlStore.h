/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import <Message/NeXTMbox.h>

@interface ParentalControlStore : NeXTMbox
{
}

- (BOOL)_shouldCallCompactWhenClosing;
- (id)_defaultRouterDestination;
- (id)realAccount;
- (void)setParentalControlMessageState:(int)fp8 forMessage:(id)fp12;
- (void)setParentalControlMessageState:(int)fp8 forMessages:(id)fp12;
- (void)saveChanges;

@end

