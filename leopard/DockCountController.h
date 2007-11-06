/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@class MailboxUid;

@interface DockCountController : NSObject
{
    MailboxUid *_mailBadgeMailbox;
    int _mailBadgeScope;
}

+ (id)sharedInstance;
- (void)dealloc;
- (id)init;
- (void)clearCountAndStopUpdating;
- (void)_setDockBadgeForCount:(id)fp8;
- (void)_mailboxWillBeInvalidated:(id)fp8;
- (void)_setMailBadgeMailbox:(id)fp8;
- (id)mailBadgeMailbox;
- (void)_updateUnreadCount;
- (void)unreadCountChanged:(id)fp8;
- (int)mailBadgeScope;
- (void)setMailBadgeScope:(int)fp8 mailbox:(id)fp12;

@end

