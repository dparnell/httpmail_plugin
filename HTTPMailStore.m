//
//  HTTPMailStore.m
//  httpmail
//
//  Created by Daniel Parnell on Thu Oct 03 2002.
//  Copyright (c) 2002 DanielParnell. All rights reserved.
//

#import "HTTPMailStore.h"
#import "HTTPMailMessage.h"
#import "HTTPMailConnection.h"

@implementation HTTPMailStore

NSMutableDictionary* stores = NULL;


+ (BOOL) createEmptyStoreForPath:(NSString*)path {
    NSLog(@"createEmptyStoreForPath: %@", path);
    
    NSFileManager* fm = [NSFileManager defaultManager];
    return [fm createDirectoryAtPath: path attributes: nil];
}


+ (BOOL) storeAtPathIsWritable:(NSString*)path {
    return YES;
}

- initWithMailboxUid:fp12 readOnly:(char)fp16 {
    NSLog(@"*** HTTPMailStore initWithMailboxUid ***");
    self = [super initWithMailboxUid:fp12 readOnly: fp16];
    return self;
}

// stolen from GPGmail
- (NSRange) findBodyForData:(NSData*) data;
{
#define CR	'\r'
#define LF	'\n'
    const unsigned char	*bytes = [data bytes];
    const int			length = [data length];
    int					i;
    NSRange				result = NSMakeRange(NSNotFound, 0);
    
    // First let's find start of body (skip headers)
    for(i = 0; i < length; i++){
        if(bytes[i] == CR){
            if(i + 1 < length){
                if(bytes[i + 1] == CR){
                    result.location = i + 1;
//                    result.length = [data length] - result.location;
                    break;
                }
                if(bytes[i + 1] == LF)
                    if(i + 3 < length)
                        if(bytes[i + 2] == CR && bytes[i + 3] == LF){
                            result.location = i + 2;
//                            result.length = [data length] - result.location;
                            break;
                        }
            }
            if(i == 0){
                result.location = 0;
//                result.length = [data length] - result.location;
                break;
            }
        }
        else if(bytes[i] == LF){
            if(i + 1 < length)
                if(bytes[i + 1] == LF){
                    result.location = i + 1;
//                    result.length = [data length] - result.location;
                    break;
                }
            if(i == 0){
                result.location = 0;
//                result.length = [data length] - result.location;
                break;
            }
        }
    }
  
    if(result.location!=NSNotFound) {  
        result.length = [data length] - result.location;
    }
    
    return result;
#undef LF
#undef CR
}

- (void)openSynchronouslyUpdatingIndex:(BOOL)updateIndex andOtherMetadata:(BOOL)updateMetadata {
//    NSLog(@"openSynchronouslyUpdatingIndex %@", self);

    [super openSynchronouslyUpdatingIndex: updateIndex andOtherMetadata: updateMetadata];
}

- (void)fetchSynchronously {
//    NSLog(@"HTTPMailStore fetchSynchronously");

    NSMutableArray* toAdd = [NSMutableArray array];
    NSMutableArray* failed = [NSMutableArray array];
    
    NSData* data = [NSData dataWithContentsOfFile: @"/Users/daniel/message.dat"];
    Message* msg = [[HTTPMailMessage alloc] initWithData: data];
    [msg setMessageStore: self];
    
    [msg autorelease];
    [toAdd addObject: msg];

//    NSLog(@"about to append the message");
    [self appendMessages: toAdd unsuccessfulOnes: failed];
//    NSLog(@"Created message %@", msg);
//    NSLog(@"failed = %@", failed);
    
//    NSLog(@"_allMessages = %@", _allMessages);
//    NSLog(@"finished opening message store");

}

- (NSData*) _fetchHeaderDataForMessage:(Message*)message { 
//    NSLog(@"_fetchHeaderDataForMessage %@", message);
    
    if([message isKindOfClass: [HTTPMailMessage class]]) {
        NSData* messageSource = [NSMutableData dataWithData: [(HTTPMailMessage*)message messageData]];
        [(NSMutableData *)messageSource convertNetworkLineEndingsToUnix];
        NSRange bodyRange = [self findBodyForData: messageSource];
        return [messageSource subdataWithRange:NSMakeRange(0, bodyRange.location)];
    } else {
        return [super _fetchHeaderDataForMessage: message];
    }
}

- (NSData*) _fetchBodyDataForMessage: (HTTPMailMessage*)message andHeaderDataIfReadilyAvailable:(id *)headers {
//    NSLog(@"_fetchBodyDataForMessage %@", message);

    if([message isKindOfClass: [HTTPMailMessage class]]) {
        NSData* messageSource = [NSMutableData dataWithData: [(HTTPMailMessage*)message messageData]];
        [(NSMutableData *)messageSource convertNetworkLineEndingsToUnix];
        NSRange bodyRange = [self findBodyForData: messageSource];
        
//        NSLog(@"Returning body data %d->%d", bodyRange.location, bodyRange.length);
        return [messageSource subdataWithRange: bodyRange];
    } else {
        return [super _fetchBodyDataForMessage: message andHeaderDataIfReadilyAvailable: headers];
    }
}

- connection {
    id result = [super connection];
    NSLog(@"returning a connection %@", result);
    
    return result;
}

@end
