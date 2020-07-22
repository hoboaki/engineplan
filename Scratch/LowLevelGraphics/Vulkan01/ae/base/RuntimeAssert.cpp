// 文字コード：UTF-8
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
const char* const RuntimeAssert::Separator      = "############################################################";
const char* const RuntimeAssert::Header         = "Assertion Failed.";
const char* const RuntimeAssert::FileLineFmt    = "File: %s(%d)";
const char* const RuntimeAssert::LabelCondition = "Condition:";
const char* const RuntimeAssert::LabelMessage   = "Message:";

}} // namespace
// EOF
