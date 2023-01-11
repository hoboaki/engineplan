// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_IALLOCATOR_HPP)
#else
#define AE_BASE_INCLUDED_IALLOCATOR_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <memory>

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-Memory
//@{
/// アロケータインターフェース。
class IAllocator {
public:
    virtual ~IAllocator();

    /// @name 定数
    //@{
    /// @brief デフォルトのアライメント値。
    /// @details
    /// 32bit環境だと4、64bit環境だと8になります。
    static const pword_t DefaultAlignment = sizeof(pword_t);
    //@}

    /// @name デフォルトのアロケータ
    //@{
    /// @brief デフォルトのアロケータ。
    /// @details 初期値は OperatorNewDelete() になっています。
    static IAllocator& Default();

    /// @brief デフォルトのアロケータを設定する。
    /// @param allocator 指定するアロケータ。
    /// @details
    /// 指定するアロケータはデフォルトのアロケータの設定が書き換わるまで生存しつづける必要があります。
    static void SetDefault(IAllocator& allocator);

    /// @brief operator new/delete を使うアロケータ。
    static IAllocator& OperatorNewDelete();
    //@}

    /// @name 仮想関数
    //@{
    /// @brief メモリ確保。
    /// @return 確保したメモリブロックの先頭アドレス。
    /// @param size 確保するメモリブロックのサイズ。
    /// @param alignment 確保するメモリブロックのアライメント。
    virtual ptr_t Alloc(pword_t size, pword_t alignment = DefaultAlignment) = 0;

    /// @brief メモリ解放。
    /// @param ptr 解放するメモリブロックの先頭アドレス。
    virtual void Free(ptr_t ptr) = 0;
    //@}
};
//@}

} // namespace ae::base

/// @addtogroup AeBase-Memory
//@{
/// @name IAllocator用operator new/delete
//@{
extern void* operator new(std::size_t, ::ae::base::IAllocator&);
extern void* operator new[](std::size_t, ::ae::base::IAllocator&);
extern void operator delete(void*, ::ae::base::IAllocator&);
extern void operator delete[](void*, ::ae::base::IAllocator&);
//@}
//@}
#endif
// EOF
