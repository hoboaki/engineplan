// 文字コード：UTF-8
#include <ae/base/Mouse.hpp>

//------------------------------------------------------------------------------
namespace ae {
namespace base {

//------------------------------------------------------------------------------
Mouse::Mouse()
: data_()
, pos_()
, trigger_()
, release_()
{
}

//------------------------------------------------------------------------------
void Mouse::update(const MouseUpdateData& aData)
{
    // メモ
    const MouseUpdateData pre = data_;
    const MouseUpdateData cur = aData;
    data_ = aData;

    // 更新
    if (data_.posUpdated != 0) {
        pos_ = data_.pos;
    }
    trigger_ = ~pre.hold &  cur.hold;
    release_ = pre.hold & ~cur.hold;
}

//------------------------------------------------------------------------------
const MouseUpdateData Mouse::lastUpdateData()const
{
    return data_;
}

//------------------------------------------------------------------------------
bool Mouse::isPosUpdated()const
{
    return data_.posUpdated != 0;
}

//------------------------------------------------------------------------------
const ScreenPosPod Mouse::pos()const
{
    return pos_;
}

//------------------------------------------------------------------------------
bool Mouse::isHold(const MouseBtnKind::EnumType aKind)const
{
    return data_.hold.get(aKind);
}

//------------------------------------------------------------------------------
bool Mouse::isTrigger(const MouseBtnKind::EnumType aKind)const
{
    return trigger_.get(aKind);
}

//------------------------------------------------------------------------------
bool Mouse::isRelease(const MouseBtnKind::EnumType aKind)const
{
    return release_.get(aKind);
}

//------------------------------------------------------------------------------
const MouseBtnBitSet Mouse::hold()const
{
    return data_.hold;
}

//------------------------------------------------------------------------------
const MouseBtnBitSet Mouse::trigger()const
{
    return trigger_;
}

//------------------------------------------------------------------------------
const MouseBtnBitSet Mouse::release()const
{
    return release_;
}

}} // namespace
// EOF
