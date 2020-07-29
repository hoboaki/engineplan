// 文字コード：UTF-8
#include <ae/base/ResFileStream.hpp>

#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Unused.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
ResFileStream::ResFileStream()
: ext_()
{
}

//------------------------------------------------------------------------------
ResFileStream::ResFileStream(const char* path)
: ext_()
{
    const bool result = Open(path);
    AE_BASE_UNUSED(result);
    AE_BASE_ASSERT_MSGFMT(result, "Can't open resource file '%s'.", path);
}

//------------------------------------------------------------------------------
pword_t ResFileStream::RequireReadBufferAlignment()const
{
    return ReadBufferAlignment;
}

//------------------------------------------------------------------------------
pword_t ResFileStream::CalcReadBufferSize(const pword_t size)const
{
    return CalcReadBufferSize(size);
}

}} // namespace
// EOF
