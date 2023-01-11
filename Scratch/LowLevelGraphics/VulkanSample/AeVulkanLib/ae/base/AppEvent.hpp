// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_APPEVENT_HPP)
#else
#define AE_BASE_INCLUDED_APPEVENT_HPP

//------------------------------------------------------------------------------
namespace ae::base {

/// @addtogroup AeBase-System
//@{
/// アプリケーションイベントの種類。
struct AppEvent
{
    enum EnumType
    {
        Quit, ///< 終了する。
        Update, ///< 状態を更新する。

        TERM,

        // alias
        INVALID, ///< 無効なイベント。
    };
};
//@}

} // namespace ae::base
#endif
// EOF
