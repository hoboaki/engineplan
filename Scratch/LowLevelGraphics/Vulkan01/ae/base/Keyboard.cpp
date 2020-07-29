// 文字コード：UTF-8
#include <ae/base/Keyboard.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

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
void Keyboard::update(const KeyboardUpdateData& aData)
{
    // データ設定
    const KeyboardUpdateData  pre = data_;
    data_ = aData;
    const KeyboardUpdateData& cur = data_;

    // 更新
    trigger_ = ~pre.hold &  cur.hold;
    release_ = pre.hold & ~cur.hold;
    pulse_ = data_.pulse | trigger_;
    repeat_ = ~pulse_ & trigger_;
}

//------------------------------------------------------------------------------
const KeyboardUpdateData Keyboard::lastUpdateData()const
{
    return data_;
}

//------------------------------------------------------------------------------
bool Keyboard::isHold(const KeyKind::EnumType aKind)const
{
    return data_.hold.get(aKind);
}

//------------------------------------------------------------------------------
bool Keyboard::isTrigger(const KeyKind::EnumType aKind)const
{
    return trigger_.get(aKind);
}

//------------------------------------------------------------------------------
bool Keyboard::isRepeat(const KeyKind::EnumType aKind)const
{
    return repeat_.get(aKind);
}

//------------------------------------------------------------------------------
bool Keyboard::isPulse(const KeyKind::EnumType aKind)const
{
    return pulse_.get(aKind);
}

//------------------------------------------------------------------------------
bool Keyboard::isRelease(const KeyKind::EnumType aKind)const
{
    return release_.get(aKind);
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::hold()const
{
    return data_.hold;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::trigger()const
{
    return trigger_;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::repeat()const
{
    return repeat_;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::pulse()const
{
    return pulse_;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::release()const
{
    return release_;
}

}} // namespace
// EOF
