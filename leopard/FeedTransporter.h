/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@class NSDate, NSError, NSString, NSTimeZone, NSURL;

@interface FeedTransporter : NSObject
{
    NSString *title;
    NSString *identifier;
    NSURL *alternateURL;
    NSURL *URL;
    NSError *lastError;
    NSDate *dateUpdated;
    NSTimeZone *timeZoneUpdated;
}

+ (id)transporterWithFeed:(id)fp8;
- (void)dealloc;
- (id)initWithFeed:(id)fp8;
- (id)timeZoneUpdated;
- (void)setTimeZoneUpdated:(id)fp8;
- (id)dateUpdated;
- (void)setDateUpdated:(id)fp8;
- (id)lastError;
- (void)setLastError:(id)fp8;
- (id)URL;
- (void)setURL:(id)fp8;
- (id)alternateURL;
- (void)setAlternateURL:(id)fp8;
- (id)identifier;
- (void)setIdentifier:(id)fp8;
- (id)title;
- (void)setTitle:(id)fp8;

@end

