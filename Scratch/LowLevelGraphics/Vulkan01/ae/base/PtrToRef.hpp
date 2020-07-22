// 文字コード：UTF-8
#pragma once

#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// ポインタが有効なアドレスを示していることをチェックしつつ参照に変換する。
template <typename T>
T& PtrToRef(T* ptr) {
    AE_BASE_ASSERT_POINTER(ptr);
    return *ptr;
}

}  // namespace base
}  // namespace ae
// EOF
