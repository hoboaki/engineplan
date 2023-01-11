// 文字コード：UTF-8
#include <ae/base/ResFile.hpp>

// includes
#include <ae/base/AutoMemBlock.hpp>
#include <ae/base/ResFileStream.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
const AutoMemBlock ResFile::Read(const char* path, IAllocator& allocator)
{
    // オープン
    ResFileStream stream;
    if (!stream.Open(path)) {
        AE_BASE_ASSERT_NOT_REACHED_MSGFMT(
            "ResFile named '%s' is failed to open.",
            path);
        return AutoMemBlock();
    }

    // メモリ準備
    const pword_t size = stream.Seek(0, ::ae::base::SeekOrigin::End);
    const pword_t bufferSize = stream.CalcReadBufferSize(size);
    ptr_t ptr =
        allocator.Alloc(bufferSize, stream.RequireReadBufferAlignment());
    if (ptr == 0) {
        AE_BASE_ASSERT_NOT_REACHED();
        return AutoMemBlock();
    }

    // 読み込み
    stream.Seek(0, ::ae::base::SeekOrigin::Begin);
    stream.Read(ptr, size);
    stream.Close();

    // 終了
    return AutoMemBlock(MemBlock(ptr, size), allocator);
}

} // namespace ae::base
// EOF
