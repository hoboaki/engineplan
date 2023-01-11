// 文字コード：UTF-8
#include <ae/base/IAllocator.hpp>

// includes
#include <ae/base/FunctionAttribute.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/Unused.hpp>
#include <memory>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
namespace {

class tDefaultAllocatorObj {
public:
    tDefaultAllocatorObj()
    : ptr(IAllocator::OperatorNewDelete())
    {
    }
    Pointer<IAllocator> ptr;
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
void IAllocator::SetDefault(IAllocator& allocator)
{
    tDefaultAllocator.ptr.Reset(&allocator);
}

//------------------------------------------------------------------------------
IAllocator& IAllocator::OperatorNewDelete()
{
    class OperatorNewDeleteAllocator : public IAllocator {
    public:
        AE_BASE_OVERRIDE(ptr_t Alloc(pword_t size, pword_t alignment))
        {
            AE_BASE_UNUSED(alignment);
            void* ptr = ::operator new(size, std::nothrow_t());
            AE_BASE_ASSERT_EQUALS(pword_t(ptr) % alignment, 0);
            return static_cast<ptr_t>(ptr);
        }
        AE_BASE_OVERRIDE(void Free(ptr_t ptr))
        {
            ::operator delete(ptr, std::nothrow_t());
        }
    };
    static OperatorNewDeleteAllocator obj;
    return obj;
}

} // namespace ae::base

//------------------------------------------------------------------------------
void* operator new(const std::size_t size, ::ae::base::IAllocator& allocator)
{
    return allocator.Alloc(size);
}

//------------------------------------------------------------------------------
void* operator new[](
    const std::size_t size,
    ::ae::base::IAllocator& allocator)
{
    return allocator.Alloc(size);
}

//------------------------------------------------------------------------------
void operator delete(void* ptr, ::ae::base::IAllocator& allocator)
{
    allocator.Free(::ae::base::ptr_t(ptr));
}

//------------------------------------------------------------------------------
void operator delete[](void* ptr, ::ae::base::IAllocator& allocator)
{
    allocator.Free(::ae::base::ptr_t(ptr));
}

// EOF
