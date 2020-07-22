// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_IALLOCATOR_HPP)
#else
#define AE_BASE_INCLUDED_IALLOCATOR_HPP

#include <memory>
#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Memory
//@{
/// アロケータインターフェース。
class IAllocator
{
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
    /// @param aAllocator 指定するアロケータ。
    /// @details
    /// 指定するアロケータはデフォルトのアロケータの設定が書き換わるまで生存しつづける必要があります。
    static void SetDefault(IAllocator& aAllocator);

    /// @brief operator new/delete を使うアロケータ。
    static IAllocator& OperatorNewDelete();
    //@}

    /// @name 仮想関数
    //@{
    /// @brief メモリ確保。
    /// @return 確保したメモリブロックの先頭アドレス。
    /// @param aSize 確保するメモリブロックのサイズ。
    /// @param aAlignment 確保するメモリブロックのアライメント。
    virtual ptr_t alloc(pword_t aSize, pword_t aAlignment = DefaultAlignment) = 0;

    /// @brief メモリ解放。
    /// @param aPtr 解放するメモリブロックの先頭アドレス。
    virtual void free(ptr_t aPtr) = 0;
    //@}
};
//@}

}} // namespace

/// @addtogroup AeBase-Memory
//@{
/// @name IAllocator用operator new/delete
//@{
extern void* operator new(std::size_t, ::ae::base::IAllocator&);
extern void* operator new[](std::size_t, ::ae::base::IAllocator&);
extern void  operator delete(void*, ::ae::base::IAllocator&);
extern void  operator delete[](void*, ::ae::base::IAllocator&);
//@}
//@}
#endif
// EOF
