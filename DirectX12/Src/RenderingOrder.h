#pragma once
#include "MeshRenderer.h"
#include "Render.h"
#include "DXMath.h"
#include <vector>
#include <map>

/// <summary>
/// cMeshRenderer�R���|�[�l���g����I�u�W�F�N�g�̕`��˗����󂯎��N���X
/// </summary>
class cRenderingOrder
{
public:
	cRenderingOrder() = default;
	~cRenderingOrder() = default;

	static void AddRenderObj(cMeshRenderer* obj);		// �ǂ�����ł��o�^���ł���悤��static
	void RetrunWorldMatrix(int resourceID,DirectX::XMFLOAT4X4* mat,int frameIndex);	// TODO �b��I�ɓ���Ă�
	std::map<UINT, std::vector<cMeshRenderer*>>& GetMapObj() { return m_ObjMap; };
private:
	static std::map<UINT, std::vector<cMeshRenderer*>> m_ObjMap;
};