// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_MEMBLOCK_HPP)
#else
#define AE_BASE_INCLUDED_MEMBLOCK_HPP

#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Memory
//@{
/// メモリブロック。
class MemBlock {
public:
    /// @name コンストラクタ。
    //@{
    /// サイズ0のメモリブロックを作成。
    MemBlock();

    /// アドレス・サイズを指定して作成。
    MemBlock(ptr_t addr, pword_t size);

    /// アドレス・サイズを指定して作成。
    MemBlock(void* addr, pword_t size)
    : MemBlock(ptr_t(addr), size)
    {
    }

    /// アドレス・サイズを指定して作成。
    MemBlock(const void* addr, pword_t size)
    : MemBlock(ptr_t(const_cast<void*>(addr)), size)
    {
    }
    //@}

    /// @name プロパティの取得。
    //@{
    bool IsNull() const; ///< 先頭アドレスが0か。
    ptr_t Head() const; ///< 先頭アドレスを取得。
    ptr_t Tail() const; ///< 終端アドレス( Head() + Size() )を取得。
    pword_t Size() const; ///< ブロックのバイト数を取得。
    //@}

private:
    ptr_t addr_;
    pword_t size_;
};
//@}

} // namespace ae::base
#endif
// EOF
