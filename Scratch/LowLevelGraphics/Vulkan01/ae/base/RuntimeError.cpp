// 文字コード：UTF-8
#include <ae/base/RuntimeError.hpp>

#include <cassert>
#include <ae/base/Compiler.hpp>
#include <ae/base/Config.hpp>
#include <ae/base/FunctionAttribute.hpp>
#include <ae/base/IRuntimeErrorCallback.hpp>
#include <ae/base/Os.hpp>

// for MessageBox
#if (defined(AE_BASE_OS_WIN32) && defined(AE_BASE_COMPILER_MSVC))
#include <crtdbg.h>
#endif

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
namespace {

IRuntimeErrorCallback* tCallbackPtr = 0;
#if defined(AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR)
IRuntimeErrorCallback& tCallbackObj()
{
    // ここに到達するということは既に致命的な状態なはずなので
    // ポインタチェックはしない。
    return tCallbackPtr != 0
        ? *tCallbackPtr
        : RuntimeError::DefaultCallback();
}
#endif

} // namespace

//------------------------------------------------------------------------------
IRuntimeErrorCallback& RuntimeError::DefaultCallback()
{
    // コールバックの実装。
    class Callback : public IRuntimeErrorCallback
    {
    public:
        AE_BASE_OVERRIDE(void onRuntimeError())
        {
        #if defined(AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR)
                    // 標準のアサートで止めてみる。
            assert(false && "Runtime Error.");

            // メッセージボックスで止めてみる。
        #if (defined(AE_BASE_OS_WIN32) && defined(AE_BASE_COMPILER_MSVC)) 
            MessageBox(0, L"エラーが発生しました。ログを確認してください。", L"Runtime Error", MB_OK);
        #endif
        #endif
        }
    };

    // コールバックを返す
    static Callback obj;
    return obj;
}

//------------------------------------------------------------------------------
void RuntimeError::SetCallback(IRuntimeErrorCallback& aCallback)
{
    tCallbackPtr = &aCallback;
}

//------------------------------------------------------------------------------
void RuntimeError::OnError()
{
#if defined(AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR)
    tCallbackObj().onRuntimeError();
#endif
}

}} // namespace
// EOF
