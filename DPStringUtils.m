//
//  DPStringUtils.m
//  httpmail
//
//  Created by Daniel Parnell on Thu Sep 26 2002.
//  Copyright (c) 2002 Daniel Parnell. All rights reserved.
//

#import "DPStringUtils.h"


@implementation DPStringUtils

+ (void) nextWordInString:(const char*)string fromIndex:(int)index intoRange:(NSRange*)range withSep:(char)sep{
    NSRange r;
    int i = index;
    char ch;
            
    r.location = NSNotFound;
    
    // skip past any leading whitespace
    while(ch = *(string+i)) {
        if((ch!='=') && (ch>' ')) break;
        i++;
    }

    if(ch>' ') {
        r.location = i;
        if(ch=='"') {
            i++;
            // it is a quoted string          
            while(ch = *(string+i)) {
                if(ch=='"') break;
                i++;
            }
            if(ch=='"') i++;
        } else {
            // keep going until we hit some white space            
            while(ch = *(string+i)) {
                if((ch<=' ') || (ch==sep) || (ch=='=')) break;
                i++;
            }
        }
        
        r.length = i - r.location;
    } else {
        r.location = NSNotFound;
        r.length = 0;
    }
    
    *range = r;
}

+ (NSDictionary*)dictionaryFromString:(NSString*)string separatedBy:(char)sepchar {
    NSMutableDictionary* result = [NSMutableDictionary dictionary];
    NSRange r;
    const char* buf = [string cStringUsingEncoding: NSUTF8StringEncoding];
    NSString* name;
    NSString* value;
    unsigned int i, L;
    NSString* sep = [NSString stringWithCString: &sepchar length: 1];

    L = [string length];
    
    [self nextWordInString: buf fromIndex: 0 intoRange: &r withSep: sepchar];
    while((r.location!=NSNotFound) && (r.location+r.length<=L)) {
        name = [string substringWithRange: r];
        i = r.location + r.length + 1;
        if([name isEqualToString: sep]) {
            [self nextWordInString: buf fromIndex: i intoRange: &r withSep: sepchar];
            continue;
        }
        
        [self nextWordInString: buf fromIndex: i intoRange: &r withSep: sepchar];
        if(r.location==NSNotFound) break;
        value = [string substringWithRange: r];
        if([value hasPrefix: @"\""] && [value hasSuffix: @"\""]) {
            NSRange r2;
            
            r2.location = 1;
            r2.length = [value length]-2;
            
            value = [value substringWithRange: r2];
        }
        
        if(name && value)
            [result setObject: value forKey: name];
                
        i = r.location + r.length + 1;
        [self nextWordInString: buf fromIndex: i intoRange: &r withSep: sepchar];
    }
    return result;
}

//---------------------------------------------------------------------------------------
//	BASE64 (RFC 2045)
//---------------------------------------------------------------------------------------

#define LF ((char)'\x0A')
#define CR ((char)'\x0D')
#define TAB ((char)'\x09')
#define SPACE ((char)'\x20')
#define EQUALS ((char)'\x3D')

static char basis64[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static char index64[128] = {
    99,99,99,99, 99,99,99,99, 99,99,99,99, 99,99,99,99,
    99,99,99,99, 99,99,99,99, 99,99,99,99, 99,99,99,99,
    99,99,99,99, 99,99,99,99, 99,99,99,62, 99,99,99,63,
    52,53,54,55, 56,57,58,59, 60,61,99,99, 99,99,99,99,
    99, 0, 1, 2,  3, 4, 5, 6,  7, 8, 9,10, 11,12,13,14,
    15,16,17,18, 19,20,21,22, 23,24,25,99, 99,99,99,99,
    99,26,27,28, 29,30,31,32, 33,34,35,36, 37,38,39,40,
    41,42,43,44, 45,46,47,48, 49,50,51,99, 99,99,99,99
};


static __inline__ unsigned char char64(unsigned char c)
{
    return (c > 127) ? 99 : index64[(int)c];
}

static __inline__ unsigned int udivroundup(unsigned int a, unsigned int b)
{
    return (a / b) + ((a % b > 0) ? 1 : 0);
}

static __inline__ unsigned char invchar64(unsigned char b)
{
    return basis64[(int)b];
}


+ (NSString*)base64Encode:(NSString*)string {
    return [DPStringUtils base64Encode: string withLineLength: 0];
}

+ (NSString*)base64Encode:(NSString*)string withLineLength:(unsigned int)lineLength {
    NSMutableData 	*encodedData;
    const char		*source, *endOfSource;
    char			*dest, groupv[4], b;
    int				i, bytec = 0, groupc = 0;
    unsigned int	numgroups, groupsPerLine, dataLength;
	int				L;
	
    source = [string cStringUsingEncoding: NSUTF8StringEncoding];
	L = strlen(source);
    endOfSource = source + L;

    if(lineLength == 0)
        lineLength = UINT_MAX;
    numgroups = udivroundup(L, 3);
    groupsPerLine = lineLength / 4;
    if(groupsPerLine == 0)
        [NSException raise:NSInvalidArgumentException format:@"Line length must be > 3"];
    dataLength = numgroups * 4;
    if(lineLength > 0)
        dataLength += udivroundup(numgroups, groupsPerLine) * 2;

    encodedData = [NSMutableData dataWithLength:dataLength];
    dest = [encodedData mutableBytes];

    while(source < endOfSource)
        {
        b = *source++;
        switch(bytec++)
            {
            case 0:
                groupv[0]  = (b & 0xFC) >> 2;
                groupv[1]  = (b & 0x03) << 4;
                break;
            case 1:
                groupv[1] |= (b & 0xF0) >> 4;
                groupv[2]  = (b & 0x0F) << 2;
                break;
            case 2:
                groupv[2] |= (b & 0xC0) >> 6;
                groupv[3]  = (b & 0x3F);
                break;
            }
        if((bytec == 3) || (source == endOfSource))
            {
            for(i = 0; i < bytec + 1; i++)
                *dest++ = invchar64(groupv[i]);
            for(; i < 4; i++)
                *dest++ = EQUALS;
            bytec = 0;
            groupc += 1;
            if((groupc % groupsPerLine) == 0)
                {
                *dest++ = CR;
                *dest++ = LF;
                }
            }
        }

    [encodedData setLength:(unsigned int)((void *)dest - [encodedData mutableBytes])];

    return [NSString stringWithCString: [encodedData bytes] length: [encodedData length]];
}

+ (unsigned int)hexValue:(NSString*)string {
    NSScanner* scanner = [NSScanner scannerWithString: string];
    unsigned int result;
    
    [scanner scanHexInt: &result];
    
    return result;
}

@end
