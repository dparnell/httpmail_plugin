/* InstallerController */

#import <Cocoa/Cocoa.h>

@interface InstallerController : NSObject
{
    IBOutlet NSTextField *bundlesField;
    IBOutlet id doneButton;
    IBOutlet NSTextField *enablingField;
    IBOutlet NSTextField *installingField;
    IBOutlet NSProgressIndicator *progress;
    IBOutlet NSPanel *panel;
}
- (IBAction)startInstall:(id)sender;
@end
