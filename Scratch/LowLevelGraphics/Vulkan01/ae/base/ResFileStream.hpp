// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RESFILESTREAM_HPP)
#else
#define AE_BASE_INCLUDED_RESFILESTREAM_HPP

#include <ae/base/FunctionAttribute.hpp>
#include <ae/base/IAllocator.hpp>
#include <ae/base/IReadStream.hpp>

// EXT
#include <ae/base/ResFileStream_STDC.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-IO
//@{
    /// @brief アプリケーションのリソースファイルを読み込むクラス。
    /// @details
    /// リソースファイルは読み込み専用です。書き込むことはできません。
    /// @n
    /// ルートディレクトリはOSによって異なります。 @n
    /// Windowsだと ".exeファイルがあるディレクトリ" がルートになります。 @n
    /// MacOSXだと ".app/Contents/Resources" がルートになります。@n
    /// iOSだと ".app/" がルートになります。@n
    /// @n
    /// OSによっては想定しないファイルがリソースファイルと同じ場所に置かれることもあります。@n
/// そのため "data" や "resource" といった名前のフォルダを１つほりそれ以下に全てのリソースファイルを配置することをおすすめします。@n
class ResFileStream : public IReadStream
{
public:
    /// @name 定数
    //@{
    /// ファイル読み込み先アドレスに求められるアライメント値。
    static const pword_t ReadBufferAlignment = IAllocator::DefaultAlignment;
    //@}

    /// @name 関数
    //@{
    /// @brief  指定のデータサイズを読み込む時に必要なバッファサイズを求める。
    /// @param aSize 読み込みデータサイズ。
    /// @details
    /// 実行環境によっては実際のデータサイズよりも大きいバッファサイズを要求することがあるため、
    /// バッファ領域は必ずこの関数で求められたサイズを確保してください。
    static pword_t CalcReadBufferSize(pword_t aSize);
    //@}

    /// @name コンストラクタとデストラクタ
    //@{
    /// @brief 何もせず作成する。
    /// @details ファイルオープンは open() を使用してください。
    ResFileStream();

    /// @brief 指定のファイルをオープンしつつ作成する。
    /// @param aPath オープンするファイルパス。
    /// @details オープンに失敗したらエラーになります。
    ResFileStream(const char* aPath);

    /// @brief デストラクタ
    /// @details オープン中なら自動で close() を呼びます。
    virtual ~ResFileStream();
    //@}

    /// @name オープン
    //@{
    /// @brief 指定のファイルをオープンする。
    /// @return オープンに成功したらtrue。
    /// @param aPath オープンするファイルパス。
    /// @details 既にオープンしている場合は自動で close() してからオープンします。
    bool open(const char* aPath);
    //@}

    // IReadStreamの実装。
    AE_BASE_OVERRIDE(pword_t requireReadBufferAlignment()const);
    AE_BASE_OVERRIDE(pword_t calcReadBufferSize(pword_t aSize)const);
    AE_BASE_OVERRIDE(pword_t seek(int aOffset, SeekOrigin::EnumType aOrigin));
    AE_BASE_OVERRIDE(pword_t read(ptr_t aBuffer, pword_t aSize));
    AE_BASE_OVERRIDE(void close());

private:
    ResFileStream_EXT mExt;
};

//@}

}} // namespace
#endif
// EOF
