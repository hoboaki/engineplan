// 文字コード：UTF-8
#include "AeBaseNSApp.h"

#import <Cocoa/Cocoa.h>

//------------------------------------------------------------------------------
@interface AeBaseApp_Delegate : NSObject <NSApplicationDelegate>
/* Example: Fire has the same problem no explanation */
{
}
/* - (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication; */

@end

//------------------------------------------------------------------------------
@implementation AeBaseApp_Delegate
- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return NO;
}
@end

//------------------------------------------------------------------------------
void AeBaseNSApp_Initialize()
{
    @autoreleasepool {
        {// Application起動
            [NSApplication sharedApplication];

            AeBaseApp_Delegate* delegate = [[AeBaseApp_Delegate alloc] init];
            [NSApp setDelegate: delegate];

            [NSApp finishLaunching];
        }

        {// .app に移動
            NSString *path;
            path=[[NSBundle mainBundle] bundlePath];
            [[NSFileManager defaultManager] changeCurrentDirectoryPath:path];
        }
    }
}

//------------------------------------------------------------------------------
void AeBaseNSApp_Finalize()
{
	//[NSApp terminate:nil];	// This can also be exit(0);
}

//------------------------------------------------------------------------------
void AeBaseNSApp_PollEvent()
{
    while(1)
    {
        @autoreleasepool {
            NSEvent *event;
            event=[NSApp
                   nextEventMatchingMask:NSAnyEventMask
                   untilDate: [NSDate distantPast]
                   inMode: NSDefaultRunLoopMode
                   dequeue:YES];
            if(event!=nil)
            {
                [NSApp sendEvent:event];
                [NSApp updateWindows];
            }
            else
            {
                break;
            }
        }
    }
}

//------------------------------------------------------------------------------
void AeBaseNSApp_Terminate()
{
    [NSApp terminate:nil];
}

// EOF
