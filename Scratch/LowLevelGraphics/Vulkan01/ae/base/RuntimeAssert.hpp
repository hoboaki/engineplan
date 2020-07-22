// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RUNTIMEASSERT_HPP)
#else
#define AE_BASE_INCLUDED_RUNTIMEASSERT_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/Console.hpp>
#include <ae/base/PointerCheck.hpp>
#include <ae/base/RuntimeError.hpp>
#include <ae/base/ShortString.hpp>
#include <ae/base/ToShortString.hpp>
#include <ae/base/ValueInRange.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

// 実行時Assertを扱う空間。
struct RuntimeAssert
{
    static const char* const Separator;      // 分離する文字列。
    static const char* const Header;         // ヘッダ。
    static const char* const FileLineFmt;    // ファイルと行数。
    static const char* const LabelCondition; // ラベル:Condition。
    static const char* const LabelMessage;   // ラベル:Message。
};

}} // namespace

// 実行時Assertの本体。AE_BASE_CONFIG_ENABLE_RUNTIME_ERRORが定義されているときに動作。
#if defined(AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR)
#define AE_BASE_RUNTIME_ASSERT( aCond , ... ) \
    do \
    { \
        if( !(aCond) ) \
        { \
            AE_BASE_COUT_LINE( ::ae::base::RuntimeAssert::Separator ); \
            AE_BASE_COUT_LINE_WITH_TIME( ::ae::base::RuntimeAssert::Header ); \
            AE_BASE_COUTFMT_LINE( ::ae::base::RuntimeAssert::FileLineFmt , __FILE__ , __LINE__ ); \
            AE_BASE_COUT( ::ae::base::RuntimeAssert::LabelCondition ); \
            AE_BASE_COUT_LINE( #aCond ); \
            AE_BASE_COUT( ::ae::base::RuntimeAssert::LabelMessage ); \
            AE_BASE_COUTFMT_LINE( __VA_ARGS__ , #aCond ); \
            AE_BASE_COUT_LINE( ::ae::base::RuntimeAssert::Separator ); \
            ::ae::base::RuntimeError::OnError(); \
            while(1){} \
        } \
    }while(0)

#else
#define AE_BASE_RUNTIME_ASSERT( aCond , ... ) do{}while(false)
#endif
//@}

/// @addtogroup AeBase-Debug
//@{
/// @name 実行時アサート
//@{

/// @brief メッセージ付きアサート。指定の条件式がtrueであることをチェックする。
/// @param aCond 条件式。
/// @param aMsg メッセージ文字列。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_MSG( aCond , aMsg ) AE_BASE_RUNTIME_ASSERT( aCond , "%s" , aMsg )

/// @brief printfフォーマットのメッセージ付きアサート。指定の条件式がtrueであることをチェックする。
/// @param aCond 条件式。
/// @param aFormat printfフォーマット文字列。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_MSGFMT( aCond , aFormat , ... ) AE_BASE_RUNTIME_ASSERT( aCond , aFormat , __VA_ARGS__ )

/// @brief 指定の条件式がtrueであることをチェックする。
/// @param aCond 条件式。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT( aCond ) AE_BASE_ASSERT_MSG( aCond , #aCond )

/// @brief NULLであるべき値をチェックする。
/// @param aVal チェックする値。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_SHOULD_NULL( aVal ) \
    AE_BASE_ASSERT_MSG( (aVal)==0 \
    , "Value is not Null (%s)\n" \
    , AE_BASE_TO_SHORT_STRING( aVal ).readPtr() \
    ) 

/// @brief NULLじゃない値をさしているかチェックする。
/// @param aVal チェックする値。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_NOT_NULL( aVal ) AE_BASE_ASSERT_MSG( (aVal)!=0 , "Value is Null\n" )

/// @briefポインタとして有効な値であることをチェックする。
/// @param aVal チェックする値。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_POINTER( aVal ) do { if ( !::ae::base::PointerCheck::IsValid( aVal ) ) { AE_BASE_ERROR_INVALID_VALUE( reinterpret_cast< ::ae::base::pword_t >( aVal ) ); } } while(false)

/// @brief 到達したらエラーにする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// 第1引数以降にprintfの書式でメッセージを指定してください。@n
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_NOT_REACHED_MSGFMT( aFormat , ... ) AE_BASE_ASSERT_MSGFMT( false , aFormat , __VA_ARGS__ )
#define AE_BASE_ASSERT_NOT_REACHED_MSG( aMsg ) AE_BASE_ASSERT_MSG( false , aMsg )

/// @brief 到達したらエラーにする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_NOT_REACHED() AE_BASE_ASSERT_NOT_REACHED_MSG( "Should nod reach here.\n" )
 
/// @brief 不正な値としてその値をコンソールにダンプしつつエラーにする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ERROR_INVALID_VALUE( aVal ) \
    AE_BASE_ASSERT_NOT_REACHED_MSGFMT( \
        "%s is invalid value(%s)\n" \
        , #aVal \
        , AE_BASE_TO_SHORT_STRING(aVal).readPtr() \
        )

/// @brief AE_BASE_ERROR_INVALID_VALUE のenum版。
/// @see AE_BASE_ERROR_INVALID_VALUE
#define AE_BASE_ERROR_INVALID_ENUM( aVal ) AE_BASE_ERROR_INVALID_VALUE( int( aVal ) )

/// @brief ２つの値が等しいことをチェックする。
/// @param aVal1 チェックする値。
/// @param aVal2 チェックする値。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_EQUALS( aVal1 , aVal2 ) \
    AE_BASE_ASSERT_MSGFMT( aVal1 == aVal2 \
    , "%s(%s) is not equals %s(%s).\n" \
    , #aVal1 , AE_BASE_TO_SHORT_STRING( aVal1 ).readPtr() \
    , #aVal2 , AE_BASE_TO_SHORT_STRING( aVal2 ).readPtr() \
    )

/// @brief ２つの値が等しくないことをチェックする。
/// @param aVal1 チェックする値。
/// @param aVal2 チェックする値。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_NOT_EQUALS( aVal1 , aVal2 ) \
    AE_BASE_ASSERT_MSGFMT( aVal1 != aVal2 \
    , "%s(%s) is quals %s(%s).\n" \
    , #aVal1 , AE_BASE_TO_SHORT_STRING( aVal1 ).readPtr() \
    , #aVal2 , AE_BASE_TO_SHORT_STRING( aVal2 ).readPtr() \
    )

/// @def AE_BASE_TEST
/// @brief テストコマンドを実行する。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#if defined(AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR)
    #define AE_BASE_TEST( aCond ) (aCond)
#else
    #define AE_BASE_TEST( aCond ) do{}while(false)
#endif

/// @brief aVal < aTermValであることをチェックする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_LESS(aVal, aTermVal) AE_BASE_ASSERT_RANGE_CORE2(AE_BASE_VALUE_IN_RANGE_LESS, aVal, aTermVal)

/// @brief aVal <= aMaxValであることをチェックする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @copydetails AE_BASE_ASSERT_MSG
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_LESS_EQUALS(aVal, aMaxVal) AE_BASE_ASSERT_RANGE_CORE2(AE_BASE_VALUE_IN_RANGE_LESS_EQUALS, aVal, aMaxVal)

/// @brief aMinVal <= aVal <= aMaxValであることをチェックする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_MIN_MAX(aVal, aMinVal, aMaxVal) AE_BASE_ASSERT_RANGE_CORE3(AE_BASE_VALUE_IN_RANGE_MIN_MAX, aMinVal ,aVal ,aMaxVal)

/// @brief aMinVal <= aVal < aTermValであることをチェックする。
/// @see ae::base::RuntimeError
/// @see AE_BASE_CONFIG_ENABLE_RUNTIME_ERROR
/// @details
/// アサートに失敗したらそれぞれの値をコンソールにダンプしエラーコールバックをコールします。@n
/// エラーが無効なときは何もしません。
#define AE_BASE_ASSERT_MIN_TERM(aVal, aMinVal, aTermVal) AE_BASE_ASSERT_RANGE_CORE3(AE_BASE_VALUE_IN_RANGE_MIN_TERM, aMinVal, aVal, aTermVal)

/// @brief aEnumValueが 0 <= aEnumValue < TERMであることをチェックする。
/// @details
/// 調査するEnumにTERMが定義されている必要があります。
#define AE_BASE_ASSERT_ENUM(aEnumValue, aEnumType) AE_BASE_ASSERT_MIN_TERM(int(aEnumValue), int(0), int(aEnumType::TERM))

//@}
//@}
    
// 範囲チェックアサートの実装。
#define AE_BASE_ASSERT_RANGE_CORE2(func, aVal1, aVal2) \
    AE_BASE_ASSERT_MSGFMT(func(aVal1 , aVal2) \
    , "Value is not in range.\n" \
      "aVal1 : %s \naVal2 : %s\n" \
    , AE_BASE_TO_SHORT_STRING(aVal1).readPtr() \
    , AE_BASE_TO_SHORT_STRING(aVal2).readPtr() \
    )
#define AE_BASE_ASSERT_RANGE_CORE3(func, aVal1, aVal2, aVal3) \
    AE_BASE_ASSERT_MSGFMT(func(aVal1, aVal2, aVal3)  \
    , "Value is not in range.\n" \
    "aVal1 : %s \naVal2 : %s \naVal3 : %s\n" \
    , AE_BASE_TO_SHORT_STRING(aVal1).readPtr() \
    , AE_BASE_TO_SHORT_STRING(aVal2).readPtr() \
    , AE_BASE_TO_SHORT_STRING(aVal3).readPtr() \
    )

#endif
// EOF
