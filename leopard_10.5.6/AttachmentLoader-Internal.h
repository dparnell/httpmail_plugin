/*
 *     Generated by class-dump 3.1.2.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2007 by Steve Nygard.
 */

#import "AttachmentLoader.h"

@interface AttachmentLoader (Internal)
+ (id)_loaderForStore:(id)fp8;
+ (id)_makeLoaderForStore:(id)fp8;
- (id)init;
- (void)_cancelInlineLoadsForWindow:(id)fp8;
- (void)_didFetchFileWrapper:(id)fp8 forQueueEntry:(id)fp12;
- (void)_processAttachmentQueue;
- (void)_setMonitor:(id)fp8;
- (void)_monitorQuit;
- (void)_mailboxBecameInvalid;
- (void)_setStore:(id)fp8;
- (void)_startBackgroundThreadIfNeeded;
- (void)_addAttachmentsToFetch:(id)fp8 fromWindow:(id)fp12 delegate:(id)fp16;
- (BOOL)_addOrReprioritizeEntryEqualTo:(id)fp8;
@end

