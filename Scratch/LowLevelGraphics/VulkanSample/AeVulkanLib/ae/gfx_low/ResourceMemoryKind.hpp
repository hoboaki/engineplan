// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae::gfx_low {

/// リソースメモリの種類。
enum class ResourceMemoryKind
{
    /// 無効値。
    Invalid,

    /// GPU にとって最も高速なメモリ。
    /// @details
    /// GPU が処理する上で最も高速なメモリの種類です。
    ///
    /// Device::IsDeviceLocalMemoryShared() が true のデバイスは
    /// 共有メモリを DeviceLocal メモリとして扱うため、
    /// SharedNonCached と同じ扱いになります。
    ///
    /// Device::IsDeviceLocalMemoryShared() が false のデバイスは
    /// メモリの内容を CPU からは直接参照することはできません。
    /// CPU が用意したデータを DeviceLocal に配置したい場合は
    /// コマンドを使って Shared 系のメモリから転送する必要があり、
    /// 逆に読み取りたい場合は Shared 系メモリに転送する必要があります。
    DeviceLocal,

    /// CPU 上でキャッシュしないGPU・CPU共有メモリ。
    /// @details
    /// Map/Unmap 時に FlushRange や InvalidateRange
    /// が不要で扱いやすい種類です。
    /// ただし、CPU からのアクセスよりも GPU
    /// からのアクセススピードを優先する種類とも言えるため、
    /// CPU上での読み書きの回数が少ないメモリでの使用を推奨します。
    SharedNonCached,

    /// GPU は読み書き、CPU は書き込みのみできるGPU・CPU共有メモリ。
    /// @details
    /// Map/Unmap 時に FlushRange や InvalidateRange が必要です。
    /// 頻繁にCPU上で読み書きするメモリでの使用を推奨します。
    SharedCached,

    TERM,
};

} // namespace ae::gfx_low
// EOF
