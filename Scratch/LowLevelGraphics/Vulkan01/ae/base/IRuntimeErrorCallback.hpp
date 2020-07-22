// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_IRUNTIMEERRORCALLBACK_HPP)
#else
#define AE_BASE_INCLUDED_IRUNTIMEERRORCALLBACK_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Debug
//@{
/// 実行時エラー用コールバックインターフェースクラス。
class IRuntimeErrorCallback
{
public:
    // デストラクタ。
    virtual ~IRuntimeErrorCallback();

       /// @brief エラーが起きたときに呼ばれる関数。
       /// @details 
       /// この関数ではアプリケーションを強制終了するなど致命的な時に実行したい処理を行ってください。
    virtual void onRuntimeError() = 0;
};
//@}

}} // namespace
#endif
// EOF
