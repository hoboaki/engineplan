// 文字コード：UTF-8
#include "AeBaseUIApplicationDelegate.h"

#import <QuartzCore/QuartzCore.h>
#include "EntryPoint_Sync.h"

//------------------------------------------------------------------------------
@implementation AeBaseUIApplicationDelegate
@synthesize displayLink;

#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
{   
    // .app に移動
    NSString *path;
    path=[[NSBundle mainBundle] bundlePath];   
    [[NSFileManager defaultManager] changeCurrentDirectoryPath:path];
    
    // XMainを起動
    AeBaseEntryPointSync_XMainSignal();
    AeBaseEntryPointSync_UIMainWait();
    
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application 
{
    // 毎フレーム処理を登録解除    
    [displayLink invalidate];
    self.displayLink = nil;
}


//- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
//}


//- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
//}


- (void)applicationDidBecomeActive:(UIApplication *)application 
{
    // 毎フレーム処理を登録
    self.displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(onUpdate:)];
    ((CADisplayLink*)displayLink).preferredFramesPerSecond = 60;
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}


- (void)applicationWillTerminate:(UIApplication *)application 
{
    // Quitイベント送信
    AeBaseEntryPointSync_SetAppEvent( AeBaseAppEvent_Quit );
    AeBaseEntryPointSync_XMainSignal();
    AeBaseEntryPointSync_UIMainWait();
}

- (void)onUpdate: (id)sender
{
    // Updateイベント送信
    AeBaseEntryPointSync_SetAppEvent( AeBaseAppEvent_Update );
    AeBaseEntryPointSync_XMainSignal();
    AeBaseEntryPointSync_UIMainWait();    
}

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [super dealloc];
}


@end
// EOF
