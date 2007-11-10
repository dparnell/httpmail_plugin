#import "InstallerController.h"

@implementation InstallerController

#define BUNDLE_NAME @"httpmail.mailbundle"

static UInt32 getOSVersion() {
	SInt32 result;
	Gestalt(gestaltSystemVersion, &result);
	
	return result;
}

static NSDictionary* bundleProps = nil;

- (void) awakeFromNib {
    [bundlesField setTextColor: [NSColor disabledControlTextColor]];
    [installingField setTextColor: [NSColor disabledControlTextColor]];
    [enablingField setTextColor: [NSColor disabledControlTextColor]];
	
    NSString* bundlePath = [[[[NSBundle mainBundle] bundlePath] stringByDeletingLastPathComponent] stringByAppendingPathComponent: BUNDLE_NAME];
	NSString* infoPath = [[bundlePath stringByAppendingPathComponent: @"Contents"] stringByAppendingPathComponent: @"Info.plist"];
	NSString* error = nil;
	
    NSData* data = [NSData dataWithContentsOfFile: infoPath]; 
    if(data) {
        bundleProps = [[NSPropertyListSerialization propertyListFromData: data mutabilityOption: NSPropertyListMutableContainersAndLeaves format: nil errorDescription: nil] retain];		
		
		NSString* ver = [bundleProps objectForKey: @"OSVersion"];
		NSString* osVer = [NSString stringWithFormat: @"%x", getOSVersion()>>4];
		NSLog(@"osVer = %@, ver=%@", osVer, ver);
		
		if(![ver isEqualToString: osVer]) {
			error = [NSString stringWithFormat: NSLocalizedString(@"This version of the plugin will only work with Mac OS X %@.%@", @""),
						[ver substringToIndex: 2], [ver substringFromIndex: 2]];
		}
	} else {
		error = NSLocalizedString(@"Could not find mailbundle.  Please run the Installer from the disk image it came in", @"");
	}
	
	if(error) {
		NSRunCriticalAlertPanel(NSLocalizedString(@"Error", @""), error, NSLocalizedString(@"Quit", @""), nil, nil);
		[NSApp terminate: self];
	}
	
}

- (void) tick:(id)userInfo {
    NSFileManager* fm = [NSFileManager defaultManager];
    NSString* bundlesPath = [@"~/Library/Mail/Bundles/" stringByExpandingTildeInPath];
    BOOL dir;
    
    NSString* mailPrefsPath = [@"~/Library/Preferences/com.apple.mail.plist" stringByExpandingTildeInPath];
    NSData* data;
    NSMutableDictionary* prefs;
    NSPropertyListFormat format;
    
    NSString* srcPath;
    
    NSString* failed = NULL;
        
    NSLog(@"creating '%@' folder", bundlesPath);
    [bundlesField setTextColor: [NSColor textColor]];
    if(![fm fileExistsAtPath: bundlesPath isDirectory: &dir] || !dir) {
        if(![fm createDirectoryAtPath: bundlesPath attributes: nil]) {
            NSLog(@"failed");
            failed = [NSString stringWithFormat: NSLocalizedString(@"Could not create the '%@' folder", @""), bundlesPath];
            [bundlesField setTextColor: [NSColor redColor]];
        }
    }
    if(!failed) {
        NSLog(@"successful");
    }
    [progress incrementBy: 10.0];
    
    NSLog(@"Enabling mail plugins");
    [enablingField setTextColor: [NSColor textColor]];
    data = [NSData dataWithContentsOfFile: mailPrefsPath]; 
    if(data) {
        prefs = [NSPropertyListSerialization propertyListFromData: data mutabilityOption: NSPropertyListMutableContainersAndLeaves format: &format errorDescription: &failed];
    } else {
		prefs = [NSMutableDictionary dictionary];
    }
	
            [prefs setObject: @"1" forKey: @"EnableBundles"];
	
	NSString* compatVersion = [bundleProps objectForKey: @"MailbundleVersion"];
	if(compatVersion) {
		[prefs setObject: compatVersion forKey: @"BundleCompatibilityVersion"];
	}
	
            data = [NSPropertyListSerialization dataFromPropertyList: prefs format: format errorDescription: &failed];
            
            if(data) {
                [data writeToFile: mailPrefsPath atomically: NO];
    } else {
		failed = NSLocalizedString(@"Could not create the Mail preferences file", @"");
    }


    if(failed) {
        NSLog(@"failed");
        [enablingField setTextColor: [NSColor redColor]];
    } else {
        NSLog(@"successful");
    }
    [progress incrementBy: 10.0];
    
    NSLog(@"Copying mailbundle files");
    [installingField setTextColor: [NSColor textColor]];
    
    NSString* destPath = [bundlesPath stringByAppendingPathComponent: BUNDLE_NAME];
	NSArray* files = [fm directoryContentsAtPath: bundlesPath];
	int i, C;
	
	C = [files count];
	for(i=0; i<C; i++) {
		NSString* f = [files objectAtIndex: i];
		
		if([f hasPrefix: @"httpmail"] && [f hasSuffix: @".mailbundle"]) {
			NSLog(@"removing %@", f);
			
			NSString* toRemove = [bundlesPath stringByAppendingPathComponent: f];
			[fm removeFileAtPath: toRemove handler: self];
		}
	}
	
    if([fm fileExistsAtPath: destPath isDirectory: nil]) {
        NSLog(@"bundle already exists.  Delete it!");
        
        if(![fm removeFileAtPath: destPath handler: self]) {
            failed = NSLocalizedString(@"Could not remove old bundle", @"");
        }
    }
    
    if(!failed) {
        srcPath = [[[[NSBundle mainBundle] bundlePath] stringByDeletingLastPathComponent] stringByAppendingPathComponent: BUNDLE_NAME];
        
        if([fm fileExistsAtPath: srcPath]) {
            NSLog(@"copying bundle from '%@' to '%@'", srcPath, destPath);
            if(![fm copyPath: srcPath toPath: destPath handler: self]) {
                failed = NSLocalizedString(@"Could not install the plugin bundle", @"");
            }
        } else { 
            failed = NSLocalizedString(@"Can not find the httpmail plugin to install", @"");
        }
    }
    
    if(failed) {
        [installingField setTextColor: [NSColor redColor]];
        NSLog(@"failed");
    } else {
        NSLog(@"successful");
    }
    
    if(failed) {
        NSRunCriticalAlertPanel(NSLocalizedString(@"Installation Failed", @""), failed, NSLocalizedString(@"Quit", @""), nil, nil);
        
        [NSApp terminate: self];
    } else {
		NSRunInformationalAlertPanel(NSLocalizedString(@"Information", @""), NSLocalizedString(@"Installation Successful", @""), NSLocalizedString(@"Ok", @""), nil, nil);
        [NSApp terminate: self];
    }
    
    [doneButton setEnabled: YES];
    [progress stopAnimation: self];
}

- (IBAction)startInstall:(id)sender
{
    NSWindow* window = [NSApp mainWindow];
    
    [progress startAnimation: self];
    [NSTimer scheduledTimerWithTimeInterval: 1.0 target: self selector: @selector(tick:) userInfo: nil repeats: NO];
    [NSApp beginSheet: panel
        modalForWindow: window
        modalDelegate: nil
        didEndSelector: nil
        contextInfo: nil];    
}

-(BOOL)fileManager:(NSFileManager *)manager 
        shouldProceedAfterError:(NSDictionary *)errorDict
{
    int result;
    result = NSRunAlertPanel(NSLocalizedString(@"Installer Error", @""), NSLocalizedString(@"File operation error: %@ with file: %@", @""), NSLocalizedString(@"Stop", @""), NSLocalizedString(@"Proceed", @""), NULL, 
            [errorDict objectForKey:@"Error"], 
            [errorDict objectForKey:@"Path"]);
        
    if (result != NSAlertDefaultReturn)
        return YES;
    else
        return NO;
}

- (void)fileManager:(NSFileManager *)manager willProcessPath:(NSString *)path {
    NSLog(@"about to process: %@", path);
    [progress incrementBy: 10.0];
}

@end
