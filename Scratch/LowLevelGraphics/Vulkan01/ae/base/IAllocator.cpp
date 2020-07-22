// 文字コード：UTF-8
#include <ae/base/IAllocator.hpp>

#include <memory>
#include <ae/base/FunctionAttribute.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Unused.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
namespace {

class tDefaultAllocatorObj
{
public:
    tDefaultAllocatorObj()
        : ptr(IAllocator::OperatorNewDelete())
    {
    }
    Pointer< IAllocator > ptr;
};

tDefaultAllocatorObj tDefaultAllocator;

} // namespace

//------------------------------------------------------------------------------
IAllocator::~IAllocator()
{
}

//------------------------------------------------------------------------------
IAllocator& IAllocator::Default()
{
    return *tDefaultAllocator.ptr;
}

//------------------------------------------------------------------------------
void IAllocator::SetDefault(IAllocator& aAllocator)
{
    tDefaultAllocator.ptr.reset(&aAllocator);
}

//------------------------------------------------------------------------------
IAllocator& IAllocator::OperatorNewDelete()
{
    class OperatorNewDeleteAllocator : public IAllocator
    {
    public:
        AE_BASE_OVERRIDE(ptr_t alloc(pword_t aSize, pword_t aAlignment))
        {
            AE_BASE_UNUSED(aAlignment);
            void* ptr = ::operator new(aSize, std::nothrow_t());
            AE_BASE_ASSERT_EQUALS(pword_t(ptr) % aAlignment, 0);
            return static_cast<ptr_t>(ptr);
        }
        AE_BASE_OVERRIDE(void free(ptr_t aPtr))
        {
            ::operator delete(aPtr, std::nothrow_t());
        }
    };
    static OperatorNewDeleteAllocator obj;
    return obj;
}

}} // namespace

//------------------------------------------------------------------------------
void* operator new(const std::size_t aSize, ::ae::base::IAllocator& aAllocator)
{
    return aAllocator.alloc(aSize);
}

//------------------------------------------------------------------------------
void* operator new[](const std::size_t aSize, ::ae::base::IAllocator& aAllocator)
{
    return aAllocator.alloc(aSize);
}

//------------------------------------------------------------------------------
void operator delete(void* aPtr, ::ae::base::IAllocator& aAllocator)
{
    aAllocator.free(::ae::base::ptr_t(aPtr));
}

//------------------------------------------------------------------------------
void operator delete[](void* aPtr, ::ae::base::IAllocator& aAllocator)
{
    aAllocator.free(::ae::base::ptr_t(aPtr));
}

// EOF
