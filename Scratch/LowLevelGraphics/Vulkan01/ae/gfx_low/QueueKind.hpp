// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Queue の種類。
enum class QueueKind {
	/// 無効値。
	Invalid,

	/// Graphics、Compute、Copy、をサポート。
	Normal,

	/// Compute のみをサポート。
	ComputeOnly,

	/// Copy のみをサポート。
	CopyOnly,

	TERM,
};

}}
// EOF
