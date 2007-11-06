//
//  HTTPMailDeliveryAccount.m
//  httpmail
//
//  Created by Daniel Parnell on Tue Feb 11 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import "HTTPMailDeliveryAccount.h"
#import "HTTPMailConnection.h"
#import "HTTPMailDelivery.h"
#import "Localization.h"

@implementation HTTPMailDeliveryAccount

- (void)doesNotRecognizeSelector:(SEL)aSelector {
    NSLog(@"HTTPMailDeliveryAccount doesNotRecognizeSelector: %s", aSelector);
}

+ newWithAccount: (HTTPMailAccount*)account {
    HTTPMailDeliveryAccount* result = [HTTPMailDeliveryAccount new];
    // result->httpmail = account;

    NSString* provider = [account providerURL];
    if(provider) {
        NSURL* url = [NSURL URLWithString: provider];
        
        [result setHostname: [url host]];
    }
    [result setUsername: [account username]];
    
    return result;
}

+ accountTypeString {
    return @"HTTPMailDelivery";
}

+ newDefaultInstance {
    return [HTTPMailDeliveryAccount new];
}

- (HTTPMailAccount*) findAccount {
    NSArray* accounts = [MailAccount mailAccounts];
    int i, C;
    
    C = [accounts count];
    for(i=0; i<C; i++) {
        MailAccount* account = [accounts objectAtIndex: i];
        
        if([[account class] isSubclassOfClass: [HTTPMailAccount class]]) {
            HTTPMailAccount* httpmail = (HTTPMailAccount*)account;
            
            if([[httpmail username] isEqualToString: [self username]]) {
                NSString* provider = [httpmail providerURL];
                
                if(provider) {
                    NSURL* url = [NSURL URLWithString: provider];
                    
                    if([[url host] isEqualToString: [self hostname]]) {
                        return httpmail;
                    }
                }
            }
        }
    }
    
    return nil;
}

- authenticatedConnectionForDomain:fp12 errorMessage:(id *)fp16 {    
    return [HTTPMailDeliveryConnection newWithAccount: [self findAccount]];
}

#ifndef TARGET_JAGUAR
- authenticatedConnection {
    return [HTTPMailDeliveryConnection newWithAccount: [self findAccount]];
}
#endif

#ifdef TARGET_TIGER
- (NSString*) identifier {
    return [NSString stringWithFormat: @"HTTPMail:%@", [self username]];
}
#endif

/*
- (NSString*) username {
    return [httpmail firstEmailAddress];
}

- (NSString*) hostname {
    NSString* provider = [httpmail providerURL];
    if(provider) {
        NSURL* url = [NSURL URLWithString: provider];
    
        return [url host];
    }
    
    return nil;
}
*/

@end

@implementation HTTPMailDeliveryConnection

+ newWithAccount: (HTTPMailAccount*)account {
    return [[HTTPMailDeliveryConnection alloc] initWithAccount: account];
}

- initWithAccount:(HTTPMailAccount*)account {
    self = [super init];
    
    if(self) {
        httpmail = account;
        mail = [[[DPhttpmail alloc] initWithMailAccount: account] retain];
        to = NULL;
    }
    
    return self;
}

- (void) dealloc {
    [mail release];
    [to release];
    
    [super dealloc];
}


- (BOOL)authenticateUsingAccount:fp12 errorMessage:(id *)fp16 {
    return YES;
}

- (BOOL)authenticateUsingAccount:fp12 authenticator:fp16 errorMessage:(id *)fp20 {
    return YES;
}

- (BOOL)connectUsingAccount:fp12 errorMessage:(id *)fp16 {    
    return YES;
}

- (int)mailFrom:(NSString*)address {
    @try {    

        if(![mail isConnected]) {
            if(![mail login]) {
                NS_VALUERETURN(4, int);
            }
        } 
            
        from = [address retain];
    } @catch (NSException* e) {
        if(![mail stopped]) {
            showAlert(httpmail, e, LocalizedString(@"Connection Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error ocurred while sending mail via '%@'\n%@", @""), [httpmail displayName], e]);
        }
        
        return 4;
    }   
    
    return 2;
}

- (int)rcptTo:(NSString*)address {   
    @try {    
        if(![mail isConnected]) {
            if(![mail login]) {
                NS_VALUERETURN(4, int);
            }
        } 
        
        if(to==NULL) {
            to = [[NSMutableArray array] retain];
        }
        
        [to addObject: address];
    
    } @catch(NSException* e) {
        if(![mail stopped]) {
            showAlert(httpmail, e, LocalizedString(@"Connection Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error ocurred while sending mail via '%@'\n%@", @""), [httpmail displayName], e]);
        }
        
        return 4;
    }

    return 2;
}

- (int)sendData:(NSData*)body {
    @try {    
        if(![mail isConnected]) {
            if(![mail login]) {
                NS_VALUERETURN(4, int);
            }
        } 
        
        [[ActivityMonitor currentMonitor] setStatusMessage: LocalizedString(@"Sending message data", @"")];
        
        NSString* bodyString = [NSString stringWithCString: [body bytes] length: [body length]];
        
        [mail sendMessage: bodyString to: to savingInSent: [httpmail shouldSaveSentMessages]];

        [from release];
        from = NULL;
        [to release];
        to = NULL;
        
        if([mail responseCode]>299) {
            NS_VALUERETURN(4, int);
        }
        
//        [NSException raise: @"test exception" format: @""];
        
    } @catch(NSException* e) {
        if(![mail stopped]) {
            showAlert(httpmail, e, LocalizedString(@"Connection Failure", @""), [NSString stringWithFormat: LocalizedString(@"An error ocurred while sending mail via '%@'\n%@", @""), [httpmail displayName], e]);
        }
        
        return 4;
    }
    
    return 2;
}

- (int)quit {
    [mail release];
    mail = NULL;
    
    return 2;
}

@end
