#pragma once
#include "Main.h"

class cFenceObj {
public:
	cFenceObj();
	~cFenceObj();
	void WaitForPreviousFrame(ID3D12CommandQueue*, DWORD MillSecTimeOut = INFINITE);
	void WaitForPreviousFrame(UINT value, DWORD MillSecTimeOut = INFINITE);
	void Signal(Microsoft::WRL::ComPtr<ID3D12CommandQueue>, unsigned totalFrame);
private:
	Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
	HANDLE m_fenceEvent;
	UINT64 m_fenceValue = 0;									// ローダークラスが保持
};