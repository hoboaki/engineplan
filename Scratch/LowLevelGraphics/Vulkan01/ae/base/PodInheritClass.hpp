// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_PodINHERITCLASS_HPP)
#else
#define AE_BASE_INCLUDED_PodINHERITCLASS_HPP

#include <ae/base/StaticAssert.hpp>
#include <ae/base/TypeTraits.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Types
//@{
/// @brief Pod型を継承するクラス用のテンプレートクラス。
/// @details ゼロクリアコンストラクタとコピーコンストラクタを自動で作成します。
template< typename Pod_TYPE >
class PodInheritClass : public Pod_TYPE
{
public:
    /// Pod型。
    typedef Pod_TYPE PodType;

    /// 0クリアの状態で作成する。
    PodInheritClass()
    {
        PodType obj = {};
        static_cast<PodType&>(*this) = obj;
    }

    /// 引数の値をコピーして作成する。
    PodInheritClass(const PodType& aObj)
        : PodType(aObj)
    {
    }

private:
    AE_BASE_STATIC_ASSERT(TypeTraits::IsPod< PodType >::Value);
};

//@}

}} // namespace
#endif
// EOF
