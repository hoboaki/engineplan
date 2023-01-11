// 文字コード：UTF-8
#pragma once

#include <ae/base/Noncopyable.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/gfx_low/ResourceMemory.hpp>

namespace ae::gfx_low {
class Device;
class ResourceMemoryAllocInfo;
} // namespace ae::gfx_low

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// リソースメモリをデストラクタで解放する　ResourceMemory
/// 専用のスマートポインタのようなクラス。
class UniqueResourceMemory : base::Noncopyable<UniqueResourceMemory> {
public:
    /// @name コンストラクタとデストラクタ
    //@{
    UniqueResourceMemory() { Reset(); }
    UniqueResourceMemory(
        Device* device,
        const ResourceMemoryAllocInfo& allocInfo)
    : UniqueResourceMemory()
    {
        Reset(device, allocInfo);
    }
    UniqueResourceMemory(Device* device, const ResourceMemory& memory)
    : UniqueResourceMemory()
    {
        Reset(device, memory);
    }
    ~UniqueResourceMemory();
    //@}

    /// @name リセット
    //@{
    void Reset();
    void Reset(Device* device, const ResourceMemoryAllocInfo& allocInfo);
    void Reset(Device* device, const ResourceMemory& memory);
    //@}

    /// @name 演算子オーバーロード
    //@{
    /// 参照演算子。
    const ResourceMemory& operator*() const { return memory_; }

    /// アドレス演算子。
    const ResourceMemory* operator->() const { return &memory_; }
    //@}

private:
    base::Pointer<Device> device_;
    ResourceMemory memory_;
};

} // namespace ae::gfx_low
// EOF
