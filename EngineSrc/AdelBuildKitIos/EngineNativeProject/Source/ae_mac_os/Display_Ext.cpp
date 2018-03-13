// 文字コード：UTF-8
#include <ae/base/Display.hpp>

#include <ae/base/Application.hpp>
#include <ae/base/Ref.hpp>
#include "AeBaseNSWindow.h"
#include <OpenGL/OpenGL.h>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
namespace {

const int tNormalKeyCode[256] =
{
    -1,                 // 0
    -1,                 // 1
    -1,                 // 2
    -1,                 // 3
    -1,                 // 4
    -1,                 // 5
    -1,                 // 6
    -1,                 // 7
    -1,                 // 8
    KeyKind::Tab,       // 9
    -1,                 // 10
    -1,                 // 11
    -1,                 // 12
    KeyKind::Return,    // 13
    -1,                 // 14
    -1,                 // 15
    -1,                 // 16
    -1,                 // 17
    -1,                 // 18
    -1,                 // 19
    -1,                 // 20
    -1,                 // 21
    -1,                 // 22
    -1,                 // 23
    -1,                 // 24
    -1,                 // 25
    -1,                 // 26
    KeyKind::Escape,    // 27
    -1,                 // 28
    -1,                 // 29
    -1,                 // 30
    -1,                 // 31
    KeyKind::Space,     // 32
    -1,                 // 33
    -1,                 // 34
    -1,                 // 35
    -1,                 // 36
    -1,                 // 37
    -1,                 // 38
    -1,//KeyKind::SINGLEQUOTE, // 39
    -1,                 // 40
    -1,                 // 41
    -1,                 // 42
    -1,//KeyKind::PLUS,        // 43
    -1,//KeyKind::COMMA,       // 44
    -1,//KeyKind::MINUS,       // 45
    -1,//KeyKind::DOT,         // 46
    -1,//KeyKind::SLASH,       // 47
    KeyKind::Num0,           // 48
    KeyKind::Num1,           // 49
    KeyKind::Num2,           // 50
    KeyKind::Num3,           // 51
    KeyKind::Num4,           // 52
    KeyKind::Num5,           // 53
    KeyKind::Num6,           // 54
    KeyKind::Num7,           // 55
    KeyKind::Num8,           // 56
    KeyKind::Num9,           // 57
    -1,//KeyKind::SEMICOLON,   // 58
    -1,                 // 59
    -1,                 // 60
    -1,                 // 61
    -1,                 // 62
    -1,                 // 63
    -1,                 // 64
    KeyKind::A,           // 65
    KeyKind::B,           // 66
    KeyKind::C,           // 67
    KeyKind::D,           // 68
    KeyKind::E,           // 69
    KeyKind::F,           // 70
    KeyKind::G,           // 71
    KeyKind::H,           // 72
    KeyKind::I,           // 73
    KeyKind::J,           // 74
    KeyKind::K,           // 75
    KeyKind::L,           // 76
    KeyKind::M,           // 77
    KeyKind::N,           // 78
    KeyKind::O,           // 79
    KeyKind::P,           // 80
    KeyKind::Q,           // 81
    KeyKind::R,           // 82
    KeyKind::S,           // 83
    KeyKind::T,           // 84
    KeyKind::U,           // 85
    KeyKind::V,           // 86
    KeyKind::W,           // 87
    KeyKind::X,           // 88
    KeyKind::Y,           // 89
    KeyKind::Z,           // 90
    -1,//KeyKind::LBRACKET,    // 91
    -1,//KeyKind::BACKSLASH,   // 92
    -1,//KeyKind::RBRACKET,    // 93
    -1,                 // 94
    -1,                 // 95
    -1,                 // 96
    KeyKind::A,           // 97
    KeyKind::B,           // 98
    KeyKind::C,           // 99
    KeyKind::D,           // 100
    KeyKind::E,           // 101
    KeyKind::F,           // 102
    KeyKind::G,           // 103
    KeyKind::H,           // 104
    KeyKind::I,           // 105
    KeyKind::J,           // 106
    KeyKind::K,           // 107
    KeyKind::L,           // 108
    KeyKind::M,           // 109
    KeyKind::N,           // 110
    KeyKind::O,           // 111
    KeyKind::P,           // 112
    KeyKind::Q,           // 113
    KeyKind::R,           // 114
    KeyKind::S,           // 115
    KeyKind::T,           // 116
    KeyKind::U,           // 117
    KeyKind::V,           // 118
    KeyKind::W,           // 119
    KeyKind::X,           // 120
    KeyKind::Y,           // 121
    KeyKind::Z,           // 122
    -1,//KeyKind::LBRACKET,    // 123
    -1,                 // 124
    -1,//KeyKind::RBRACKET,    // 125
    -1,//KeyKind::TILDA,       // 126
    KeyKind::BackSpace,          // 127
    -1,                 // 128
    -1,                 // 129
    -1,                 // 130
    -1,                 // 131
    -1,                 // 132
    -1,                 // 133
    -1,                 // 134
    -1,                 // 135
    -1,                 // 136
    -1,                 // 137
    -1,                 // 138
    -1,                 // 139
    -1,                 // 140
    -1,                 // 141
    -1,                 // 142
    -1,                 // 143
    -1,                 // 144
    -1,                 // 145
    -1,                 // 146
    -1,                 // 147
    -1,                 // 148
    -1,                 // 149
    -1,                 // 150
    -1,                 // 151
    -1,                 // 152
    -1,                 // 153
    -1,                 // 154
    -1,                 // 155
    -1,                 // 156
    -1,                 // 157
    -1,                 // 158
    -1,                 // 159
    -1,                 // 160
    -1,                 // 161
    -1,                 // 162
    -1,                 // 163
    -1,                 // 164
    -1,                 // 165
    -1,                 // 166
    -1,                 // 167
    -1,                 // 168
    -1,                 // 169
    -1,                 // 170
    -1,                 // 171
    -1,                 // 172
    -1,                 // 173
    -1,                 // 174
    -1,                 // 175
    -1,                 // 176
    -1,                 // 177
    -1,                 // 178
    -1,                 // 179
    -1,                 // 180
    -1,                 // 181
    -1,                 // 182
    -1,                 // 183
    -1,                 // 184
    -1,                 // 185
    -1,                 // 186
    -1,                 // 187
    -1,                 // 188
    -1,                 // 189
    -1,                 // 190
    -1,                 // 191
    -1,                 // 192
    -1,                 // 193
    -1,                 // 194
    -1,                 // 195
    -1,                 // 196
    -1,                 // 197
    -1,                 // 198
    -1,                 // 199
    -1,                 // 200
    -1,                 // 201
    -1,                 // 202
    -1,                 // 203
    -1,                 // 204
    -1,                 // 205
    -1,                 // 206
    -1,                 // 207
    -1,                 // 208
    -1,                 // 209
    -1,                 // 210
    -1,                 // 211
    -1,                 // 212
    -1,                 // 213
    -1,                 // 214
    -1,                 // 215
    -1,                 // 216
    -1,                 // 217
    -1,                 // 218
    -1,                 // 219
    -1,                 // 220
    -1,                 // 221
    -1,                 // 222
    -1,                 // 223
    -1,                 // 224
    -1,                 // 225
    -1,                 // 226
    -1,                 // 227
    -1,                 // 228
    -1,                 // 229
    -1,                 // 230
    -1,                 // 231
    -1,                 // 232
    -1,                 // 233
    -1,                 // 234
    -1,                 // 235
    -1,                 // 236
    -1,                 // 237
    -1,                 // 238
    -1,                 // 239
    -1,                 // 240
    -1,                 // 241
    -1,                 // 242
    -1,                 // 243
    -1,                 // 244
    -1,                 // 245
    -1,                 // 246
    -1,                 // 247
    -1,                 // 248
    -1,                 // 249
    -1,                 // 250
    -1,                 // 251
    -1,                 // 252
    -1,                 // 253
    -1,                 // 254
    0                  // 255
};

const int tSpecialKeyCode[256] =
{
    KeyKind::Up,           // 0
    KeyKind::Down,         // 1
    KeyKind::Left,         // 2
    KeyKind::Right,        // 3
    KeyKind::F1,           // 4
    KeyKind::F2,           // 5
    KeyKind::F3,           // 6
    KeyKind::F4,           // 7
    KeyKind::F5,           // 8
    KeyKind::F6,           // 9
    KeyKind::F7,           // 10
    KeyKind::F8,           // 11
    KeyKind::F9,           // 12
    KeyKind::F10,          // 13
    KeyKind::F11,          // 14
    KeyKind::F12,          // 15
    KeyKind::F1,           // 16 0x10
    KeyKind::F2,           // 17
    KeyKind::F3,           // 18
    KeyKind::F4,           // 19
    KeyKind::F5,           // 20
    KeyKind::F6,           // 21
    KeyKind::F7,           // 22
    KeyKind::F8,           // 23
    KeyKind::F9,           // 24
    KeyKind::F10,          // 25
    KeyKind::F11,          // 26
    KeyKind::F12,          // 27
    KeyKind::F1,           // 28
    KeyKind::F2,           // 29
    KeyKind::F3,           // 30
    KeyKind::F4,           // 31
    KeyKind::F5,           // 32 0x20
    KeyKind::F6,           // 33
    KeyKind::F7,           // 34
    KeyKind::F8,           // 35
    KeyKind::F9,           // 36
    KeyKind::F10,          // 37
    KeyKind::F11,          // 38
    KeyKind::Insert,          // 39
    KeyKind::Delete,          // 40
    KeyKind::Home,         // 41
    -1,                  // 42 Begin
    KeyKind::End,          // 43
    KeyKind::PageUp,       // 44
    KeyKind::PageDown,     // 45
    -1,//KeyKind::PrintScreen,    // 46
    KeyKind::ScrolLock,   // 47
    -1,//KeyKind::PauseBreak,   // 48 0x30
    -1,                  // 49
    -1,//KeyKind::PauseBreak,   // 50
    -1,                  // 51 Reset
    -1,                  // 52 Stop
    -1,                  // 53 Menu
    -1,                  // 54 User
    -1,                  // 55 System
    -1,//KeyKind::PRINTSCRN,    // 56
    -1,                  // 57 Clear line
    -1,                  // 58 Clear display
    -1,                  // 59 Insert line
    -1,                  // 60 Delete line
    KeyKind::Insert,          // 61
    KeyKind::Delete,          // 62
    KeyKind::PageUp,       // 63
    KeyKind::PageDown,     // 64
    -1,                  // 65 Select
    -1,                  // 66 Execute
    -1,                  // 67 Undo
    -1,                  // 68 Redo
    -1,                  // 69 Find
    -1,                  // 70 Help
    -1,                  // 71 Mode Switch
    -1,                  // 72
    -1,                  // 73
    -1,                  // 74
    -1,                  // 75
    -1,                  // 76
    -1,                  // 77
    -1,                  // 78
    -1,                  // 79
    -1,                  // 80
    -1,                  // 81
    -1,                  // 82
    -1,                  // 83
    -1,                  // 84
    -1,                  // 85
    -1,                  // 86
    -1,                  // 87
    -1,                  // 88
    -1,                  // 89
    -1,                  // 90
    -1,                  // 91
    -1,                  // 92
    -1,                  // 93
    -1,                  // 94
    -1,                  // 95
    -1,                  // 96
    -1,                  // 97
    -1,                  // 98
    -1,                  // 99
    -1,                  // 100
    -1,                  // 101
    -1,                  // 102
    -1,                  // 103
    -1,                  // 104
    -1,                  // 105
    -1,                  // 106
    -1,                  // 107
    -1,                  // 108
    -1,                  // 109
    -1,                  // 110
    -1,                  // 111
    -1,                  // 112
    -1,                  // 113
    -1,                  // 114
    -1,                  // 115
    -1,                  // 116
    -1,                  // 117
    -1,                  // 118
    -1,                  // 119
    -1,                  // 120
    -1,                  // 121
    -1,                  // 122
    -1,                  // 123
    -1,                  // 124
    -1,                  // 125
    -1,                  // 126
    -1,                  // 127
    -1,                  // 128
    -1,                  // 129
    -1,                  // 130
    -1,                  // 131
    -1,                  // 132
    -1,                  // 133
    -1,                  // 134
    -1,                  // 135
    -1,                  // 136
    -1,                  // 137
    -1,                  // 138
    -1,                  // 139
    -1,                  // 140
    -1,                  // 141
    -1,                  // 142
    -1,                  // 143
    -1,                  // 144
    -1,                  // 145
    -1,                  // 146
    -1,                  // 147
    -1,                  // 148
    -1,                  // 149
    -1,                  // 150
    -1,                  // 151
    -1,                  // 152
    -1,                  // 153
    -1,                  // 154
    -1,                  // 155
    -1,                  // 156
    -1,                  // 157
    -1,                  // 158
    -1,                  // 159
    -1,                  // 160
    -1,                  // 161
    -1,                  // 162
    -1,                  // 163
    -1,                  // 164
    -1,                  // 165
    -1,                  // 166
    -1,                  // 167
    -1,                  // 168
    -1,                  // 169
    -1,                  // 170
    -1,                  // 171
    -1,                  // 172
    -1,                  // 173
    -1,                  // 174
    -1,                  // 175
    -1,                  // 176
    -1,                  // 177
    -1,                  // 178
    -1,                  // 179
    -1,                  // 180
    -1,                  // 181
    -1,                  // 182
    -1,                  // 183
    -1,                  // 184
    -1,                  // 185
    -1,                  // 186
    -1,                  // 187
    -1,                  // 188
    -1,                  // 189
    -1,                  // 190
    -1,                  // 191
    -1,                  // 192
    -1,                  // 193
    -1,                  // 194
    -1,                  // 195
    -1,                  // 196
    -1,                  // 197
    -1,                  // 198
    -1,                  // 199
    -1,                  // 200
    -1,                  // 201
    -1,                  // 202
    -1,                  // 203
    -1,                  // 204
    -1,                  // 205
    -1,                  // 206
    -1,                  // 207
    -1,                  // 208
    -1,                  // 209
    -1,                  // 210
    -1,                  // 211
    -1,                  // 212
    -1,                  // 213
    -1,                  // 214
    -1,                  // 215
    -1,                  // 216
    -1,                  // 217
    -1,                  // 218
    -1,                  // 219
    -1,                  // 220
    -1,                  // 221
    -1,                  // 222
    -1,                  // 223
    -1,                  // 224
    -1,                  // 225
    -1,                  // 226
    -1,                  // 227
    -1,                  // 228
    -1,                  // 229
    -1,                  // 230
    -1,                  // 231
    -1,                  // 232
    -1,                  // 233
    -1,                  // 234
    -1,                  // 235
    -1,                  // 236
    -1,                  // 237
    -1,                  // 238
    -1,                  // 239
    -1,                  // 240
    -1,                  // 241
    -1,                  // 242
    -1,                  // 243
    -1,                  // 244
    -1,                  // 245
    -1,                  // 246
    -1,                  // 247
    -1,                  // 248
    -1,                  // 249
    -1,                  // 250
    -1,                  // 251
    -1,                  // 252
    -1,                  // 253
    -1,                  // 254
    -1                   // 255
};

void tUpdateModKey(KeyboardUpdateData& aData, KeyKind::EnumType aKey, int aIsDown)
{
    // 同じなら何もしない
    const bool isDown = aIsDown != 0;
    if (aData.hold.get(aKey) == isDown) {
        return;
    }

    // 変更
    aData.hold.set(aKey, isDown);
    if (isDown) {
        aData.pulse.set(aKey, true);
    }
}

} // namespace

//------------------------------------------------------------------------------
int Display::screenCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
Screen& Display::screenAtIndex(const int aIndex)
{
    AE_BASE_ASSERT_LESS(aIndex, screenCount());
    return mainScreen();
}

//------------------------------------------------------------------------------
Screen& Display::mainScreen()
{
    return *mExt.mainScreen;
}

//------------------------------------------------------------------------------
void Display::show()
{
    mExt.isClosed = 0;
    AeBaseNSWindow_Show(mExt.windowPtr);
}

//------------------------------------------------------------------------------
bool Display::isClosed()const
{
    return mExt.isClosed != 0;
}

//------------------------------------------------------------------------------
void Display_Ext::CBKeyEvent(void* aOwnerPtr, const int aUnicode, const int aIsDown)
{
    // キー選択
    int keyKind = -1;
    if (0 <= aUnicode && aUnicode <= 0xFF) {
        keyKind = tNormalKeyCode[aUnicode];
    }
    else if (0xF700 <= aUnicode &&  aUnicode <= 0xF7FF) {
        keyKind = tSpecialKeyCode[aUnicode - 0xF700];
    }

    // 有効なキーなら保存
    if (0 <= keyKind) {
        Display_Ext* owner = static_cast<Display_Ext*>(aOwnerPtr);
        owner->keyboardUpdateData.hold.set(uint(keyKind), aIsDown != 0);
        if (aIsDown) {
            owner->keyboardUpdateData.pulse.set(uint(keyKind), true);
        }
    }
}

//------------------------------------------------------------------------------
void Display_Ext::CBModKeyEvent(void* aOwnerPtr, const int aIsShift, const int aIsCtrl, const int aIsAlt)
{
    Display_Ext* owner = static_cast<Display_Ext*>(aOwnerPtr);
    tUpdateModKey(owner->keyboardUpdateData, KeyKind::Shift, aIsShift);
    tUpdateModKey(owner->keyboardUpdateData, KeyKind::Ctrl, aIsCtrl);
    tUpdateModKey(owner->keyboardUpdateData, KeyKind::Alt, aIsAlt);
}

//------------------------------------------------------------------------------
void Display_Ext::CBMouseEvent(void* aOwnerPtr, const int aPressedButton, const float aX, const float aY)
{
    Display_Ext* owner = static_cast<Display_Ext*>(aOwnerPtr);
    owner->mouseUpdateData.pos.x = s16(aX);
    owner->mouseUpdateData.pos.y = s16(aY);
    owner->mouseUpdateData.posUpdated = true;
    owner->mouseUpdateData.hold.set(MouseBtnKind::L, aPressedButton & 0x01);
    owner->mouseUpdateData.hold.set(MouseBtnKind::R, aPressedButton & 0x02);
    owner->mouseUpdateData.hold.set(MouseBtnKind::M, aPressedButton & 0x04);
}

//------------------------------------------------------------------------------
Display_Ext::Display_Ext(const DisplayContext& aContext)
: windowPtr(0)
, mainScreen()
, hidPtr()
, isClosed(0)
, keyboardUpdateData()
, mouseUpdateData()
{
    // Window作成
    windowPtr = AeBaseNSWindow_Create(
        aContext.locationX(),
        aContext.locationY(),
        aContext.width(),
        aContext.height(),
        this,
        &isClosed,
        CBKeyEvent,
        CBModKeyEvent,
        CBMouseEvent
        );

// メインスクリーンの作成
    mainScreen.init(Ref(*this), aContext.width(), aContext.height());
}

//------------------------------------------------------------------------------
Display_Ext::~Display_Ext()
{
    // メインスクリーンの削除
    mainScreen.reset();

    // Window解放
    AeBaseNSWindow* ptr = windowPtr;
    windowPtr = 0;
    AeBaseNSWindow_Destroy(ptr);
}

}} // namespace
// EOF
