// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_DISPLAY_HPP)
#else
#define AE_BASE_INCLUDED_DISPLAY_HPP

#include <ae/base/DisplayContext.hpp>
#include <ae/base/Os.hpp>
#include <ae/base/Screen.hpp>

#if defined(AE_BASE_OS_WINDOWS)
#include <ae/base/Display_Windows.hpp>
#elif defined(AE_BASE_OS_MACOSX)
#include <ae/base/Display_MacOSX.hpp>
#elif defined(AE_BASE_OS_IOS)
#include <ae/base/Display_iOS.hpp>
#else
#include <ae/base/Display_Default.hpp>
#endif
//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-System
//@{

    /// @class ae::base::Display
    /// @brief ディスプレイ。
    /// @details 
    /// ここでいうディスプレイとはWindowsやMacOSX環境では１つのウィンドウのことを指します。@n
    /// ウィンドウという概念がない環境では仮想的なウィンドウが存在するとします。@n
    /// @n
    /// ディスプレイは1つ以上のスクリーンを所持します。 @n
    /// WindowsやMacOSX環境では１つのウィンドウが１つのスクリーンを所持すると考えます。@n
/// Nintendo DSなど1つのハードに2つ以上の画面が存在するハードではスクリーンが画面の数だけ所持すると考えます。@n
class Display
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    Display(const DisplayContext&);
    ~Display();
    //@}

    /// @name スクリーン
    //@{
    int screenCount()const; ///< スクリーンの総数を取得する。
    Screen& screenAtIndex(int aIndex); ///< 指定番目のスクリーンを取得する。
    Screen& mainScreen(); ///< メインとなるスクリーンを取得する。
    //@}

    /// @name コントロール
    //@{
    /// 表示する。
    void show();
    //@}

    /// @name 状態取得
    //@{        
    /// ディスプレイが閉じられたか。
    bool isClosed()const;
    //@}

    //============================================================
    // 内部実装用関数群。
    const DisplayContext context_()const; // コンテキストの取得。
    Display_Ext& ext_(); // 拡張。

private:
    DisplayContext mContext;
    Display_Ext mExt;
};

//@}

}} // namespace
#endif
// EOF
