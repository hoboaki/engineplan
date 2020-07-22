// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_ARRAYLENGTH_HPP)
#else
#define AE_BASE_INCLUDED_ARRAYLENGTH_HPP

#include <ae/base/StaticAssert.hpp>

/// @addtogroup AeBase-Util
//@{
/// @name 配列長
//@{

/// @brief 配列の長さを取得するマクロ。
/// @return 配列長。
#define AE_BASE_ARRAY_LENGTH( obj ) ( sizeof(obj)/sizeof(obj[0]) )

/// 指定の配列の長さが指定の長さかチェックする。
#define AE_BASE_ARRAY_LENGTH_CHECK( arr , len ) AE_BASE_STATIC_ASSERT( AE_BASE_ARRAY_LENGTH( arr ) == len )

//@}
//@}
#endif
// EOF
