// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_HASH_HPP)
#else
#define AE_BASE_INCLUDED_HASH_HPP

#include <ae/base/BuiltInTypes.hpp>

namespace ae {
namespace base {
class MemBlock;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Util
//@{
/// ハッシュ値を求める関数群。
struct Hash
{
    /// CRC16の値を求める。
    static uint16 CRC16(const MemBlock&);

    /// CRC32(Castagnoli)の値を求める。
    static uint32 CRC32(const MemBlock&);
};
//@}

}} // namespace
#endif
// EOF
