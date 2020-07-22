// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_ENUM_HPP)
#else
#define AE_BASE_INCLUDED_ENUM_HPP

#include <ae/base/BuiltInTypes.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Types
//@{
    /// @brief EnumTmpl のPod版。
template< typename TEnumType, typename TDataType >
struct EnumPodTmpl
{
    //============================================================
    // private
    TDataType val_;

    //============================================================
    // public

    /// @name typedef
    //@{
    typedef TEnumType EnumType;
    typedef TDataType DataType;
    //@}

    /// @name operator実装
    //@{
    /// @brief enum値代入。
    /// @details
    /// これを定義することで下記のコードが実行できるようになります。
    /// @code
    /// struct Color
    /// {
    ///    enum EnumType
    ///    {}
    ///         Red,
    ///         Green,
    ///         Blue,
    ///         TERM,
    ///    };
    /// };
    /// EnumPodTmpl< Color::EnumType, int > color;
    /// color = Color::Red; // 代入できる
    /// @endcode
    EnumPodTmpl< TEnumType, TDataType >& operator=(const TEnumType aVal)
    {
        val_ = DataType(aVal);
        return *this;
    }

    /// @brief enum値取得。
    /// @details
    /// これを定義することで下記のコードが実行できるようになります。
    /// @code
    /// void func( const EnumPodTmpl< Color , int >& aColor )
    /// {
    ///     Color var = aColor; // enumの値を取得できるのでこのように代入できる
    /// }
    /// @endcode
    operator TEnumType()const
    {
        return TEnumType(val_);
    }
    //@}
};

/// @brief 組み込み型を指定したenum値。
/// @details
/// enumの変数サイズは環境によって変わります。 @n
/// それをを防ぎたいときにこのテンプレート構造体を使います。 @n
/// TDataTypeに指定した組み込み型を指定します。@n
/// データとしては0以外の値が入っていたらtrueと扱います。@n
template< typename TEnumType, typename TDataType >
class EnumTmpl : public EnumPodTmpl< TEnumType, TDataType >
{
public:
    /// @name コンストラクタ
    //@{
    /// 0として作成。
    EnumTmpl()
    {
        EnumPodTmpl< TEnumType, TDataType >::val_ = 0;
    }

    /// 値を指定して作成。
    EnumTmpl(const TEnumType aVal)
    {
        EnumPodTmpl< TEnumType, TDataType >::val_ = DataType(aVal);
    }
    //@}
};

/// @name EnumTmpl EnumPodTmpl をラップする型。
//@{
template< typename TEnumType > class Enum8 : public EnumTmpl< TEnumType, s8  > { public: Enum8() {};  Enum8(const TEnumType aVal) { EnumTmpl< TEnumType, s8   >::val_ = s8(aVal); } };  ///< 8bitクラス版。
template< typename TEnumType > class Enum16 : public EnumTmpl< TEnumType, s16 > { public: Enum16() {}; Enum16(const TEnumType aVal) { EnumTmpl< TEnumType, s16  >::val_ = s16(aVal); } };  ///< 16bitクラス版。
template< typename TEnumType > class Enum32 : public EnumTmpl< TEnumType, s32 > { public: Enum32() {}; Enum32(const TEnumType aVal) { EnumTmpl< TEnumType, s32  >::val_ = s32(aVal); } }; ///< 32bitクラス版。
template< typename TEnumType > class Enum64 : public EnumTmpl< TEnumType, s64 > { public: Enum64() {}; Enum64(const TEnumType aVal) { EnumTmpl< TEnumType, s64  >::val_ = s64(aVal); } }; ///< 64bitクラス版。

template< typename TEnumType > class Enum : public Enum8< TEnumType > { public: Enum(const TEnumType aVal) { Enum8< TEnumType >::val_ = aVal; } }; ///< 標準のクラス版(8bit)。
//@}

//@}

}} // namespace
#endif
// EOF
