// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RESFILE_HPP)
#else
#define AE_BASE_INCLUDED_RESFILE_HPP

#include <ae/base/IAllocator.hpp>

namespace ae {
namespace base {
class AutoMemBlock;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-IO
//@{
/// @brief アプリケーションのリソースファイルにアクセスするクラス。
/// @see ResFileStream
class ResFile
{
public:
    /// @brief 指定のファイルを読み込む。
    /// @return 読み込んだデータ。
    /// @param aPath ファイルパス。
    /// @param aAllocator 読み込んだデータを格納するアロケータ。
    /// @details
    /// ファイルが見つからない場合、読み込めなかった場合はエラーになります。 @n
    /// 戻り値のMemBlockのサイズは読み込んだファイルのサイズと同じです。 @n
    static const AutoMemBlock Read(const char* aPath, IAllocator& aAllocator = IAllocator::Default());
};
//@}

}} // namespace
#endif
// EOF
