// 文字コード：UTF-8
#include <ae/base/AutoMemBlock.hpp>

// includes
#include <ae/base/IAllocator.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock()
: block_()
, allocatorPtr_()
{
}

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock(
    const pword_t size,
    IAllocator& allocator,
    const pword_t alignment)
: block_()
, allocatorPtr_()
{
    // 確保
    ptr_t ptr = allocator.Alloc(size, alignment);
    if (ptr == 0) {
        // 失敗
        return;
    }

    // 設定
    block_ = MemBlock(ptr, size);
    allocatorPtr_.Set(allocator);
}

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock(const MemBlock& block, IAllocator& allocator)
: block_(block)
, allocatorPtr_(allocator)
{
}

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock(const AutoMemBlock& other)
: block_()
, allocatorPtr_()
{
    *this = other;
}

//------------------------------------------------------------------------------
AutoMemBlock::~AutoMemBlock()
{
    Clear();
}

//------------------------------------------------------------------------------
bool AutoMemBlock::IsEmpty() const
{
    return allocatorPtr_.IsNull();
}

//------------------------------------------------------------------------------
void AutoMemBlock::Clear()
{
    if (IsEmpty()) {
        return;
    }
    allocatorPtr_->Free(block_.Head());
    allocatorPtr_.Reset();
    block_ = MemBlock();
}

//------------------------------------------------------------------------------
const MemBlock& AutoMemBlock::Ref() const
{
    AE_BASE_ASSERT(!IsEmpty());
    return block_;
}

//------------------------------------------------------------------------------
AutoMemBlock& AutoMemBlock::operator=(const AutoMemBlock& rHS)
{
    // まずクリア
    Clear();

    // つぎに移動
    block_ = rHS.block_;
    allocatorPtr_ = rHS.allocatorPtr_;

    // 相手をクリア
    rHS.block_ = MemBlock();
    rHS.allocatorPtr_.Reset();

    // 終了
    return *this;
}

//------------------------------------------------------------------------------
const MemBlock& AutoMemBlock::operator*() const
{
    return Ref();
}

//------------------------------------------------------------------------------
const MemBlock* AutoMemBlock::operator->() const
{
    return &Ref();
}

} // namespace ae::base
// EOF
