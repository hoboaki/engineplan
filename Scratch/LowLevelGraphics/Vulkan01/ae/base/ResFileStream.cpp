// 文字コード：UTF-8
#include <ae/base/ResFileStream.hpp>

#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Unused.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
ResFileStream::ResFileStream()
: mExt()
{
}

//------------------------------------------------------------------------------
ResFileStream::ResFileStream(const char* aPath)
: mExt()
{
    const bool result = open(aPath);
    AE_BASE_UNUSED(result);
    AE_BASE_ASSERT_MSGFMT(result, "Can't open resource file '%s'.", aPath);
}

//------------------------------------------------------------------------------
pword_t ResFileStream::requireReadBufferAlignment()const
{
    return ReadBufferAlignment;
}

//------------------------------------------------------------------------------
pword_t ResFileStream::calcReadBufferSize(const pword_t aSize)const
{
    return CalcReadBufferSize(aSize);
}

}} // namespace
// EOF
