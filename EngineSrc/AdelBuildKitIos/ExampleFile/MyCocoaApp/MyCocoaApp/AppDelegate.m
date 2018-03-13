//
//  AppDelegate.m
//  MyCocoaApp
//
//  Created by あっきー on 2017/10/02.
//  Copyright © 2017年 あっきー. All rights reserved.
//

#import "AppDelegate.h"

extern void MyFunc();

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    MyFunc();
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


@end
