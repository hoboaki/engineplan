// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_AE_BASE_HPP)
#else
#define AE_BASE_INCLUDED_AE_BASE_HPP

/// @namespace AeBase AeLibraryの基本となるクラス・関数・マクロ群を定義する名前空間。

/// @defgroup AeBase-Collection AeBase:コレクション
#include <ae/base/BitSet.hpp>
#include <ae/base/RuntimeArray.hpp>
#include <ae/base/RuntimeAutoArray.hpp>
#include <ae/base/RuntimeMArray.hpp>

/// @defgroup AeBase-Env AeBase:環境情報
#include <ae/base/Compiler.hpp>
#include <ae/base/Config.hpp>
#include <ae/base/Endian.hpp>
#include <ae/base/Os.hpp>

/// @defgroup AeBase-DateTime AeBase:日時
#include <ae/base/Calendar.hpp>
#include <ae/base/Time.hpp>
#include <ae/base/TimeSpan.hpp>

/// @defgroup AeBase-Debug AeBase:デバッグ・エラー処理
#include <ae/base/Console.hpp>
#include <ae/base/DivideCheck.hpp>
#include <ae/base/EnumCheck.hpp>
#include <ae/base/FunctionAttribute.hpp>
#include <ae/base/PointerCheck.hpp>
#include <ae/base/RuntimeAssert.hpp>
#include <ae/base/RuntimeError.hpp>
#include <ae/base/StaticAssert.hpp>

/// @defgroup AeBase-IO AeBase:ファイル操作
#include <ae/base/IReadStream.hpp>
#include <ae/base/ResFile.hpp>
#include <ae/base/ResFileStream.hpp>
#include <ae/base/SeekOrigin.hpp>

/// @defgroup AeBase-Hid AeBase:Hid
#include <ae/base/KeyBitSet.hpp>
#include <ae/base/Keyboard.hpp>
#include <ae/base/KeyKind.hpp>
#include <ae/base/Hid.hpp>
#include <ae/base/Mouse.hpp>
#include <ae/base/MouseBtnBitSet.hpp>
#include <ae/base/MouseBtnKind.hpp>
#include <ae/base/Touch.hpp>
#include <ae/base/TouchTap.hpp>

/// @defgroup AeBase-Math AeBase:数学
#include <ae/base/Aabb2.hpp>
#include <ae/base/Aabb2i.hpp>
#include <ae/base/Angle.hpp>
#include <ae/base/Degree.hpp>
#include <ae/base/Infinity.hpp>
#include <ae/base/Math.hpp>
#include <ae/base/Matrix34.hpp>
#include <ae/base/Matrix44.hpp>
#include <ae/base/Pi.hpp>
#include <ae/base/Quaternion.hpp>
#include <ae/base/Radian.hpp>
#include <ae/base/Random.hpp>
#include <ae/base/Vector2.hpp>
#include <ae/base/Vector2i.hpp>
#include <ae/base/Vector3.hpp>
#include <ae/base/Vector3i.hpp>
#include <ae/base/Vector4.hpp>
#include <ae/base/Vector4i.hpp>

/// @defgroup AeBase-Memory AeBase:メモリ
#include <ae/base/AutoMemBlock.hpp>
#include <ae/base/AutoPtr.hpp>
#include <ae/base/AutoSpPtr.hpp>
#include <ae/base/IAllocator.hpp>
#include <ae/base/MemBlock.hpp>
#include <ae/base/ScopedPtr.hpp>

/// @defgroup AeBase-String AeBase:文字列
#include <ae/base/FixedString.hpp>
#include <ae/base/ShortString.hpp>
#include <ae/base/StringTraits.hpp>
#include <ae/base/ToShortString.hpp>

/// @defgroup AeBase-System AeBase:システム
#include <ae/base/Application.hpp>
#include <ae/base/Argument.hpp>
#include <ae/base/Display.hpp>
#include <ae/base/DisplayContext.hpp>
#include <ae/base/EntryPoint.hpp>
#include <ae/base/Screen.hpp>

/// @defgroup AeBase-Thread AeBase:スレッド
#include <ae/base/Thread.hpp>

/// @defgroup AeBase-Util AeBase:ユーティリティ
#include <ae/base/ArrayLength.hpp>
#include <ae/base/Color4.hpp>
#include <ae/base/Color4b.hpp>
#include <ae/base/ExplicitSingleton.hpp>
#include <ae/base/FrameCounter.hpp>
#include <ae/base/Hash.hpp>
#include <ae/base/Ref.hpp>
#include <ae/base/Reference.hpp>
#include <ae/base/Placement.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/ScreenPos.hpp>
#include <ae/base/Unused.hpp>
#include <ae/base/ValueInRange.hpp>

/// @defgroup AeBase-Types AeBase:型
#include <ae/base/Bool.hpp>
#include <ae/base/BuiltInTypes.hpp>
#include <ae/base/Enum.hpp>
#include <ae/base/PodClass.hpp>
#include <ae/base/PodTypes.hpp>
#include <ae/base/ScalerClass.hpp>

#endif
// EOF
