#import <Foundation/Foundation.h>
#import "DPAsyncHttp.h"

int main(int argc, const char *argv[])
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

//    DPAsyncHttp* http = [DPAsyncHttp newWithURL: [NSURL URLWithString: @"http://localhost/~daniel/redirect/redir.php"]];
//    DPAsyncHttp* http = [DPAsyncHttp newWithURL: [NSURL URLWithString: @"http://localhost/~daniel/redirect/test.html"]];
//    DPAsyncHttp* http = [DPAsyncHttp newWithURL: [NSURL URLWithString: @"http://localhost/~daniel/redirect/"]];
    DPAsyncHttp* http = [DPAsyncHttp newWithURL: [NSURL URLWithString: @"http://www.yahoo.com/"]];
    
    [http setProxy: [NSURL URLWithString: @"http://proxy.oz.quest.com:8080/"]];
    [http setProxyUsername: @"OZQUEST\\Daniel.Parnell"];
    [http setProxyPassword: @"yellow22"];
    
    [http get];
    
    [[NSRunLoop currentRunLoop] run];
    
    NSData* data = [http responseData];
    NSLog(@"data = \n%@", [NSString stringWithCString: [data bytes] length: [data length]]);
    
    [pool release];
    
}
