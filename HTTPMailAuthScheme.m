//
//  HTTPMailAuthScheme.m
//  httpmail
//
//  Created by Daniel Parnell on Tue Mar 02 2004.
//  Copyright (c) 2004 Daniel Parnell. All rights reserved.
//

#import "HTTPMailAuthScheme.h"
#import "HTTPMailAccount.h"
#import "HTTPMailConnection.h"

@implementation HTTPMailAuthScheme

- (char)supportsAccountType:(Account*)account {
    return [[account class] isSubclassOfClass: [HTTPMailAccount class]];
}

- (Class)connectionClassForAccount:fp8 {
    return [HTTPMailConnection class];
}

- (unsigned int)defaultPortForAccount:fp8 {
    return 80;
}

- (Class)authenticatorClassForAccount:fp8 {
    return [PlainAuthenticator class];
}

- (BOOL)requiresPassword {
    return YES;
}

- name {
    return @"HTTPMail";
}

- humanReadableName {
    return @"HTTP Mail";
}


@end
