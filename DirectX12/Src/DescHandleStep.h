#pragma once
#include "Main.h"

/// <summary>
/// �q�[�v�T�C�Y�̎擾���s���N���X
/// </summary>
class cDescHandleStep
{
public:
	cDescHandleStep() = default;
	~cDescHandleStep() = default;
	static UINT GetSize(D3D12_DESCRIPTOR_HEAP_TYPE type);
	void Init(ID3D12Device* dev);
private:
	static UINT m_Size[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
};