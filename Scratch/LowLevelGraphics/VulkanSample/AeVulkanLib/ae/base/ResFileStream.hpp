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
namespace ae::base {

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
/// そのため "data" や "resource"
/// といった名前のフォルダを１つほりそれ以下に全てのリソースファイルを配置することをおすすめします。@n
class ResFileStream : public IReadStream {
public:
    /// @name 定数
    //@{
    /// ファイル読み込み先アドレスに求められるアライメント値。
    static const pword_t ReadBufferAlignment = IAllocator::DefaultAlignment;
    //@}

    /// @name 関数
    //@{
    /// @brief  指定のデータサイズを読み込む時に必要なバッファサイズを求める。
    /// @param size 読み込みデータサイズ。
    /// @details
    /// 実行環境によっては実際のデータサイズよりも大きいバッファサイズを要求することがあるため、
    /// バッファ領域は必ずこの関数で求められたサイズを確保してください。
    static pword_t StaticCalcReadBufferSize(pword_t size);
    //@}

    /// @name コンストラクタとデストラクタ
    //@{
    /// @brief 何もせず作成する。
    /// @details ファイルオープンは Open() を使用してください。
    ResFileStream();

    /// @brief 指定のファイルをオープンしつつ作成する。
    /// @param path オープンするファイルパス。
    /// @details オープンに失敗したらエラーになります。
    ResFileStream(const char* path);

    /// @brief デストラクタ
    /// @details オープン中なら自動で Close() を呼びます。
    virtual ~ResFileStream();
    //@}

    /// @name オープン
    //@{
    /// @brief 指定のファイルをオープンする。
    /// @return オープンに成功したらtrue。
    /// @param path オープンするファイルパス。
    /// @details 既にオープンしている場合は自動で Close()
    /// してからオープンします。
    bool Open(const char* path);
    //@}

    // IReadStreamの実装。
    AE_BASE_OVERRIDE(pword_t RequireReadBufferAlignment() const);
    AE_BASE_OVERRIDE(pword_t CalcReadBufferSize(pword_t size) const);
    AE_BASE_OVERRIDE(pword_t Seek(int offset, SeekOrigin::EnumType origin));
    AE_BASE_OVERRIDE(pword_t Read(ptr_t buffer, pword_t size));
    AE_BASE_OVERRIDE(void Close());

private:
    ResFileStream_EXT ext_;
};

//@}

} // namespace ae::base
#endif
// EOF
