// 文字コード：UTF-8
#include <ae/base/Keyboard.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Keyboard::Keyboard()
: mData()
, mTrigger()
, mRepeat()
, mPulse()
, mRelease()
{
}

//------------------------------------------------------------------------------
void Keyboard::update(const KeyboardUpdateData& aData)
{
    // データ設定
    const KeyboardUpdateData  pre = mData;
    mData = aData;
    const KeyboardUpdateData& cur = mData;

    // 更新
    mTrigger = ~pre.hold &  cur.hold;
    mRelease = pre.hold & ~cur.hold;
    mPulse = mData.pulse | mTrigger;
    mRepeat = ~mPulse & mTrigger;
}

//------------------------------------------------------------------------------
const KeyboardUpdateData Keyboard::lastUpdateData()const
{
    return mData;
}

//------------------------------------------------------------------------------
bool Keyboard::isHold(const KeyKind::EnumType aKind)const
{
    return mData.hold.get(aKind);
}

//------------------------------------------------------------------------------
bool Keyboard::isTrigger(const KeyKind::EnumType aKind)const
{
    return mTrigger.get(aKind);
}

//------------------------------------------------------------------------------
bool Keyboard::isRepeat(const KeyKind::EnumType aKind)const
{
    return mRepeat.get(aKind);
}

//------------------------------------------------------------------------------
bool Keyboard::isPulse(const KeyKind::EnumType aKind)const
{
    return mPulse.get(aKind);
}

//------------------------------------------------------------------------------
bool Keyboard::isRelease(const KeyKind::EnumType aKind)const
{
    return mRelease.get(aKind);
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::hold()const
{
    return mData.hold;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::trigger()const
{
    return mTrigger;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::repeat()const
{
    return mRepeat;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::pulse()const
{
    return mPulse;
}

//------------------------------------------------------------------------------
const KeyBitSet Keyboard::release()const
{
    return mRelease;
}

}} // namespace
// EOF
