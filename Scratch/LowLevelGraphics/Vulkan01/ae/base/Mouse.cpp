// 文字コード：UTF-8
#include <ae/base/Mouse.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Mouse::Mouse()
: mData()
, mPos()
, mTrigger()
, mRelease()
{
}

//------------------------------------------------------------------------------
void Mouse::update(const MouseUpdateData& aData)
{
    // メモ
    const MouseUpdateData pre = mData;
    const MouseUpdateData cur = aData;
    mData = aData;

    // 更新
    if (mData.posUpdated != 0) {
        mPos = mData.pos;
    }
    mTrigger = ~pre.hold &  cur.hold;
    mRelease = pre.hold & ~cur.hold;
}

//------------------------------------------------------------------------------
const MouseUpdateData Mouse::lastUpdateData()const
{
    return mData;
}

//------------------------------------------------------------------------------
bool Mouse::isPosUpdated()const
{
    return mData.posUpdated != 0;
}

//------------------------------------------------------------------------------
const ScreenPosPod Mouse::pos()const
{
    return mPos;
}

//------------------------------------------------------------------------------
bool Mouse::isHold(const MouseBtnKind::EnumType aKind)const
{
    return mData.hold.get(aKind);
}

//------------------------------------------------------------------------------
bool Mouse::isTrigger(const MouseBtnKind::EnumType aKind)const
{
    return mTrigger.get(aKind);
}

//------------------------------------------------------------------------------
bool Mouse::isRelease(const MouseBtnKind::EnumType aKind)const
{
    return mRelease.get(aKind);
}

//------------------------------------------------------------------------------
const MouseBtnBitSet Mouse::hold()const
{
    return mData.hold;
}

//------------------------------------------------------------------------------
const MouseBtnBitSet Mouse::trigger()const
{
    return mTrigger;
}

//------------------------------------------------------------------------------
const MouseBtnBitSet Mouse::release()const
{
    return mRelease;
}

}} // namespace
// EOF
