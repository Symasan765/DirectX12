#pragma once
#include "Graphic3D.h"
#include "BoneStruct.h"
#include "InstVertexBuffer.h"

class cModelResource
{
public:
	cModelResource() = default;
	~cModelResource() = default;
	
	std::vector<cGraphic3D> m_Graphic;
	std::vector<BoneStruct> m_Bone;
	cInstVertexBuffer m_InstBuffer;
};