//
//  DPMD5.m
//  httpmail
//
//  Created by Daniel Parnell on Wed Sep 25 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "DPMD5.h"
#include <openssl/evp.h>

@implementation DPMD5

+ (NSString*)computeFor:(NSString*)value {
    EVP_MD_CTX mdctx;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;
    NSMutableString* result = [NSMutableString string];
    const char* buf;
	
	buf = [value cStringUsingEncoding: NSUTF8StringEncoding];
    EVP_DigestInit(&mdctx, EVP_md5());
    EVP_DigestUpdate(&mdctx, buf, strlen(buf));
    EVP_DigestFinal(&mdctx, md_value, &md_len);
    
    for(i=0; i<md_len; i++) {
        [result appendString: [NSString stringWithFormat: @"%02x", md_value[i]]];
    }
    
    return result;
}

@end
