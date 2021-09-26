// 文字コード：UTF-8
#include <ae/base/Screen.hpp>

#include "AeBaseNSMetalView.h"

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Screen_Ext::Screen_Ext() {
}

//------------------------------------------------------------------------------
void* Screen_Ext::MetalLayer() {
    return AeBaseNSMetalView_GetLayer(metalView);
}

} // namespace base
} // namespace ae
// EOF
