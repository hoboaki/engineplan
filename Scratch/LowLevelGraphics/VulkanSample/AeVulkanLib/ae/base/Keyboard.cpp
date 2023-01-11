// 文字コード：UTF-8
#include <ae/base/Keyboard.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Keyboard::Keyboard()
: data_()
, trigger_()
, repeat_()
, pulse_()
, release_()
{
}

//------------------------------------------------------------------------------
void Keyboard::Update(const KeyboardUpdateData& data)
{
    // データ設定
    const KeyboardUpdateData pre = data_;
    data_ = data;
    const KeyboardUpdateData& cur = data_;

    // 更新
    trigger_ = ~pre.hold & cur.hold;
    release_ = pre.hold & ~cur.hold;
    pulse_ = data_.pulse | trigger_;
    repeat_ = ~pulse_ & trigger_;
}

//------------------------------------------------------------------------------
const KeyboardUpdateData Keyboard::LastUpdateData() const
{
    return data_;
}

//------------------------------------------------------------------------------
bool Keyboard::IsHold(const KeyKind::EnumType kind) const
{
    return data_.hold.Get(kind);
}

//------------------------------------------------------------------------------
bool Keyboard::IsTrigger(const KeyKind::EnumType kind) const
{
    return trigger_.Get(kind);
}

//------------------------------------------------------------------------------
bool Keyboard::IsRepeat(const KeyKind::EnumType kind) const
{
    return repeat_.Get(kind);
}

//------------------------------------------------------------------------------
bool Keyboard::IsPulse(const KeyKind::EnumType kind) const
{
    return pulse_.Get(kind);
}

//------------------------------------------------------------------------------
bool Keyboard::IsRelease(const KeyKind::EnumType kind) const
{
    return release_.Get(kind);
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::Hold() const
{
    return data_.hold;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::Trigger() const
{
    return trigger_;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::Repeat() const
{
    return repeat_;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::Pulse() const
{
    return pulse_;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::Release() const
{
    return release_;
}

} // namespace ae::base
// EOF
