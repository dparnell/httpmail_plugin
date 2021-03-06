/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import "NSFileManager.h"

@interface NSFileManager (NSFileManagerAdditions)
- (BOOL)canWriteToDirectoryAtPath:(id)fp8;
- (BOOL)canWriteToFileAtPath:(id)fp8;
- (void)deleteFilesInArray:(id)fp8 fromDirectory:(id)fp12;
- (void)deleteFilesInSortedArray:(id)fp8 matchingPrefix:(id)fp12 fromDirectory:(id)fp16;
- (id)fileModificationDateAtPath:(id)fp8 traverseLink:(BOOL)fp12;
- (long long)fileSizeAtPath:(id)fp8 traverseLink:(BOOL)fp12;
- (BOOL)makeCompletePath:(id)fp8 mode:(int)fp12;
- (id)makeUniqueDirectoryWithPath:(id)fp8;
- (id)pathsAtDirectory:(id)fp8 beginningWithString:(id)fp12;
- (id)rawDirectoryContentsAtPath:(id)fp8;
@end

