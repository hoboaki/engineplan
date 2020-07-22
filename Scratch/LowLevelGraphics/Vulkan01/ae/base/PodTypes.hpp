// 文字コード：UTF-8
#if defined(AE_XS_DATA_INCLUDED_PodTYPES_HPP)
#else
#define AE_XS_DATA_INCLUDED_PodTYPES_HPP

#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/ScalerClass.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Types
//@{
//=================================================
/// @name struct化された符号無し型
//@{
typedef PodStruct< u8 >   U8Pod;     ///< 8bit符号有り整数型。
typedef PodStruct< u8 >   UInt8Pod;  ///< 8bit符号有り整数型。
typedef PodStruct< u16 >  U16Pod;    ///< 16bit符号有り整数型。
typedef PodStruct< u16 >  UInt16Pod; ///< 16bit符号有り整数型。
typedef PodStruct< u32 >  U32Pod;    ///< 32bit符号有り整数型。
typedef PodStruct< u32 >  UIntPod;   ///< 32bit符号有り整数型。
typedef PodStruct< u32 >  UInt32Pod; ///< 32bit符号有り整数型。
typedef PodStruct< u64 >  U64Pod;    ///< 64bit符号有り整数型。
typedef PodStruct< u64 >  UInt64Pod; ///< 64bit符号有り整数型。
//@}

//=================================================
/// @name struct化された符号有り型
//@{
typedef PodStruct< s8 >   Int8Pod;   ///< 8bit符号有り整数型。
typedef PodStruct< s8 >   S8Pod;     ///< 8bit符号有り整数型。
typedef PodStruct< s8 >   SInt8Pod;  ///< 8bit符号有り整数型。
typedef PodStruct< s16 >  Int16Pod;  ///< 16bit符号有り整数型。
typedef PodStruct< s16 >  S16Pod;    ///< 16bit符号有り整数型。
typedef PodStruct< s16 >  SInt16Pod; ///< 16bit符号有り整数型。
typedef PodStruct< s32 >  Int32Pod;  ///< 32bit符号有り整数型。
typedef PodStruct< s32 >  S32Pod;    ///< 32bit符号有り整数型。
typedef PodStruct< s32 >  SIntPod;   ///< 32bit符号有り整数型。
typedef PodStruct< s32 >  SInt32Pod; ///< 32bit符号有り整数型。
typedef PodStruct< s64 >  Int64Pod;  ///< 64bit符号有り整数型。
typedef PodStruct< s64 >  S64Pod;    ///< 64bit符号有り整数型。
typedef PodStruct< s64 >  SInt64Pod; ///< 64bit符号有り整数型。
//@}

//=================================================
/// @name struct化された浮動小数型
//@{
typedef PodStruct< f32 > F32Pod;     ///< 32bit浮動小数型。
typedef PodStruct< f32 > Float32Pod; ///< 32bit浮動小数型。
typedef PodStruct< f32 > SinglePod;  ///< 32bit浮動小数型。
typedef PodStruct< f64 > F64Pod;     ///< 64bit浮動小数型。
typedef PodStruct< f64 > Float64Pod; ///< 64bit浮動小数型。
//@}

//============================================================
/// @name struct化されたデータ型
//@{
typedef PodStruct<  byte_t > BytePod;  ///< 1バイトデータ型。
typedef PodStruct<  word_t > WordPod;  ///< 2バイトデータ型。
typedef PodStruct< dword_t > DWordPod; ///< 4バイトデータ型。
typedef PodStruct< qword_t > QWordPod; ///< 8バイトデータ型。
typedef PodStruct< pword_t > PWordPod; ///< アドレスサイズを表すデータ型。
typedef PodStruct<  size_t>  SizePod;  ///< アドレスサイズを表すデータ型。
//@}

//============================================================
/// @name struct化されたアドレス型
//@{
typedef PodStruct< ptr_t >          PtrPod;         ///< ポインタ型。void** -> void*に変換できてしまう事故を防ぐため基本はこちらを使用。
typedef PodStruct< const_ptr_t >    ConstPtrPod;    ///< ptr_tのconst版。
typedef PodStruct< anyptr_t >       AnyPtrPod;      ///< 何でもいけるポインタ型。
typedef PodStruct< const_anyptr_t > ConstAnyPtrPod; ///< any_ptr_tのconst版。
//@}

//@}

}} // namespace
#endif
// EOF
