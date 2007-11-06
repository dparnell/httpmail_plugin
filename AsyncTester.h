/* AsyncTester */

#import <Cocoa/Cocoa.h>
#import "DPAsyncHttpMail.h"
#import "DPhttpmail.h"

@interface AsyncTester : NSObject
{
    DPAsyncHttpMail* 	fMail;
    DPhttpmail*         fMail2;
    
    BOOL		finished;
    int			mode;
}
- (IBAction)performTests:(id)sender;
- (IBAction)performTests2:(id)sender;
- (IBAction)testMail:(id)sender;
@end
