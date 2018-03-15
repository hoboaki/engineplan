// 文字コード：UTF-8
#include "AeBaseUIScreen.h"

#import <UIKit/UIKit.h>

//------------------------------------------------------------------------------
void AeBaseUIScreen_GetMainScreenBounds( struct AeBaseUIRect* aRect )
{ 
    CGRect rect = [[UIScreen mainScreen] bounds];
    aRect->originX = rect.origin.x;
    aRect->originY = rect.origin.y;
    aRect->sizeW   = rect.size.width;
    aRect->sizeH   = rect.size.height;
}

// EOF
