// 文字コード：UTF-8
#if defined(AE_XS_DATA_INCLUDED_TYPES_HPP)
#else
#define AE_XS_DATA_INCLUDED_TYPES_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ScalerClass.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {
    
/// @addtogroup AeBase-Types
//@{
//=================================================
/// @name 必ず初期化される符号無し型
//@{
typedef ScalerClass< u8 >   U8;     ///< 8bit符号有り整数型。
typedef ScalerClass< u8 >   UInt8;  ///< 8bit符号有り整数型。
typedef ScalerClass< u16 >  U16;    ///< 16bit符号有り整数型。
typedef ScalerClass< u16 >  UInt16; ///< 16bit符号有り整数型。
typedef ScalerClass< u32 >  U32;    ///< 32bit符号有り整数型。
typedef ScalerClass< u32 >  UInt;   ///< 32bit符号有り整数型。
typedef ScalerClass< u32 >  UInt32; ///< 32bit符号有り整数型。
typedef ScalerClass< u64 >  U64;    ///< 64bit符号有り整数型。
typedef ScalerClass< u64 >  UInt64; ///< 64bit符号有り整数型。
//@}

//=================================================
/// @name 必ず初期化される符号有り型
//@{
typedef ScalerClass< s8 >   Int8;   ///< 8bit符号有り整数型。
typedef ScalerClass< s8 >   S8;     ///< 8bit符号有り整数型。
typedef ScalerClass< s8 >   SInt8;  ///< 8bit符号有り整数型。
typedef ScalerClass< s16 >  Int16;  ///< 16bit符号有り整数型。
typedef ScalerClass< s16 >  S16;    ///< 16bit符号有り整数型。
typedef ScalerClass< s16 >  SInt16; ///< 16bit符号有り整数型。
typedef ScalerClass< s32 >  Int32;  ///< 32bit符号有り整数型。
typedef ScalerClass< s32 >  S32;    ///< 32bit符号有り整数型。
typedef ScalerClass< s32 >  SInt;   ///< 32bit符号有り整数型。
typedef ScalerClass< s32 >  SInt32; ///< 32bit符号有り整数型。
typedef ScalerClass< s64 >  Int64;  ///< 64bit符号有り整数型。
typedef ScalerClass< s64 >  S64;    ///< 64bit符号有り整数型。
typedef ScalerClass< s64 >  SInt64; ///< 64bit符号有り整数型。
//@}

//=================================================
/// @name 必ず初期化される浮動小数型
//@{
typedef ScalerClass< f32 > F32;     ///< 32bit浮動小数型。
typedef ScalerClass< f32 > Float32; ///< 32bit浮動小数型。
typedef ScalerClass< f32 > Single;  ///< 32bit浮動小数型。
typedef ScalerClass< f64 > F64;     ///< 64bit浮動小数型。
typedef ScalerClass< f64 > Float64; ///< 64bit浮動小数型。
//@}

//============================================================
/// @name 必ず初期化されるデータ型
//@{
typedef ScalerClass<  byte_t > Byte;  ///< 1バイトデータ型。
typedef ScalerClass<  word_t > Word;  ///< 2バイトデータ型。
typedef ScalerClass< dword_t > DWord; ///< 4バイトデータ型。
typedef ScalerClass< qword_t > QWord; ///< 8バイトデータ型。
typedef ScalerClass< pword_t > PWord; ///< アドレスサイズを表すデータ型。
typedef ScalerClass<  size_t>  Size;  ///< アドレスサイズを表すデータ型。
//@}

//============================================================
/// @name 必ず初期化されるアドレス型
//@{
typedef ScalerClass< ptr_t >          Ptr;         ///< ポインタ型。void** -> void*に変換できてしまう事故を防ぐため基本はこちらを使用。
typedef ScalerClass< const_ptr_t >    ConstPtr;    ///< ptr_tのconst版。
typedef ScalerClass< anyptr_t >       AnyPtr;      ///< 何でもいけるポインタ型。
typedef ScalerClass< const_anyptr_t > ConstAnyPtr; ///< any_ptr_tのconst版。
//@}
//@}

}} // namespace
#endif
// EOF
