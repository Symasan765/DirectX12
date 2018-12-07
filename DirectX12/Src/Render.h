#pragma once

/// <summary>
/// 描画に利用しているデータをまとめている
/// </summary>
namespace Render {
	constexpr int g_LatencyNum = 2;		// 描画を遅らせる数。2は一つ前のフレームデータを使うことになる
	constexpr int g_ThreadNum = 4;		// 並列化させるコマンド実行の数
}