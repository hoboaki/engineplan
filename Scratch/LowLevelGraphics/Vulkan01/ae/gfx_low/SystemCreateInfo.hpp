// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SystemDebugLevel.hpp>

namespace ae {
    namespace base {
class IAllocator;
}
}

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// System オブジェクト作成に必要な情報。
class SystemCreateInfo {
public:
    /// @name コンストラクタ
    //@{
    SystemCreateInfo();
    //@}

    /// @name システムデバッグレベル（初期値：NoDebug）
    //@{
    SystemDebugLevel DebugLevel() const { return debugLevel_; }
    SystemCreateInfo& SetDebugLevel(SystemDebugLevel level);
    //@}

    /// @name オブジェクト生成時に確保・破棄時に解放されるメモリ用のアロケータ。nullptr 時はデフォルトアロケータを使用。（初期値：nullptr）
    //@{
    ::ae::base::IAllocator* ObjectAllocator() const {
        return objectAllocator_.get();
    }
    SystemCreateInfo& SetObjectAllocator(::ae::base::IAllocator* allocator) {
        objectAllocator_.reset(allocator);
        return *this;
    }
    //@}

    /// @name 関数内で確保・関数終了時に解放されるメモリ用のアロケータ。nullptr 時はデフォルトアロケータを使用。（初期値：nullptr）
    //@{
    ::ae::base::IAllocator* TempWorkAllocator() const {
        return tempWorkAllocator_.get();
    }
    SystemCreateInfo& SetTempWorkAllocator(::ae::base::IAllocator* allocator) {
        tempWorkAllocator_.reset(allocator);
        return *this;
    }
    //@}


private:
    SystemDebugLevel debugLevel_ = SystemDebugLevel::NoDebug;
    ::ae::base::Pointer<::ae::base::IAllocator> objectAllocator_;
    ::ae::base::Pointer<::ae::base::IAllocator> tempWorkAllocator_;
};

}  // namespace gfx_low
}  // namespace ae
// EOF
