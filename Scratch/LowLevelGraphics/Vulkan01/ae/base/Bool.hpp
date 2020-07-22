// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_BOOL_HPP)
#else
#define AE_BASE_INCLUDED_BOOL_HPP

#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Types
//@{
/// @brief BoolTmpl のPod版。
template< typename DATA_TYPE >
struct BoolPodTmpl
{
    //============================================================
    // private
    DATA_TYPE val_;

    //============================================================
    // public
    /// @name typedef
    //@{
    typedef DATA_TYPE DataType;
    //@}

    /// @name operator実装
    //@{
    /// @brief bool値代入。
    /// @details
    /// これを定義することで下記のコードが実行できるようになります。
    /// @code
    /// BoolPodTmpl< int > var;
    /// var = true; // 代入できる
    /// @endcode
    BoolPodTmpl< DataType >& operator=(const bool aVal)
    {
        val_ = DataType(aVal ? 1 : 0);
        return *this;
    }

    /// @brief bool値取得。
    /// @details
    /// これを定義することで下記のコードが実行できるようになります。
    /// @code
    /// void func( const BoolPodTmpl< int >& aVal )
    /// {
    ///     bool var = aVal; // boolの値を取得できるのでこのように代入できる
    /// }
    /// @endcode
    operator bool()const
    {
        return val_ != 0;
    }
    //@}
};

/// @brief 組み込み型を指定したbool。
/// @details
/// bool変数のサイズは環境によって変わります。 @n
/// それをを防ぎたいときにこのテンプレート構造体を使います。 @n
/// DATA_TYPEに指定した組み込み型を指定します。@n
/// データとしては0以外の値が入っていたらtrueと扱います。@n
template< typename DATA_TYPE >
class BoolTmpl : public BoolPodTmpl< DATA_TYPE >
{
public:
    /// @name コンストラクタ
    //@{
    /// falseとして作成。
    BoolTmpl()
    {
        BoolPodTmpl< DATA_TYPE >::val_ = false;
    }

    /// 値を指定して作成。
    BoolTmpl(const bool aVal)
    {
        BoolPodTmpl< DATA_TYPE >::val_ = aVal;
    }
    //@}
};

/// @name BoolTmpl BoolPodTmpl のtypedef。
//@{
typedef BoolPodTmpl< u8  > BoolPod8;  ///< 8bitPod版。
typedef BoolPodTmpl< u16 > BoolPod16; ///< 16bitPod版。
typedef BoolPodTmpl< u32 > BoolPod32; ///< 32bitPod版。
typedef BoolPodTmpl< u64 > BoolPod64; ///< 64bitPod版。
typedef BoolTmpl< u8  >    Bool8;  ///< 8bitクラス版。
typedef BoolTmpl< u16 >    Bool16; ///< 16bitクラス版。
typedef BoolTmpl< u32 >    Bool32; ///< 32bitクラス版。
typedef BoolTmpl< u64 >    Bool64; ///< 64bitクラス版。
typedef Bool8    Bool;    ///< 標準のクラス版(8bit)。
typedef BoolPod8 BoolPod; ///< 標準のPod版(8bit)。
//@}

//@}

}} // namespace
#endif
// EOF
