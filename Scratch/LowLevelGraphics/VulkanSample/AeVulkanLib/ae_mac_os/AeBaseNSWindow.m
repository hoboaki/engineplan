// 文字コード：UTF-8
#include "AeBaseNSWindow.h"

#import <Cocoa/Cocoa.h>

//------------------------------------------------------------------------------
@interface AeBaseOpenGLWindow : NSWindow
{
@private
    void* mOwnerPtr;
    int* mIsClosedPtr;
    AeBaseNSWindow_CBKeyEvent mCBKeyEvent;
    AeBaseNSWindow_CBModKeyEvent mCBModKeyEvent;
    AeBaseNSWindow_CBMouseEvent mCBMouseEvent;
}
- (void**) ownerPtr;
- (int**) isClosedPtr;
- (AeBaseNSWindow_CBKeyEvent*) cbKeyEventPtr;
- (AeBaseNSWindow_CBModKeyEvent*) cbModKeyEventPtr;
- (AeBaseNSWindow_CBMouseEvent*) cbMouseEventPtr;
@end

//------------------------------------------------------------------------------
@implementation AeBaseOpenGLWindow
- (id) initWithContentRect: (NSRect)rect styleMask:(NSWindowStyleMask)wndStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)deferFlg
{
	id result = [super initWithContentRect:rect styleMask:wndStyle backing:bufferingType defer:deferFlg];

	[[NSNotificationCenter defaultCenter]
     addObserver:self
     selector:@selector(windowDidResize:)
     name:NSWindowDidResizeNotification
     object:self];

	[[NSNotificationCenter defaultCenter]
     addObserver:self
     selector:@selector(windowWillClose:)
     name:NSWindowWillCloseNotification
     object:self];

	[self setAcceptsMouseMovedEvents:YES];

	return result;
}

- (void) windowDidResize: (NSNotification *)notification
{
}

- (void) windowWillClose: (NSNotification *)notification
{
    *mIsClosedPtr = 1;
}

- (void) flagsChanged: (NSEvent *)aEvent
{
    // 変数準備
	unsigned int flags;

    // フラグ取得
	flags = [aEvent modifierFlags];

    // コールバック
    mCBModKeyEvent(
        mOwnerPtr
        , ( flags & NSShiftKeyMask )
        , ( flags & NSControlKeyMask )
        , ( flags & NSAlternateKeyMask )
        );
}

- (void) keyDown:(NSEvent *)aEvent
{
    NSString* chrsNoMod;
    chrsNoMod = [aEvent charactersIgnoringModifiers];
    if ( 0 < [chrsNoMod length] )
    {
        mCBKeyEvent( mOwnerPtr , [chrsNoMod characterAtIndex:0] , 1 );
    }
}

- (void) keyUp:(NSEvent *)aEvent
{
    NSString* chrsNoMod;
    chrsNoMod = [aEvent charactersIgnoringModifiers];
    if ( 0 < [chrsNoMod length] )
    {
        mCBKeyEvent( mOwnerPtr , [chrsNoMod characterAtIndex:0] , 0 );
    }
}

- (void) mouseEventFunc:(NSEvent *)theEvent
{
    NSPoint pos = [theEvent locationInWindow];
    mCBMouseEvent( mOwnerPtr , (int)[NSEvent pressedMouseButtons] , pos.x , pos.y );
}

- (void) mouseEntered:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) mouseExited:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) mouseMoved:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) mouseDown:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) mouseDragged:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) mouseUp:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) rightMouseDown:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) rightMouseDragged:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) rightMouseUp:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) otherMouseDown:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) otherMouseDragged:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void) otherMouseUp:(NSEvent *)theEvent
{
    [self mouseEventFunc:theEvent];
}

- (void**) ownerPtr
{
    return &mOwnerPtr;
}

- (int**) isClosedPtr
{
    return &mIsClosedPtr;
}

- (AeBaseNSWindow_CBKeyEvent*) cbKeyEventPtr
{
    return &mCBKeyEvent;
}

- (AeBaseNSWindow_CBModKeyEvent*) cbModKeyEventPtr
{
    return &mCBModKeyEvent;
}

- (AeBaseNSWindow_CBMouseEvent*) cbMouseEventPtr
{
    return &mCBMouseEvent;
}
@end
//------------------------------------------------------------------------------
struct AeBaseNSWindow* AeBaseNSWindow_Create(
    const float aPosX
    , const float aPosY
    , const float aWidth
    , const float aHeight
    , void* aOwnerPtr
    , int* aIsClosedPtr
    , AeBaseNSWindow_CBKeyEvent aCBKeyEvent
    , AeBaseNSWindow_CBModKeyEvent aCBModKeyEvent
    , AeBaseNSWindow_CBMouseEvent aCBMouseEvent
    )
{
    @autoreleasepool {
        NSRect contRect;
        contRect = NSMakeRect( aPosX , aPosY , aWidth , aHeight );
        unsigned int winStyle=
        NSTitledWindowMask|
        NSClosableWindowMask|
        NSMiniaturizableWindowMask;

        AeBaseOpenGLWindow* window =[AeBaseOpenGLWindow alloc];
        *[window ownerPtr] = aOwnerPtr;
        *[window isClosedPtr] = aIsClosedPtr;
        *[window cbKeyEventPtr] = aCBKeyEvent;
        *[window cbModKeyEventPtr] = aCBModKeyEvent;
        *[window cbMouseEventPtr] = aCBMouseEvent;

        [window
        initWithContentRect:contRect
        styleMask:winStyle
        backing:NSBackingStoreBuffered
            defer:NO];
        
        return (__bridge struct AeBaseNSWindow*)window;
    }
}

//------------------------------------------------------------------------------
void AeBaseNSWindow_Destroy( struct AeBaseNSWindow* aWindow )
{
}

//------------------------------------------------------------------------------
void AeBaseNSWindow_Show( struct AeBaseNSWindow* aWindow )
{
    @autoreleasepool {
        AeBaseOpenGLWindow* window = (__bridge AeBaseOpenGLWindow*)aWindow;

        **[window isClosedPtr] = 0;
        [window makeKeyAndOrderFront:nil];
        [window makeMainWindow];

        [NSApp activateIgnoringOtherApps:YES];
    }
}

// EOF
