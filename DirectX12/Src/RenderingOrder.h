#pragma once
#include "MeshRenderer.h"
#include "Render.h"
#include "DXMath.h"
#include <vector>
#include <unordered_map>

struct cPsoRendrObjData {
	std::unordered_map<int, std::vector<cMeshRenderer*>> m_ObjMap;
};

/// <summary>
/// cMeshRenderer�R���|�[�l���g����I�u�W�F�N�g�̕`��˗����󂯎��N���X
/// </summary>
class cRenderingOrder
{
public:
	cRenderingOrder() = default;
	~cRenderingOrder() = default;

	static void AddRenderObj(cMeshRenderer* obj);		// �ǂ�����ł��o�^���ł���悤��static
	void RetrunWorldMatrix(DirectX::XMFLOAT4X4* mat,int frameIndex);	// TODO �b��I�ɓ���Ă�
private:
	static std::unordered_map<std::string, std::vector<cPsoRendrObjData>> m_PsoMap;
};