// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_DISPLAYCONTEXT_HPP)
#else
#define AE_BASE_INCLUDED_DISPLAYCONTEXT_HPP

#include <ae/base/Bool.hpp>
#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/OsType.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-System
//@{
/// Display クラスのコンテキスト。
class DisplayContext {
public:
    /// デフォルトの設定で作成する。
    DisplayContext();

#if defined(AE_BASE_OSTYPE_WINDOWSYSTEM)
    /// @name WindowSystem環境でのカスタマイズ
    //@{
    void
    SetLocationToCenter(); ///< 現在のwidthとheightの値を見て画面の中央にウィンドウがくるようにlocationX,Yを設定する。
    int LocationX() const;
    int LocationY() const;
    int Width() const;
    int Height() const;
    bool IsScreenDoubleBuffer() const;
    //@}
#endif

private:
#if defined(AE_BASE_OSTYPE_WINDOWSYSTEM)
    int locationX_;
    int locationY_;
    int width_;
    int height_;
    Bool32 isScreenDoubleBuffer_;
#endif
};
//@}

} // namespace base
} // namespace ae
#endif
// EOF
