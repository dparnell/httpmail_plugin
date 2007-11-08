//
//  HTTPMailDeliveryAccount.h
//  httpmail
//
//  Created by Daniel Parnell on Tue Feb 11 2003.
//  Copyright (c) 2003 Daniel Parnell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HTTPMailAccount.h"
#import "mail-api.h"
#import "DPhttpmail.h"

#ifdef TARGET_LEOPARD
#import "SMTPDelivery.h"
#endif

@interface HTTPMailDeliveryAccount : SMTPAccount {
//    HTTPMailAccount* httpmail;
}

+ newWithAccount: (HTTPMailAccount*)account;

@end

@interface HTTPMailDeliveryConnection : SMTPConnection {
    HTTPMailAccount* httpmail;
    DPhttpmail* mail;
    NSString* from;
    NSMutableArray* to;
}

+ newWithAccount: (HTTPMailAccount*)account;

@end

#ifdef TARGET_LEOPARD
@interface HTTPMailDelivery : SMTPDelivery {
}

@end
#endif
