// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_EXPLICITSINGLETON_HPP)
#else
#define AE_BASE_INCLUDED_EXPLICITSINGLETON_HPP

#include <ae/base/NonCopyable.hpp>
#include <ae/base/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @name addtogroup AeBase-Util
//@{
    /// @brief 明示的に生成・解放できるシングルトン。
    /// @details 
    /// 継承して使用します。@n
    /// 継承先のコンストラクタで SetInstance() を呼びデストラクタで UnsetInstance() を呼ぶようにしてください。 @n
    /// ２つ以上インスタンス化させるとエラーになります。 @n
    ///      *
    /// @code
    /// // 例
    /// class Manager : public ::ae::base::ExplicitSingleton< Manager >
    /// {
    /// public:
    ///     Manager()
    ///     {
    ///         SetInstance( *this );
    ///     }
    ///     ~Manager()
    ///     {
    ///         UnsetInstance();
    ///     }
    ///     int value()const { return 1; }
    /// };
    /// void func()
    /// {
    ///     // Managerが作成済みならこのようにアクセスできる
    ///     return Manager::Instance().value();
    /// }
    /// @endcode
template< typename T >
class ExplicitSingleton : public NonCopyable
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    ExplicitSingleton()
    {
        AE_BASE_ASSERT(!IsCreated());
    }
    ~ExplicitSingleton()
    {
        AE_BASE_ASSERT(!IsCreated());
    }
    //@}

    /// @name アクセス
    //@{
    static inline T& Instance(); ///< 作成済みのインスタンスにアクセス。 @details もし作成していない状態でこの関数を呼ぶとエラーになります。
    static inline bool IsCreated(); ///< 作成済みならtrueを返す。
    //@}

protected:
    /// インスタンス化が終わったときに呼ぶ。
    inline void SetInstance(T&);

    /// インスタンス化を解除したいときに呼ぶ。
    inline void UnsetInstance();

private:
    static T* sPtr;
};
//@}

template< typename T >
T& ExplicitSingleton<T>::Instance()
{
    AE_BASE_ASSERT(IsCreated());
    return *sPtr;
}

template< typename T >
bool ExplicitSingleton<T>::IsCreated()
{
    return sPtr != 0;
}

template< typename T >
void ExplicitSingleton<T>::SetInstance(T& aRef)
{
    AE_BASE_ASSERT(!IsCreated());
    sPtr = &aRef;
}

template< typename T >
void ExplicitSingleton<T>::UnsetInstance()
{
    AE_BASE_ASSERT(IsCreated());
    sPtr = 0;
}

template< typename T >
T* ExplicitSingleton<T>::sPtr = 0;

}} // namespace
#endif
// EOF
