// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_DISPLAYCONTEXT_HPP)
#else
#define AE_BASE_INCLUDED_DISPLAYCONTEXT_HPP

#include <ae/base/Bool.hpp>
#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/FixedString.hpp>
#include <ae/base/OsType.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-System
//@{
/// Display クラスのコンテキスト。
class DisplayContext {
public:
    /// @name コンストラクタ
    //@{
    /// デフォルトの設定で作成する。
    DisplayContext();
    //@}

    /// @name プロパティ
    //@{
    /// ウィンドウタイトル。（初期値："AdelEngine Application"）
    /// @details Windows プラットフォームでのみ使われます。
    const char* WindowTitle() const { return windowTitle_.ReadPtr(); }

    /// WindowTitle() の設定。
    DisplayContext& SetWindowTitle(const char* aText) {
        windowTitle_ = aText;
        return *this;
    }
    //@}

#if defined(AE_BASE_OSTYPE_WINDOWSYSTEM)
    /// @name WindowSystem環境でのカスタマイズ（TODO: #if を切って関数自体はどのプラットフォームでも呼べるようにする）
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
    FixedString<char, 64> windowTitle_ = "AdelEngine Application";
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
