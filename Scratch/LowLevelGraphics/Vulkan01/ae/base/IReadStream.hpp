// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_IREADSTREAM_HPP)
#else
#define AE_BASE_INCLUDED_IREADSTREAM_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/SeekOrigin.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-IO
//@{
/// 読み込み専用ストリーム。
class IReadStream
{
public:
    virtual ~IReadStream();

    /// @brief データ読み込み時のバッファに求められるアライメント値を取得する。
    /// 実行環境によってこの値が異なることがあるため、
    /// バッファの先頭アドレスはこの関数で得られたアライメント値になるようにしてください。
    virtual pword_t requireReadBufferAlignment()const = 0;

    /// @brief 指定のデータサイズを読み込む時に必要なバッファサイズを求める。
    /// @param aSize 読み込みデータサイズ。
    /// @details
    /// 実行環境によっては実際のデータサイズよりも大きいバッファサイズを要求することがあるため、
    /// バッファ領域は必ずこの関数で求められたサイズを確保してください。
    virtual pword_t calcReadBufferSize(pword_t aSize)const = 0;

    /// @brief ストリームの位置を変更し変更後の位置を取得する。
    /// @return 変更後の位置。0は先頭を示す。
    /// @param aOffset aOriginを基準としたオフセット位置。
    /// @param aOrigin 変更の基準。
    virtual pword_t seek(int aOffset, SeekOrigin::EnumType aOrigin) = 0;

    /// @brief データを読み込む。
    /// @return 実際に読み込んだバイト数。
    /// @param aBuffer 読み込んだデータを格納するバッファの先頭アドレス。
    /// @param aSize 読み込むバイト数。
    /// @details
    /// バッファには calcReadBufferSize() で求められたサイズ分書き込まれるので注意してください。
    virtual pword_t read(ptr_t aBuffer, pword_t aSize) = 0;

    /// @brief 開いているストリームを閉じる。
    /// @details 
    /// 既にストリームが閉じた状態で呼ぶとエラーになります。
    virtual void close() = 0;
};
//@}

}} // namespace
#endif
// EOF
