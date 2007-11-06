#import <Foundation/Foundation.h>


int main(int argc, const char *argv[])
{
    NSAutoreleasePool* pool = [NSAutoreleasePool new];
    
    NSString* urlString = @"http://bay15.oe.hotmail.com/cgi-bin/hmdata/danielparnell@hotmail.com/folders/f%f4%f3/MSG1085345148.94";
    NSURL* url = [NSURL URLWithString: urlString];
    
    NSLog(@"%@", url);
    NSLog(@"%@", [url absoluteString]);
    NSLog(@"%@", [[url absoluteString] lastPathComponent]);
    NSLog(@"%@", [url path]);
    NSLog(@"%@", [[url path] lastPathComponent]);

    [pool release];
    
    return 0;
}
