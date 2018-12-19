#pragma once
#include <string>
#include <unordered_map>
#include "DirectX12.h"
#include "ModelResource.h"

class cModelManager
{
public:
	cModelManager() = default;
	~cModelManager() = default;

	static UINT Load(std::string fileName);
private:
	static std::unordered_map<UINT, std::unique_ptr<cModelResource>> m_ResourceMap;
};