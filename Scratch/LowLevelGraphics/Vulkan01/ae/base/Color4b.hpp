// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_COLOR4U8_HPP)
#else
#define AE_BASE_INCLUDED_COLOR4U8_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ShortString.hpp>

namespace ae {
namespace base {
struct Color3bPod;
struct Color4Pod;
}}

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Util
//@{
/// 8bit符号無し整数をRGBAの順に並べた色構造体。
struct Color4bPod
{
    //============================================================
    /// @name 定数取得
    //@{
    static const Color4bPod Zero();     ///< 0の色。
    static const Color4bPod One();      ///< R,G,B,Aが全て255の色。
    static const Color4bPod UnitR();    ///< Rだけ1の色。
    static const Color4bPod UnitG();    ///< Gだけ1の色。
    static const Color4bPod UnitB();    ///< Bだけ1の色。
    static const Color4bPod UnitA();    ///< Aだけ1の色。
    //@}

    //============================================================
    /// @name 変数
    //@{
    u8 r; ///< r。
    u8 g; ///< g。
    u8 b; ///< b。
    u8 a; ///< a。
    //@}

    //============================================================
    /// @name 変換
    //@{
    const Color3bPod toRGB()const;
    const Color3bPod toRRR()const;
    const Color3bPod toGGG()const;
    const Color3bPod toBBB()const;
    const Color3bPod toAAA()const;
    const Color4bPod toRRRR()const;
    const Color4bPod toGGGG()const;
    const Color4bPod toBBBB()const;
    const Color4bPod toAAAA()const;
    const Color4Pod toRGBAf()const;
    //@}

    //============================================================
    /// @name ユーティリティ
    //@{
    /// r,g,b,a形式の文字列に変換。
    const ShortString toShortString()const;
    //@}
};

/// Color4bPod のクラス版。
class Color4b : public Color4bPod
{
public:
    //============================================================
    /// @name コンストラクタ
    //@{
    Color4b(); ///< Zero() で作成。
    Color4b(const Color4bPod& aRGBA); ///< コピーして作成。
    Color4b(u8 aR, u8 aG, u8 aB, u8 aA); ///< RGBAを指定して作成。
    //@}
};
//@}

}} // namespace
#endif
// EOF
