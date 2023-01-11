// 文字コード：UTF-8
#include <ae/base/Mouse.hpp>

//------------------------------------------------------------------------------
namespace ae::base {

//------------------------------------------------------------------------------
Mouse::Mouse()
: data_()
, pos_()
, trigger_()
, release_()
{
}

//------------------------------------------------------------------------------
void Mouse::Update(const MouseUpdateData& data)
{
    // メモ
    const MouseUpdateData pre = data_;
    const MouseUpdateData cur = data;
    data_ = data;

    // 更新
    if (data_.posUpdated != 0) {
        pos_ = data_.pos;
    }
    trigger_ = ~pre.hold & cur.hold;
    release_ = pre.hold & ~cur.hold;
}

//------------------------------------------------------------------------------
const MouseUpdateData Mouse::LastUpdateData() const
{
    return data_;
}

//------------------------------------------------------------------------------
bool Mouse::IsPosUpdated() const
{
    return data_.posUpdated != 0;
}

//------------------------------------------------------------------------------
const ScreenPosPod Mouse::Pos() const
{
    return pos_;
}

//------------------------------------------------------------------------------
bool Mouse::IsHold(const MouseBtnKind::EnumType kind) const
{
    return data_.hold.Get(kind);
}

//------------------------------------------------------------------------------
bool Mouse::IsTrigger(const MouseBtnKind::EnumType kind) const
{
    return trigger_.Get(kind);
}

//------------------------------------------------------------------------------
bool Mouse::IsRelease(const MouseBtnKind::EnumType kind) const
{
    return release_.Get(kind);
}

//------------------------------------------------------------------------------
const MouseBtnBitSet Mouse::Hold() const
{
    return data_.hold;
}

//------------------------------------------------------------------------------
const MouseBtnBitSet Mouse::Trigger() const
{
    return trigger_;
}

//------------------------------------------------------------------------------
const MouseBtnBitSet Mouse::Release() const
{
    return release_;
}

} // namespace ae::base
// EOF
