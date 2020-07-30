// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// リソースメモリの種類。
enum class ResourceMemoryKind {
    /// 無効値。
    Invalid,

    /// GPU 専用メモリ。CPU からは直接参照することはできない。
    DeviceLocal,

    /// GPU は読み書き、CPU は読み込みのみできるGPU・CPU共有メモリ。
    SharedRead,

    /// GPU は読み書き、CPU は書き込みのみできるGPU・CPU共有メモリ。
    SharedWrite,

    /// GPU・CPU 共には読み書きができるGPU・CPU共有メモリ。
    SharedReadWrite,

    TERM,
};

} // namespace gfx_low
} // namespace ae
// EOF
