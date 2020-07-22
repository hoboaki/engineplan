// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_RESFILESTREAM_STDC_HPP)
#else
#define AE_BASE_INCLUDED_RESFILESTREAM_STDC_HPP

#include <cstdio>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

// C標準ライブラリ用のResFileStream拡張。
class ResFileStream_EXT
{
public:
    FILE* fp;

    ResFileStream_EXT();
};

}} // namespace
#endif
// EOF
