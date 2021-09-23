// 文字コード：UTF-8
#include "AeBaseNSScreen.h"

#import <Cocoa/Cocoa.h>

//------------------------------------------------------------------------------
void AeBaseNSScreen_GetMainScreenFrame( struct AeBaseNSRect* aRect )
{
    NSRect rect = [[NSScreen mainScreen] frame];
    aRect->originX = rect.origin.x;
    aRect->originY = rect.origin.y;
    aRect->sizeW   = rect.size.width;
    aRect->sizeH   = rect.size.height;
}

//------------------------------------------------------------------------------
void AeBaseNSScreen_GetMainScreenVisibleFrame( struct AeBaseNSRect* aRect )
{
    NSRect rect = [[NSScreen mainScreen] visibleFrame];
    aRect->originX = rect.origin.x;
    aRect->originY = rect.origin.y;
    aRect->sizeW   = rect.size.width;
    aRect->sizeH   = rect.size.height;
}

// EOF
