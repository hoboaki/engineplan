// 文字コード：UTF-8
#include <ae/base/AutoMemBlock.hpp>

#include <ae/base/IAllocator.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock()
: block_()
, allocatorPtr_()
{
}

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock(
    const pword_t aSize,
    IAllocator& aAllocator,
    const pword_t aAlignment
    )
: block_()
, allocatorPtr_()
{
    // 確保
    ptr_t ptr = aAllocator.alloc(aSize, aAlignment);
    if (ptr == 0) {
        // 失敗
        return;
    }

    // 設定
    block_ = MemBlock(ptr, aSize);
    allocatorPtr_.set(aAllocator);
}

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock(const MemBlock& aBlock, IAllocator& aAllocator)
: block_(aBlock)
, allocatorPtr_(aAllocator)
{
}

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock(const AutoMemBlock& aOther)
: block_()
, allocatorPtr_()
{
    *this = aOther;
}

//------------------------------------------------------------------------------
AutoMemBlock::~AutoMemBlock()
{
    clear();
}

//------------------------------------------------------------------------------
bool AutoMemBlock::isEmpty()const
{
    return allocatorPtr_.isNull();
}

//------------------------------------------------------------------------------
void AutoMemBlock::clear()
{
    if (isEmpty()) {
        return;
    }
    allocatorPtr_->free(block_.head());
    allocatorPtr_.reset();
    block_ = MemBlock();
}

//------------------------------------------------------------------------------
const MemBlock& AutoMemBlock::ref()const
{
    AE_BASE_ASSERT(!isEmpty());
    return block_;
}

//------------------------------------------------------------------------------
AutoMemBlock& AutoMemBlock::operator=(const AutoMemBlock& aRHS)
{
    // まずクリア
    clear();

    // つぎに移動
    block_ = aRHS.block_;
    allocatorPtr_ = aRHS.allocatorPtr_;

    // 相手をクリア
    aRHS.block_ = MemBlock();
    aRHS.allocatorPtr_.reset();

    // 終了
    return *this;
}

//------------------------------------------------------------------------------
const MemBlock& AutoMemBlock::operator*()const
{
    return ref();
}

//------------------------------------------------------------------------------
const MemBlock* AutoMemBlock::operator->()const
{
    return &ref();
}

}} // namespace
// EOF
