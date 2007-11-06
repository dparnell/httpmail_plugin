//
//  POPHandler.m
//  httpmail
//
//  Created by Daniel Parnell on Sun Dec 08 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "POPHandler.h"
#import "DPhttpmail.h"
#import "DPhttpmailMessage.h"
#import <syslog.h>
#import "DPKeychain.h"
#import <SystemConfiguration/SystemConfiguration.h>

//#define DEBUG

@implementation POPHandler

#ifdef DEBUG
void sysLog(NSString* string) {
    syslog(LOG_INFO, "%s\n", [string cString]);
}
#endif

- (POPHandler*)initWithIO: (IO*) aIO {
    self = [super init];
    
    if(self) {
        io = aIO;
    }
    
    return self;
}

- (void)run {
    DPhttpmail* mail = [DPhttpmail new];
    NSArray*	messages = NULL;
    NSMutableArray*	deleted = [NSMutableArray array];
    
/*
    NSDictionary* settings = (NSDictionary*)SCDynamicStoreCopyProxies(NULL);
    NSString* proxy = [settings objectForKey: @"HTTPProxy"];

    if(proxy) {
        NSNumber* port = [settings objectForKey: @"HTTPPort"];
        
        DPKeychain* keychain = [DPKeychain newWithPath: @"/Library/Keychains/proxy"];
        NSDictionary* auth = [keychain findKeychainItem: proxy];
        
        [mail setProxy: [NSURL URLWithString: [NSString stringWithFormat: @"http://%@:%@/", proxy, port]]];
        [mail setProxyUsername: [auth objectForKey: kcUsername]];
        [mail setProxyPassword: [auth objectForKey: kcPassword]];
    }    
*/
        [mail setProxy: [NSURL URLWithString: @"http://proxy.oz.quest.com:8080/"]];
        [mail setProxyUsername: @"OZQUEST\\Daniel.Parnell"];
        [mail setProxyPassword: @"yellow22"];

#ifdef DEBUG
    sysLog(@"got a connection");
#endif    

    [io write: @"+OK POP3 to HTTPMAIL gateway v0.01 by Daniel Parnell ready\r\n"];
    [io flush];
    NSAutoreleasePool* linepool = NULL;
    while(1) {
        if(linepool) {
            [linepool release];
            linepool = NULL;
        }
        
        // dunno why this doesn't work :(
//        linepool = [[NSAutoreleasePool alloc] init];

        NSString* line = [io readln];
        
        // die if the socket has been closed
        if(line==NULL) break;
        
#ifdef DEBUG
        sysLog([NSString stringWithFormat: @"got line '%@'", line]);
#endif
        
        NSScanner* scanner = [NSScanner scannerWithString: line];
        NSString* word;
        
        if([scanner scanUpToCharactersFromSet: [NSCharacterSet whitespaceAndNewlineCharacterSet] intoString: &word]) {            
            if([word caseInsensitiveCompare: @"QUIT"]==0) {
                if([mail isConnected] && ([deleted count]>0)) {
                    [mail remove: deleted fromFolder: [mail inboxFolder]];
                }
                
                [io write: @"+OK goodbye\r\n"];
                [io flush];
                break;
            }
            
            if([word caseInsensitiveCompare: @"NOOP"]==0) {
                [io write: @"+OK\r\n"];
                [io flush];
                continue;
            }
            
            if([word caseInsensitiveCompare: @"USER"]==0) {
                if([scanner scanUpToCharactersFromSet: [NSCharacterSet whitespaceAndNewlineCharacterSet] intoString: &word]) {
                    [mail setUsername: word];
                    [io write: @"+OK\r\n"];
                    [io flush];
                    continue;
                }
            }
            
            if([word caseInsensitiveCompare: @"PASS"]==0) {
                if([scanner scanUpToCharactersFromSet: [NSCharacterSet whitespaceAndNewlineCharacterSet] intoString: &word]) {
#ifdef DEBUG
                    sysLog(@"loggin in to hotmail");
#endif                    
                    [mail setPassword: word];
                 
                    NS_DURING   
                        if([mail login]) {
                            [io write: @"+OK\r\n"];
                        } else {
                            [io write: [NSString stringWithFormat: @"-ERR %@\r\n", [mail responseString]]];
                        }
                        [io flush];
                    
                    NS_HANDLER
                        [io write: [NSString stringWithFormat: @"-ERR %@\r\n", [localException reason]]];
                    NS_ENDHANDLER
                    
                    continue;
                }
            }
            
            if([word caseInsensitiveCompare: @"STAT"]==0) {
                if(![mail isConnected]) {
                    [io write: @"-ERR not connected\r\n"];
                    [io flush];
                    continue;
                }
                
                messages = [[mail messagesForFolder: @"inbox"] retain];
                
                int i, L, T;
                L = [messages count];
                T = 0;
                for(i=0; i<L; i++) {
                    DPhttpmailMessage* m = [messages objectAtIndex: i];
                    T = T + [m size];
                }
                
                [io write: [NSString stringWithFormat: @"+OK %d %d\r\n", L, T]];
                [io flush];
                continue;
            }
            
            if([word caseInsensitiveCompare: @"LIST"]==0) {
                int index;
                
                if(![mail isConnected]) {
                    [io write: @"-ERR not connected\r\n"];
                    [io flush];
                    continue;
                }
                
                if([scanner scanInt: &index]) {
                    index = index - 1;
                    if(index<[messages count]) {
                        [io write: @"+OK\r\n"];
                        DPhttpmailMessage* m = [messages objectAtIndex: index];
                        [io write: [NSString stringWithFormat: @"%d %d\r\n", index, [m size]]];
                    } else {
                        [io write: @"-ERR\r\n"];
                    }
                } else {
                    int i, L;
                    
                    L = [messages count];
                    [io write: [NSString stringWithFormat: @"+OK %d messages\r\n", L]];
                    for(i=0; i<L; i++) {
                        DPhttpmailMessage* m = [messages objectAtIndex: i];
                        [io write: [NSString stringWithFormat: @"%d %d\r\n", i+1, [m size]]];
                    }
                    
                    [io write: @".\r\n"];
                }
                
                [io flush];
                continue;
            }

            if([word caseInsensitiveCompare: @"UIDL"]==0) {
                int index;

                if(![mail isConnected]) {
                    [io write: @"-ERR not connected\r\n"];
                    [io flush];
                    continue;
                }
                
                if([scanner scanInt: &index]) {
                    index = index - 1;
                    if(index<[messages count]) {
                        [io write: @"+OK\r\n"];
                        DPhttpmailMessage* m = [messages objectAtIndex: index];
                        [io write: [NSString stringWithFormat: @"%d %@\r\n", index+1, [m uniqueID]]];
                    } else {
                        [io write: [NSString stringWithFormat: @"-ERR no such message, only %d messages in maildrop\r\n", [messages count]]];
                    }
                } else {
                    int i, L;
                    
                    L = [messages count];
                    [io write: [NSString stringWithFormat: @"+OK %d messages\r\n", L]];
                    for(i=0; i<L; i++) {
                        DPhttpmailMessage* m = [messages objectAtIndex: i];
                        [io write: [NSString stringWithFormat: @"%d %@\r\n", i+1, [m uniqueID]]];
                    }
                    
                    [io write: @".\r\n"];
                }
                
                [io flush];
                continue;
            }
            
            if([word caseInsensitiveCompare: @"RETR"]==0) {
                int index;

                if(![mail isConnected]) {
                    [io write: @"-ERR not connected\r\n"];
                    [io flush];
                    continue;
                }
                
                if([scanner scanInt: &index]) {
                    index = index - 1;
                    if(index<[messages count]) {
                        DPhttpmailMessage* m = [messages objectAtIndex: index];
                        NSData* data = [mail get: [m url]];
                        [io write: @"+OK %d octets\r\n"];
                        [io writeData: data];
                        [io write: @"\r\n.\r\n"];
                    } else {
                        [io write: @"-ERR\r\n"];
                    }
                } else {
                    [io write: @"-ERR\r\n"];
                }
                
                [io flush];
                continue;
            }

            if([word caseInsensitiveCompare: @"RSET"]==0) {
                [deleted removeAllObjects];

                if(![mail isConnected]) {
                    [io write: @"-ERR not connected\r\n"];
                    [io flush];
                    continue;
                }
                
                [io write: @"+OK\r\n"];
                [io flush];
                
                continue;
            }
            
            if([word caseInsensitiveCompare: @"DELE"]==0) {
                int index;

                if(![mail isConnected]) {
                    [io write: @"-ERR not connected\r\n"];
                    [io flush];
                    continue;
                }
                
                if([scanner scanInt: &index]) {
                    index = index - 1;
                    if(index<[messages count]) {
                        DPhttpmailMessage* m = [messages objectAtIndex: index];
                        [deleted addObject: m];
                        
                        [io write: @"+OK\r\n"];
                    } else {
                        [io write: @"-ERR\r\n"];
                    }
                } else {
                    [io write: @"-ERR\r\n"];
                }
                
                [io flush];
                continue;
            }            
            
            [io write: [NSString stringWithFormat: @"-ERR unknown command '%@'\r\n", word]];
            [io flush];
        }
    }
    [io flush];
    [linepool release];
}

@end
