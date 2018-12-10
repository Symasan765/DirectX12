#pragma once
#include "Main.h"

struct WindowBuuferStruct
{
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
	D3D12_CPU_DESCRIPTOR_HANDLE descHandleRtv;		// 現在のフレームで使用するRTVハンドルを保持
	D3D12_CPU_DESCRIPTOR_HANDLE descHandleDsv;		// 現在のフレームで使用するDSVハンドルを保持
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> HeapRtv;	// ハンドル取得に使用
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> HeapDsv;	// ハンドル取得に使用
};