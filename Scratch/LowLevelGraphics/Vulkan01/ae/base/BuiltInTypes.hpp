// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_BUILTINTYPES_HPP)
#else
#define AE_BASE_INCLUDED_BUILTINTYPES_HPP

#include <cstddef>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Types
//@{
//=================================================
/// @name 符号無し整数型
//@{
typedef unsigned char           u8;     ///< 8bit符号無し整数型。
typedef unsigned char           uint8;  ///< 8bit符号無し整数型。
typedef unsigned short int      u16;    ///< 16bit符号無し整数型。
typedef unsigned short int      uint16; ///< 16bit符号無し整数型。
typedef unsigned int            u32;    ///< 32bit符号無し整数型。
typedef unsigned int            uint;   ///< 32bit符号無し整数型。
typedef unsigned int            uint32; ///< 32bit符号無し整数型。
typedef unsigned long long int  u64;    ///< 64bit符号無し整数型。
typedef unsigned long long int  uint64; ///< 64bit符号無し整数型。
//@}

//=================================================
/// @name 符号有り整数型
//@{
typedef signed char           int8;   ///< 8bit符号有り整数型。
typedef signed char           s8;     ///< 8bit符号有り整数型。
typedef signed char           sint8;  ///< 8bit符号有り整数型。
typedef signed short int      int16;  ///< 16bit符号有り整数型。
typedef signed short int      s16;    ///< 16bit符号有り整数型。
typedef signed short int      sint16; ///< 16bit符号有り整数型。
typedef signed int            int32;  ///< 32bit符号有り整数型。
typedef signed int            s32;    ///< 32bit符号有り整数型。
typedef signed int            sint;   ///< 32bit符号有り整数型。
typedef signed int            sint32; ///< 32bit符号有り整数型。
typedef signed long long int  int64;  ///< 64bit符号有り整数型。
typedef signed long long int  s64;    ///< 64bit符号有り整数型。
typedef signed long long int  sint64; ///< 64bit符号有り整数型。
//@}

//=================================================
/// @name 浮動小数型
//@{
typedef float  f32;     ///< 32bit浮動小数型。
typedef float  float32; ///< 32bit浮動小数型。
typedef float  single;  ///< 32bit浮動小数型。
typedef double f64;     ///< 64bit浮動小数型。
typedef double float64; ///< 64bit浮動小数型。
//@}

//============================================================
/// @name データ型
//@{
typedef u8          byte_t;  ///< 1バイトデータ型。
typedef u16         word_t;  ///< 2バイトデータ型。
typedef u32         dword_t; ///< 4バイトデータ型。
typedef u64         qword_t; ///< 8バイトデータ型。    
typedef std::size_t pword_t; ///< アドレスサイズを表すデータ型。
//@}

//============================================================
/// @name アドレス型 
//@{
typedef u8*         ptr_t;          ///< ポインタ型。void** -> void*に変換できてしまう事故を防ぐため基本はこちらを使用。
typedef const u8*   const_ptr_t;    ///< ptr_tのconst版。
typedef void*       anyptr_t;       ///< 何でもいけるポインタ型。
typedef const void* const_anyptr_t; ///< any_ptr_tのconst版。
//@}    
//@}

}} // namespace
#endif
// EOF
