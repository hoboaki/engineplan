// 文字コード：UTF-8
#include <ae/base/MemBlock.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
MemBlock::MemBlock()
: addr_(0)
, size_(0) {
}

//------------------------------------------------------------------------------
MemBlock::MemBlock(const ptr_t addr, const pword_t size)
: addr_(addr)
, size_(size) {
}

//------------------------------------------------------------------------------
bool MemBlock::IsNull() const {
    return addr_ == 0;
}

//------------------------------------------------------------------------------
ptr_t MemBlock::Head() const {
    return addr_;
}

//------------------------------------------------------------------------------
ptr_t MemBlock::Tail() const {
    return addr_ + size_;
}

//------------------------------------------------------------------------------
pword_t MemBlock::Size() const {
    return size_;
}

} // namespace base
} // namespace ae
// EOF
