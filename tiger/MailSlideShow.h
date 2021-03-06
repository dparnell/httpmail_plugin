/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "GenericAttachmentFetcher.h"

@interface MailSlideShow : GenericAttachmentFetcher
{
    BOOL _isPlaying;
}

+ (BOOL)canDoSlideShow;
+ (void)initialize;
+ (id)slideShowWithAttachments:(id)fp8;
- (id)_realFileWrapperAtIndex:(int)fp8;
- (void)_slideshowStopped:(id)fp8;
- (BOOL)canExportObjectAtIndexToiPhoto:(int)fp8;
- (void)dealloc;
- (void)didFinishBackgroundLoadOfAttachment:(id)fp8;
- (void)exportObjectAtIndexToiPhoto:(int)fp8;
- (void)exportObjectsToiPhoto:(id)fp8;
- (id)initWithAttachments:(id)fp8;
- (int)numberOfObjectsInSlideshow;
- (id)slideshowObjectAtIndex:(int)fp8;
- (void)start;

@end

