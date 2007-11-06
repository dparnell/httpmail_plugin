#import <Foundation/Foundation.h>
#import "DPhttp.h"
//#import "DPMD5.h"
#import "DPhttpmail.h"
#import "DPhttpmailMessage.h"
#include <stdio.h>

#define TEST_HTTPMAIL

#define TEST_MESSAGE @"Subject: Test Message %@\r\n\
Date: %@\r\n\
From: HTTPMail Tester <your.hotmail.username@hotmail.com>\r\n\
To: <nobody@nowhere.com>\r\n\
Mime-version: 1.0\r\n\
Content-type: text/plain; charset=\"US-ASCII\"\r\n\
Content-transfer-encoding: 7bit\r\n\
\r\n\
I really want this sending stuff to work!\r\n\
Wouldn't it be cool!\r\n\
"

int main(int argc, const char *argv[])
{
    char* bytes;
    int	L;

    NSEnumerator* keys;
    NSDictionary* headers;
    NSString* key;
    DPhttp* http;

    NSData* data;

    DPhttpmail* mail;
    
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    

    http = [DPhttp new];

/*
    NSLog(@"testing MD5: foo = %@", [DPMD5 computeFor: @"foo"]);
    NSLog(@"Testing httpmail transport code");
    NSLog(@"");
*/

    [http setProxy: NULL];
//    [http setUsername: @"daniel"];
//    [http setPassword: @"yellow1"];

/*
    [http setURL: [NSURL URLWithString: @"http://localhost/"]];

    data = [http get];

    bytes = (char*)[data bytes];
    L = [data length];

    headers = [http responseHeaders];
    keys = [headers keyEnumerator];
    while ((key = [keys nextObject])) {
        NSLog( @"HEADER - %@: %@", key, [headers objectForKey: key]);
    }
    fwrite(bytes, 1, L, stdout);
*/
    
/*
    NSLog(@"");
    [http setURL: [NSURL URLWithString: @"http://localhost/~daniel/secure/test.html"]];
    data = [http get];
    headers = [http responseHeaders];
    keys = [headers keyEnumerator];
    while ((key = [keys nextObject])) {
        NSLog( @"%@: %@", key, [headers objectForKey: key]);
    }
    bytes = (char*)[data bytes];
    L = [data length];
    fwrite(bytes, 1, L, stdout);
    NSLog(@"");
*/

/*
//    [http setProxy: [NSURL URLWithString: @"http://proxy.oz.quest.com:8080/"]];
    [http setURL: [NSURL URLWithString: @"http://www.yahoo.com/"]];
    data = [http get];
    NSLog( @"Response code=%d message='%@'", [http responseCode], [http responseString]);
    headers = [http responseHeaders];
    keys = [headers keyEnumerator];
    while ((key = [keys nextObject])) {
        NSLog( @"%@: %@", key, [headers objectForKey: key]);
    }
    bytes = (char*)[data bytes];
    L = [data length];
    fwrite(bytes, 1, L, stdout);
*/
    
#ifdef TEST_HTTPMAIL
    NSLog(@"Connecting to hotmail");
    mail = [DPhttpmail new];
    [mail setUsername: @"danielparnell"];
    [mail setPassword: @"yellow1"];

/*
    x[mail setProxy: [NSURL URLWithString: @"http://your.proxy.server:8080/"]]x;
    x[mail setProxyUsername: @"your proxy username here"]x;
    x[mail setProxyPassword: @"your proxy password here"]x;
*/

    if([mail login]) {
        NSLog(@"login successful");
        
        NSLog(@"Getting messages for inbox");
    
        NSArray* messages = [mail messagesForFolder: @"inbox"];
      
        DPhttpmailMessage* msg;        
        
/*
        msg = [messages objectAtIndex: 0];

        NSLog(@"Getting message: %@", [msg url]);
        data = [mail get: [msg url]];
        bytes = (char*)[data bytes];
        L = [data length];
        fwrite(bytes, 1, L, stdout);
*/
    
/*
        NSURL* inbox = [mail inboxFolder];
        msg = [messages objectAtIndex: [messages count]-1];
        NSLog(@"trashing message: %@", [msg url]);
        data = [mail remove: [NSArray arrayWithObject: msg] fromFolder: inbox];
        bytes = (char*)[data bytes];
        L = [data length];
        fwrite(bytes, 1, L, stdout);
        NSLog(@"Response code: %d", [mail responseCode]);
        NSLog(@"Response: %@", [mail responseString]);
*/

/*
        NSLog(@"Sending a test message");
        
        // Date: Thu, 13 Feb 2003 18:55:53 +1100
        NSString* date = [[NSDate date] descriptionWithCalendarFormat: @"%a, %d %b %Y, %H:%M:%S %z" timeZone: nil locale: nil];
        NSString* msg = [NSString stringWithFormat: TEST_MESSAGE, [NSDate date], date];
        NSLog(@"Sending message:\n%@", msg);
        
        data = x[mail sendMessage: msg to: @"nobody@nowhere.com"]x;
        bytes = (char*)[data bytes];
        L = [data length];
        fwrite(bytes, 1, L, stdout);
        NSLog(@"Response code: %d", [mail responseCode]);
        NSLog(@"Response: %@", [mail responseString]);    
*/        

    }
#endif    
    
    [pool release];
    
    NSLog(@"All done");
    return 0;
}
