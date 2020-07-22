// 文字コード：UTF-8
#if defined(AE_BASE_INCLUDED_KEYKIND_HPP)
#else
#define AE_BASE_INCLUDED_KEYKIND_HPP

//------------------------------------------------------------------------------
namespace ae {
namespace base {

/// @addtogroup AeBase-Hid
//@{
/// キーボードのキーの種類。
struct KeyKind
{
    enum EnumType
    {
        BackSpace,
        Tab,
        Return,
        Pause,
        Escape,
        Space,
        Delete,

        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        // End of ASCII mapped keysyms

        // Arrows + Home/End pad
        Up,
        Down,
        Right,
        Left,
        Insert,
        Home,
        End,
        PageUp,
        PageDown,

        // Function keys
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,

        // Key state modifier keys
        NumLock,
        CapsLock,
        ScrolLock,
        Shift,
        Ctrl,
        Alt,

        // term
        TERM,
    };
};
//@}

}} // namespace
#endif
// EOF
