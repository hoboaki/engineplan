// 文字コード：UTF-8
#include <ae/base/AutoMemBlock.hpp>

#include <ae/base/IAllocator.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock()
: mBlock()
, mAllocatorPtr()
{
}

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock(
    const pword_t aSize,
    IAllocator& aAllocator,
    const pword_t aAlignment
    )
: mBlock()
, mAllocatorPtr()
{
    // 確保
    ptr_t ptr = aAllocator.alloc(aSize, aAlignment);
    if (ptr == 0) {
        // 失敗
        return;
    }

    // 設定
    mBlock = MemBlock(ptr, aSize);
    mAllocatorPtr.set(aAllocator);
}

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock(const MemBlock& aBlock, IAllocator& aAllocator)
: mBlock(aBlock)
, mAllocatorPtr(aAllocator)
{
}

//------------------------------------------------------------------------------
AutoMemBlock::AutoMemBlock(const AutoMemBlock& aOther)
: mBlock()
, mAllocatorPtr()
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
    return mAllocatorPtr.isNull();
}

//------------------------------------------------------------------------------
void AutoMemBlock::clear()
{
    if (isEmpty()) {
        return;
    }
    mAllocatorPtr->free(mBlock.head());
    mAllocatorPtr.reset();
    mBlock = MemBlock();
}

//------------------------------------------------------------------------------
const MemBlock& AutoMemBlock::ref()const
{
    AE_BASE_ASSERT(!isEmpty());
    return mBlock;
}

//------------------------------------------------------------------------------
AutoMemBlock& AutoMemBlock::operator=(const AutoMemBlock& aRHS)
{
    // まずクリア
    clear();

    // つぎに移動
    mBlock = aRHS.mBlock;
    mAllocatorPtr = aRHS.mAllocatorPtr;

    // 相手をクリア
    aRHS.mBlock = MemBlock();
    aRHS.mAllocatorPtr.reset();

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
