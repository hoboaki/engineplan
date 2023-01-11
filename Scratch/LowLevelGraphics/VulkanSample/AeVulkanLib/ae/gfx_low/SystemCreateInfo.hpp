// 文字コード：UTF-8
#pragma once

#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/SystemDebugLevel.hpp>

namespace ae::base {
class IAllocator;
}

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// System オブジェクト作成に必要な情報。
class SystemCreateInfo {
public:
    /// @name コンストラクタ
    //@{
    SystemCreateInfo();
    //@}

    /// @name プロパティ
    //@{
    /// システムデバッグレベル。（初期値：NoDebug）
    SystemDebugLevel DebugLevel() const { return debugLevel_; }

    /// DebugLevel() の設定。
    SystemCreateInfo& SetDebugLevel(SystemDebugLevel level);

    /// オブジェクト生成時に確保・破棄時に解放されるメモリ用のアロケータ。（初期値：nullptr）
    /// @details nullptr 時はデフォルトアロケータを使用。
    ::ae::base::IAllocator* ObjectAllocator() const
    {
        return objectAllocator_.Get();
    }

    /// ObjectAllocator() の設定。
    SystemCreateInfo& SetObjectAllocator(::ae::base::IAllocator* allocator)
    {
        objectAllocator_.Reset(allocator);
        return *this;
    }

    /// 関数内で確保・関数終了時に解放されるメモリ用のアロケータ。（初期値：nullptr）
    /// @details nullptr 時はデフォルトアロケータを使用。
    ::ae::base::IAllocator* TempWorkAllocator() const
    {
        return tempWorkAllocator_.Get();
    }

    /// TempWorkAllocator() の設定。
    SystemCreateInfo& SetTempWorkAllocator(::ae::base::IAllocator* allocator)
    {
        tempWorkAllocator_.Reset(allocator);
        return *this;
    }
    //@}

private:
    SystemDebugLevel debugLevel_ = SystemDebugLevel::NoDebug;
    ::ae::base::Pointer<::ae::base::IAllocator> objectAllocator_;
    ::ae::base::Pointer<::ae::base::IAllocator> tempWorkAllocator_;
};

} // namespace ae::gfx_low
// EOF
