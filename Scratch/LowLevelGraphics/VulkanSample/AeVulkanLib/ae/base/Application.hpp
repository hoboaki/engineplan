// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_APPLICATION_HPP)
#else
#define AE_BASE_INCLUDED_APPLICATION_HPP

#include <ae/base/AppEvent.hpp>
#include <ae/base/Enum.hpp>
#include <ae/base/NonCopyable.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/SdkHeader.hpp>

#if defined(AE_BASE_OS_WINDOWS)
#include <ae/base/Application_Windows.hpp>
#elif defined(AE_BASE_OS_MACOSX)
#include <ae/base/Application_MacOSX.hpp>
#else
#include <ae/base/Application_Default.hpp>
#endif

namespace ae::base {
class Argument;
class Display;
} // namespace ae::base

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-System
//@{
/// @brief アプリケーションの全体を扱うクラス。
/// @details
/// このクラスのインスタンスはフレームワークによって生成されます。@n
/// xmain 関数が呼ばれた時点でこのクラスは生成されているため Instance()
/// を使ってアクセスできます。@n
class Application : ::ae::base::Noncopyable<Application> {
public:
    /// インスタンスにアクセス。
    static Application& Instance();

    // コンストラクタと
    Application(const Argument&);
    ~Application();

    /// コマンドライン引数を取得する。
    const base::Argument& Argument() const;

    /// @brief アプリケーションの終了を要求する。
    /// @details
    /// 任意のタイミングでアプリケーションを終了したい場合にこの関数を呼びます。@n
    /// そうすると ReceiveEvent() は次の呼び出しで AppEvent::Quit を返します。
    /// @n
    void Quit();

    /// @name  イベント
    //@{
    AppEvent::EnumType ReceiveEvent(); ///< 新しいイベントを受け取る。
    AppEvent::EnumType LastEvent()
        const; ///< 最後に受け取ったイベントを取得する。
    //@}

    //============================================================
    // 内部処理用関数。
    void registerDisplay_(Display&);
    void unregisterDisplay_(Display&);

private:
    const base::Argument& argument_;
    Enum32<AppEvent::EnumType> lastEvent_;
    Pointer<Display> displayPtr_;
    Application_Ext ext_;
    //------------------------------------------------------------------------------
    AppEvent::EnumType ReceiveEventCore();
};
//@}

} // namespace ae::base
#endif
// EOF
