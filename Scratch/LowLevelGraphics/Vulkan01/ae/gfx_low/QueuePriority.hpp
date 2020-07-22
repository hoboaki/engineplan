// 文字コード：UTF-8
#pragma once

//------------------------------------------------------------------------------
namespace ae {
namespace gfx_low {

/// Queue の実行優先度。
enum class QueuePriority {
	/// 通常。
	Normal,

	/// Normal より高い。非サポート環境では Normal と同じ優先度になる。
	High,

	/// High より高い。非サポート環境では High もしくは Normal と同じ優先度になる。
	Highest,

	TERM,
};

}
}  // namespace ae
// EOF
