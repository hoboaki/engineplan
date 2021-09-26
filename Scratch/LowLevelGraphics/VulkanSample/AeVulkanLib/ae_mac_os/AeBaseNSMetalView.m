// 文字コード：UTF-8
#include "AeBaseNSMetalView.h"

#include <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

//------------------------------------------------------------------------------
@interface AeBaseMetalView : NSView
- (instancetype)initWithFrame:(NSRect)frame
                      highDPI:(BOOL)highDPI;

- (void)updateDrawableSize;
- (NSView *)hitTest:(NSPoint)point;

@property (assign, readonly) NSInteger tag;
@property (nonatomic) BOOL highDPI;

@end

@implementation AeBaseMetalView


/* Return a Metal-compatible layer. */
+ (Class)layerClass
{
    return NSClassFromString(@"CAMetalLayer");
}

/* Indicate the view wants to draw using a backing layer instead of drawRect. */
- (BOOL)wantsUpdateLayer
{
    return YES;
}

/* When the wantsLayer property is set to YES, this method will be invoked to
 * return a layer instance.
 */
- (CALayer*)makeBackingLayer
{
    return [self.class.layerClass layer];
}

- (instancetype)initWithFrame:(NSRect)frame
                      highDPI:(BOOL)highDPI;
{
    if ((self = [super initWithFrame:frame])) {
        self.highDPI = highDPI;
        self.wantsLayer = YES;

        /* Allow resize. */
        self.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;

        //SDL_AddEventWatch(SDL_MetalViewEventWatch, self);

        [self updateDrawableSize];
    }

    return self;
}

- (void)dealloc
{
    //SDL_DelEventWatch(SDL_MetalViewEventWatch, self);
    [super dealloc];
}

- (NSInteger)tag
{
    return AE_BASE_METALVIEW_TAG;
}

- (void)updateDrawableSize
{
    CAMetalLayer *metalLayer = (CAMetalLayer *)self.layer;
    NSSize size = self.bounds.size;
    NSSize backingSize = size;

    if (self.highDPI) {
        /* Note: NSHighResolutionCapable must be set to true in the app's
         * Info.plist in order for the backing size to be high res.
         */
        backingSize = [self convertSizeToBacking:size];
    }

    metalLayer.contentsScale = backingSize.height / size.height;
    metalLayer.drawableSize = NSSizeToCGSize(backingSize);
}

- (NSView *)hitTest:(NSPoint)point {
    return nil;
}

@end

//------------------------------------------------------------------------------
struct AeBaseNSMetalView* AeBaseNSMetalView_Setup(
    struct AeBaseNSWindow* aWindow) {
    @autoreleasepool {
        NSWindow* window = (NSWindow*)aWindow;
        NSView *view = window.contentView;
        BOOL highDPI = FALSE;
        AeBaseMetalView* newView;
        struct AeBaseNSMetalView* structView;

        newView = [[AeBaseMetalView alloc] initWithFrame:view.frame
                                                    highDPI:highDPI];
        if (newView == nil) {
            return NULL;
        }

        [view addSubview:newView];

        structView = (struct AeBaseNSMetalView*)CFBridgingRetain(newView);
        [newView release];
        return structView;
    }
}

//------------------------------------------------------------------------------
void AeBaseNSMetalView_DestroyView(struct AeBaseNSMetalView* view)
{
    @autoreleasepool {
        AeBaseMetalView* metalView = CFBridgingRelease(view);
        [metalView removeFromSuperview];
    }
}

//------------------------------------------------------------------------------
void* AeBaseNSMetalView_GetLayer(struct AeBaseNSMetalView* view)
{
    @autoreleasepool {
        AeBaseMetalView* metalView = (__bridge AeBaseMetalView*)view;
        return (__bridge void*)metalView.layer;
    }
}

//------------------------------------------------------------------------------
void AeBaseNSMetalView_GetDrawableSize(struct AeBaseNSWindow* window, int* w, int* h)
{
    @autoreleasepool {
        NSWindow* nswindow = (NSWindow*)window;
        NSView* contentView = nswindow.contentView;
        AeBaseMetalView* metalview = [contentView viewWithTag: AE_BASE_METALVIEW_TAG];
        if (metalview) {
            CAMetalLayer* layer = (CAMetalLayer*)metalview.layer;
            assert(layer != NULL);
            if (w) {
                *w = layer.drawableSize.width;
            }
            if (h) {
                *h = layer.drawableSize.height;
            }
        } else {
            /* Fall back to the viewport size. */
            NSRect viewport = [contentView bounds];
            // if (window->flags & SDL_WINDOW_ALLOW_HIGHDPI) {
            //     /* This gives us the correct viewport for a Retina-enabled view, only
            //     * supported on 10.7+. */
            //     if ([contentView respondsToSelector:@selector(convertRectToBacking:)]) {
            //         viewport = [contentView convertRectToBacking:viewport];
            //     }
            // }
            if (w) {
                *w = viewport.size.width;
            }
            if (h) {
                *h = viewport.size.height;
            }
        }
    }
}

// EOF
