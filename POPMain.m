#import <Foundation/Foundation.h>
#import "DPPOPServer.h"

int main(int argc, const char *argv[])
{
    [[NSAutoreleasePool alloc] init];
    
    DPPOPServer* pop = [DPPOPServer new];
    [pop run];
    
    return 0;
}
