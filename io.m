//
//  io.m
//  httpmail
//
//  Created by Daniel Parnell on Sun Dec 08 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "io.h"

@implementation IO

+ (IO*)stdio {
    return [self newWithHandle: 0];
}

+ (IO*)newWithHandle: (FILE*)aHandle {
    return [[self alloc] initWithHandle: aHandle];
}

+ (IO*)newWithFileName: (NSString*)aFileName {
    return [self newWithHandle: fopen([aFileName cString], "r")];
}

- (IO*)initWithHandle: (FILE*)aHandle {
    self = [super init];
    
    if(self) {
        fHandle = aHandle;
    }
    
    return self;
}

- (void)write:(NSString*)string {
    const char* cstr = [string cString];
    
    if(fHandle) {
        fprintf(fHandle, "%s", cstr);
    } else {
        fprintf(stdout, "%s", cstr);
    }
}

- (NSString*)readln {
    char* buf;
    size_t len;
    
    if(fHandle) {
        buf = fgetln(fHandle, &len); 
    } else {
        buf = fgetln(stdin, &len);
    }
    
    if(buf) {
        return [NSString stringWithCString: buf length: len];
    } else {
        return NULL;
    }
}

- (void)close {
    if(fHandle) {
        fclose(fHandle);
    }
}

- (void)flush {
    if(fHandle) {
        fflush(fHandle);
    } else {
        fflush(stdout);
    }
}

- (void)writeData:(NSData*)data {
    int len = [data length];
    const char* buf = [data bytes];
    
    if(fHandle) {
        fwrite(buf, 1, len, fHandle);
    } else {
        fwrite(buf, 1, len, stdout);
    }

}

@end
