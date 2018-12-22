#pragma once
#include "ComponentBase.h"
#include <string>

/// <summary>
/// ���b�V���`���S������R���|�[�l���g
/// </summary>
class cMeshRenderer : public cComponentBase
{
public:
	cMeshRenderer(cBehavior* owner);
	~cMeshRenderer() = default;

	void Update(float deltaTime);
	void Start() {};

	void Road(std::string fileName, std::string psoName);
	int ResourceID() { return m_ResourceID; };
private:
	int m_ResourceID = -1;
	std::string m_PsoName;
};