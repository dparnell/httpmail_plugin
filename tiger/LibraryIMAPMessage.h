/*
 *     Generated by class-dump 3.0.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004 by Steve Nygard.
 */

#import <Message/LibraryMessage.h>

@class MessageHeaders;

@interface LibraryIMAPMessage : LibraryMessage
{
    MessageHeaders *_headers;
}

+ (id)messageWithLibraryID:(unsigned int)fp8;
- (void)dealloc;
- (id)headers;
- (void)setHeaders:(id)fp8;

@end

