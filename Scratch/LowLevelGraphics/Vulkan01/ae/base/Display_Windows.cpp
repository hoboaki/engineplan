// 文字コード：UTF-8
#include <ae/base/Display.hpp>

#include <ae/base/Application.hpp>
#include <ae/base/KeyKind.hpp>
#include <ae/base/Hid.hpp>
#include <ae/base/Pointer.hpp>
#include <ae/base/Ref.hpp>
#include <ae/base/Unused.hpp>
#include <ae/base/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
namespace {

Pointer< Display_Ext > tCurrentDisplay;

KeyKind::EnumType tToKeyKind(WPARAM aKey)
{
    switch (aKey) {
        case VK_BACK:   return KeyKind::BackSpace;
        case VK_TAB:    return KeyKind::Tab;
        case VK_RETURN: return KeyKind::Return;
        case VK_PAUSE:  return KeyKind::Pause;
        case VK_ESCAPE: return KeyKind::Escape;
        case VK_SPACE:  return KeyKind::Space;
        case VK_DELETE: return KeyKind::Delete;

        case '0': return KeyKind::Num0;
        case '1': return KeyKind::Num1;
        case '2': return KeyKind::Num2;
        case '3': return KeyKind::Num3;
        case '4': return KeyKind::Num4;
        case '5': return KeyKind::Num5;
        case '6': return KeyKind::Num6;
        case '7': return KeyKind::Num7;
        case '8': return KeyKind::Num8;
        case '9': return KeyKind::Num9;
        case 'A': return KeyKind::A;
        case 'B': return KeyKind::B;
        case 'C': return KeyKind::C;
        case 'D': return KeyKind::D;
        case 'E': return KeyKind::E;
        case 'F': return KeyKind::F;
        case 'G': return KeyKind::G;
        case 'H': return KeyKind::H;
        case 'I': return KeyKind::I;
        case 'J': return KeyKind::J;
        case 'K': return KeyKind::K;
        case 'L': return KeyKind::L;
        case 'M': return KeyKind::M;
        case 'N': return KeyKind::N;
        case 'O': return KeyKind::O;
        case 'P': return KeyKind::P;
        case 'Q': return KeyKind::Q;
        case 'R': return KeyKind::R;
        case 'S': return KeyKind::S;
        case 'T': return KeyKind::T;
        case 'U': return KeyKind::U;
        case 'V': return KeyKind::V;
        case 'W': return KeyKind::W;
        case 'X': return KeyKind::X;
        case 'Y': return KeyKind::Y;
        case 'Z': return KeyKind::Z;

        #if 0
        case VK_NUMPAD0: return KeyKind::KP0;
        case VK_NUMPAD1: return KeyKind::KP1;
        case VK_NUMPAD2: return KeyKind::KP2;
        case VK_NUMPAD3: return KeyKind::KP3;
        case VK_NUMPAD4: return KeyKind::KP4;
        case VK_NUMPAD5: return KeyKind::KP5;
        case VK_NUMPAD6: return KeyKind::KP6;
        case VK_NUMPAD7: return KeyKind::KP7;
        case VK_NUMPAD8: return KeyKind::KP8;
        case VK_NUMPAD9: return KeyKind::KP9;
        case VK_DECIMAL: return KeyKind::KPPeriod;
        case VK_DIVIDE:   return KeyKind::KPDivide;
        case VK_MULTIPLY: return KeyKind::KPMultiply;
        case VK_SUBTRACT: return KeyKind::KPMinus;
        case VK_ADD: return KeyKind::KPPlus;
        //case : return KeyKind::KPEnter;
        //case : return KeyKind::KPEquals;
        #endif

        case VK_UP: return KeyKind::Up;
        case VK_DOWN: return KeyKind::Down;
        case VK_RIGHT: return KeyKind::Right;
        case VK_LEFT: return KeyKind::Left;
        case VK_INSERT: return KeyKind::Insert;
        case VK_HOME: return KeyKind::Home;
        case VK_END: return KeyKind::End;
        case VK_PRIOR: return KeyKind::PageUp;
        case VK_NEXT: return KeyKind::PageDown;

        case VK_F1: return KeyKind::F1;
        case VK_F2: return KeyKind::F2;
        case VK_F3: return KeyKind::F3;
        case VK_F4: return KeyKind::F4;
        case VK_F5: return KeyKind::F5;
        case VK_F6: return KeyKind::F6;
        case VK_F7: return KeyKind::F7;
        case VK_F8: return KeyKind::F8;
        case VK_F9: return KeyKind::F9;
        case VK_F10: return KeyKind::F10;
        case VK_F11: return KeyKind::F11;
        case VK_F12: return KeyKind::F12;
        case VK_F13: return KeyKind::F13;
        case VK_F14: return KeyKind::F14;
        case VK_F15: return KeyKind::F15;

        case VK_NUMLOCK: return KeyKind::NumLock;
        case VK_OEM_ATTN: return KeyKind::CapsLock;
        case VK_SCROLL: return KeyKind::ScrolLock;
        case VK_RSHIFT: return KeyKind::Shift;
        case VK_LSHIFT: return KeyKind::Shift;
        case VK_LCONTROL: return KeyKind::Ctrl;
        case VK_RCONTROL: return KeyKind::Ctrl;
        case VK_MENU: return KeyKind::Alt;

        default:
            return KeyKind::TERM;
    }
}

void tUpdateMouseBtn(MouseUpdateData& aData, WPARAM aWParam)
{
    aData.hold.set(MouseBtnKind::L, (aWParam & MK_LBUTTON) != 0);
    aData.hold.set(MouseBtnKind::R, (aWParam & MK_RBUTTON) != 0);
    aData.hold.set(MouseBtnKind::M, (aWParam & MK_MBUTTON) != 0);
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
    AE_BASE_UNUSED(aIndex);
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
    mExt.isClosed = false;
    ShowWindow(mExt.hwindow, SW_SHOWNORMAL);
    UpdateWindow(mExt.hwindow);
}

//------------------------------------------------------------------------------
bool Display::isClosed()const
{
    return mExt.isClosed;
}

//------------------------------------------------------------------------------
Display_Ext::Display_Ext(const DisplayContext& aContext)
: hinstance((HINSTANCE)GetModuleHandle(0))
, hwindow()
, windowClass()
, message()
, minSize({0, 0})
, mainScreen()
, hidPtr()
, isClosed(true)
, keyboardUpdateData()
, mouseUpdateData()
{
    // Windowクラスのセットアップ
    const char* className = "Adel Engine Application";
    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProcess;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hinstance;
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = className;
    windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&windowClass);

    // 変数準備
    const int style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

    // 矩形の計算
    RECT rect = {0, 0, LONG(aContext.width()), LONG(aContext.height())};
    AdjustWindowRect(
        &rect,
        style,
        FALSE
        );

    // ウィンドウの作成
    tCurrentDisplay.set(*this);
    hwindow = CreateWindow(
        className,
        "Window Title",
        style,
        aContext.locationX(),
        aContext.locationY(),
        rect.right - rect.left,
        rect.bottom - rect.top,
        0, // hWndParent
        0, // hMenu
        hinstance,
        0 // lpParam
        );
    tCurrentDisplay.unset(*this);

    minSize.x = GetSystemMetrics(SM_CXMINTRACK);
    minSize.y = GetSystemMetrics(SM_CYMINTRACK) + 1;

    // メインスクリーンの作成
    mainScreen.init(Ref(*this), aContext.width(), aContext.height());
}

//------------------------------------------------------------------------------
void Display_Ext::pollEvent(Application&)
{
    // pulseをクリア
    keyboardUpdateData.pulse.clear();

    // マウスのposUpdatedをクリア
    mouseUpdateData.posUpdated = false;

    // 今のディスプレイを設定
    tCurrentDisplay.set(*this);

    // メッセージ解析
    while (PeekMessage(&message, hwindow, 0, 0, PM_REMOVE) != 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    // 今のディスプレイを設定解除
    tCurrentDisplay.unset(*this);

    // マウスの座標変換
    if (mouseUpdateData.posUpdated) {
        mouseUpdateData.pos.y = s16(int(mainScreen->height()) - 1 - mouseUpdateData.pos.y);
    }

    // マウスのボタンが何か押されていたら強制的にposUpdatedを設定
    if (mouseUpdateData.hold.isAnyOn()) {
        mouseUpdateData.posUpdated = true;
    }

    // Hid更新
    if (hidPtr.isValid()) {
        hidPtr->ext_().keyboard.update(keyboardUpdateData);
        hidPtr->ext_().mouse.update(mouseUpdateData);
    }
}

//------------------------------------------------------------------------------
LRESULT Display_Ext::WindowProcess(HWND aHWND, UINT aMsg, WPARAM aWParam, LPARAM aLParam)
{
    return tCurrentDisplay->windowProcess(aHWND, aMsg, aWParam, aLParam);
}

//------------------------------------------------------------------------------
LRESULT Display_Ext::windowProcess(HWND aHWND, UINT aMsg, WPARAM aWParam, LPARAM aLParam)
{
    switch (aMsg) {
        case WM_GETMINMAXINFO:  // set window's minimum size
            ((MINMAXINFO*)aLParam)->ptMinTrackSize = minSize;
            return 0;

        case WM_SYSKEYDOWN:
            break;

        case WM_SYSKEYUP:
            break;

        case WM_KEYDOWN:
        {
            KeyKind::EnumType k = tToKeyKind(aWParam);
            if (k < KeyKind::TERM) {
                keyboardUpdateData.hold.set(k, true);
                keyboardUpdateData.pulse.set(k, true);
            }
        }
        break;

        case WM_KEYUP:
        {
            KeyKind::EnumType k = tToKeyKind(aWParam);
            if (k < KeyKind::TERM) {
                keyboardUpdateData.hold.set(k, false);
            }
        }
        break;

        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MOUSEMOVE:
        {
            switch (aMsg) {
                case WM_LBUTTONDOWN:
                case WM_MBUTTONDOWN:
                case WM_RBUTTONDOWN:
                {// ボタンが押された
                    // 更新する前にキャプチャー設定
                    if (mouseUpdateData.hold.isAllOff()) {
                        SetCapture(aHWND);
                    }

                    // 更新
                    tUpdateMouseBtn(mouseUpdateData, aWParam);
                }
                break;

                case WM_LBUTTONUP:
                case WM_MBUTTONUP:
                case WM_RBUTTONUP:
                {// ボタンが離された
                    // 更新
                    tUpdateMouseBtn(mouseUpdateData, aWParam);

                    // キャプチャー設定
                    if (mouseUpdateData.hold.isAllOff()) {
                        ReleaseCapture();
                    }
                }
                break;
                default:
                    break;
            }

            // 位置設定
            const s16 mx = reinterpret_cast<const s16*>(&aLParam)[0];
            const s16 my = reinterpret_cast<const s16*>(&aLParam)[1];
            mouseUpdateData.pos = ScreenPos(mx, my);
            mouseUpdateData.posUpdated = true;
        }
        break;

        case WM_DESTROY:
            isClosed = true;
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(aHWND, aMsg, aWParam, aLParam);
}

}} // namespace
// EOF
