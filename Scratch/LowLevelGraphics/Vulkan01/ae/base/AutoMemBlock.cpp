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
    ptr_t ptr = aAllocator.Alloc(aSize, aAlignment);
    if (ptr == 0) {
        // 失敗
        return;
    }

    // 設定
    block_ = MemBlock(ptr, aSize);
    allocatorPtr_.Set(aAllocator);
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
    Clear();
}

//------------------------------------------------------------------------------
bool AutoMemBlock::IsEmpty()const
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
const MemBlock& AutoMemBlock::Ref()const
{
    AE_BASE_ASSERT(!IsEmpty());
    return block_;
}

//------------------------------------------------------------------------------
AutoMemBlock& AutoMemBlock::operator=(const AutoMemBlock& aRHS)
{
    // まずクリア
    Clear();

    // つぎに移動
    block_ = aRHS.block_;
    allocatorPtr_ = aRHS.allocatorPtr_;

    // 相手をクリア
    aRHS.block_ = MemBlock();
    aRHS.allocatorPtr_.Reset();

    // 終了
    return *this;
}

//------------------------------------------------------------------------------
const MemBlock& AutoMemBlock::operator*()const
{
    return Ref();
}

//------------------------------------------------------------------------------
const MemBlock* AutoMemBlock::operator->()const
{
    return &Ref();
}

}} // namespace
// EOF
