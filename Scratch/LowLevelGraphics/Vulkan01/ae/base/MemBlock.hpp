// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_MEMBLOCK_HPP)
#else
#define AE_BASE_INCLUDED_MEMBLOCK_HPP

#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Memory
//@{
/// メモリブロック。
class MemBlock
{
public:
    /// @name コンストラクタ。
    //@{
    /// サイズ0のメモリブロックを作成。
    MemBlock();

    /// アドレス・サイズを指定して作成。
    MemBlock(ptr_t aAddr, pword_t aSize);
    //@}

    /// @name プロパティの取得。
    //@{
    bool    isNull()const; ///< 先頭アドレスが0か。
    ptr_t   head()const; ///< 先頭アドレスを取得。
    ptr_t   tail()const; ///< 終端アドレス( head() + size() )を取得。
    pword_t size()const; ///< ブロックのバイト数を取得。
    //@}

private:
    ptr_t   mAddr;
    pword_t mSize;
};
//@}

}} // namespace
#endif
// EOF
