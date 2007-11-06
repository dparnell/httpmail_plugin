//
//  DPPOPHandler.m
//  httpmail
//
//  Created by Daniel Parnell on Thu Oct 10 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "DPPOPHandler.h"
#import "DPhttpmail.h"
#import "DPhttpmailMessage.h"

@implementation DPPOPHandler

- initWithSocket:(DPSocket*)socket {
    self = [super init];
    
    if(self) {
        fSocket = [socket autorelease];
    }
    
    return self;
}

- (void)run:(id)server {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    DPhttpmail* mail = [DPhttpmail new];
    NSArray*	messages = NULL;
    
/*
    [mail setProxy: [NSURL URLWithString: @"http://proxy.oz.quest.com:8080/"]];
    [mail setProxyUsername: @"OZQUEST\\Daniel.Parnell"];
    [mail setProxyPassword: @"yellow22"];
*/
    
    NSLog(@"New handler thread started");
    [fSocket writeString: @"+OK POP3 to HTTPMAIL gateway ready\r\n"];
    NSAutoreleasePool* linepool = NULL;
    while(1) {
        if(linepool) {
            [linepool release];
        }
        
        linepool = [[NSAutoreleasePool alloc] init];
        NSString* line = [fSocket readLine];
        NSLog(@"got line: '%@'", line);
        
        NSScanner* scanner = [NSScanner scannerWithString: line];
        NSString* word;
        
        if([scanner scanUpToCharactersFromSet: [NSCharacterSet whitespaceCharacterSet] intoString: &word]) {
            NSLog(@"command '%@'", word);
            
            if([word caseInsensitiveCompare: @"QUIT"]==0) {
                [fSocket writeString: @"+OK goodbye\r\n"];
                break;
            }
            
            if([word caseInsensitiveCompare: @"NOOP"]==0) {
                [fSocket writeString: @"+OK\r\n"];
                continue;
            }
            
            if([word caseInsensitiveCompare: @"USER"]==0) {
                if([scanner scanUpToCharactersFromSet: [NSCharacterSet whitespaceCharacterSet] intoString: &word]) {
                    [mail setUsername: word];
                    [fSocket writeString: @"+OK\r\n"];
                    continue;
                }
            }
            
            if([word caseInsensitiveCompare: @"PASS"]==0) {
                NSLog(@"Connecting to hotmail");
                if([scanner scanUpToCharactersFromSet: [NSCharacterSet whitespaceCharacterSet] intoString: &word]) {
                    [mail setPassword: word];
                    
                    [mail login];
                    [fSocket writeString: @"+OK\r\n"];
                    continue;
                }
            }
            
            if([word caseInsensitiveCompare: @"STAT"]==0) {
                NSLog(@"Downloading messages");
                messages = [[mail messagesForFolder: @"inbox"] retain];
                
                int i, L, T;
                L = [messages count];
                T = 0;
                for(i=0; i<L; i++) {
                    DPhttpmailMessage* m = [messages objectAtIndex: i];
                    T = T + [m size];
                }
                
                [fSocket writeString: [NSString stringWithFormat: @"+OK %d %d\r\n", L, T]];
                continue;
            }
            
            if([word caseInsensitiveCompare: @"LIST"]==0) {
                int index;
                
                if([scanner scanInt: &index]) {
                    index = index - 1;
                    if(index<[messages count]) {
                        [fSocket writeString: @"+OK\r\n"];
                        DPhttpmailMessage* m = [messages objectAtIndex: index];
                        [fSocket writeString: [NSString stringWithFormat: @"%d %d\r\n", index, [m size]]];
                    } else {
                        [fSocket writeString: @"-ERR\r\n"];
                    }
                } else {
                    int i, L;
                    
                    L = [messages count];
                    [fSocket writeString: [NSString stringWithFormat: @"+OK %d messages\r\n", L]];
                    for(i=0; i<L; i++) {
                        DPhttpmailMessage* m = [messages objectAtIndex: i];
                        [fSocket writeString: [NSString stringWithFormat: @"%d %d\r\n", i+1, [m size]]];
                    }
                    
                    [fSocket writeString: @".\r\n"];
                }
                
                continue;
            }

            if([word caseInsensitiveCompare: @"UIDL"]==0) {
                int index;
                
                if([scanner scanInt: &index]) {
                    index = index - 1;
                    if(index<[messages count]) {
                        [fSocket writeString: @"+OK\r\n"];
                        DPhttpmailMessage* m = [messages objectAtIndex: index];
                        [fSocket writeString: [NSString stringWithFormat: @"%d %@\r\n", index+1, [m uniqueID]]];
                    } else {
                        [fSocket writeString: [NSString stringWithFormat: @"-ERR no such message, only %d messages in maildrop\r\n", [messages count]]];
                    }
                } else {
                    int i, L;
                    
                    L = [messages count];
                    [fSocket writeString: [NSString stringWithFormat: @"+OK %d messages\r\n", L]];
                    for(i=0; i<L; i++) {
                        DPhttpmailMessage* m = [messages objectAtIndex: i];
                        [fSocket writeString: [NSString stringWithFormat: @"%d %@\r\n", i+1, [m uniqueID]]];
                    }
                    
                    [fSocket writeString: @".\r\n"];
                }
                
                continue;
            }
            
            if([word caseInsensitiveCompare: @"RETR"]==0) {
                int index;
                
                if([scanner scanInt: &index]) {
                    index = index - 1;
                    if(index<[messages count]) {
                        DPhttpmailMessage* m = [messages objectAtIndex: index];
                        NSData* data = [mail get: [m url]];
                        [fSocket writeString: @"+OK %d octets\r\n"];
                        [fSocket writeData: data];
                        [fSocket writeString: @"\r\n.\r\n"];
                    } else {
                        [fSocket writeString: @"-ERR\r\n"];
                    }
                } else {
                    [fSocket writeString: @"-ERR\r\n"];
                }
                
                continue;
            }

            
            [fSocket writeString: [NSString stringWithFormat: @"-ERR unknown command '%@'\r\n", word]];
        }
    }
    [linepool release];
            
    [pool release];
}

@end
