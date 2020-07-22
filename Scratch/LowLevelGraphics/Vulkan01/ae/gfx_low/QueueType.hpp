// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Queue の特性。
enum class QueueType {
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
