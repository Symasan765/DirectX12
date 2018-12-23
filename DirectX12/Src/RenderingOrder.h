#pragma once
#include "MeshRenderer.h"
#include "Render.h"
#include "DXMath.h"
#include <vector>
#include <unordered_map>

/// <summary>
/// cMeshRenderer�R���|�[�l���g����I�u�W�F�N�g�̕`��˗����󂯎��N���X
/// </summary>
class cRenderingOrder
{
public:
	cRenderingOrder() = default;
	~cRenderingOrder() = default;

	static void AddRenderObj(cMeshRenderer* obj,int frameIndex);		// �ǂ�����ł��o�^���ł���悤��static
	void ClearObjs(int frameIndex);		// �N���A�͎��Ԃ������Ă���ꏊ�ł̂݉\�B�`�悪�I��������ƂɎ��s����
	void RetrunWorldMatrix(DirectX::XMFLOAT4X4* mat,int frameIndex);	// TODO �b��I�ɓ���Ă�
private:
	static std::unordered_map<int, std::vector<cMeshRenderer*>> m_ObjMap[Render::g_LatencyNum];
};