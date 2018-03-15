// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_UIAPPLICATIONDELEGATE_H)
#else
#define AE_BASE_INCLUDED_UIAPPLICATIONDELEGATE_H

#include <UIKit/UIKit.h>

//------------------------------------------------------------------------------
@interface AeBaseUIApplicationDelegate : NSObject <UIApplicationDelegate> 
{
}
@property (nonatomic, retain) id displayLink;

- (void)onUpdate:(id)sender;
@end

#endif
// EOF
