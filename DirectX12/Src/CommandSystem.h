#pragma once
#include "CommandObject.h"

/// <summary>
/// �V�X�e���̃��C���`����i��R�}���h�@�\���܂Ƃ߂��N���X
/// </summary>
class cCommandSystem
{
public:
	cCommandSystem();
	~cCommandSystem() = default;

private:
	std::unique_ptr <cCommandObject[]> m_pGameCommand;		// ���C���Q�[���ŗ��p����R�}���h�Q
	std::unique_ptr <cCommandObject> m_pBeginCommand;		// �O�����p�̃R�}���h�Q
	std::unique_ptr <cCommandObject> m_pEndCommand;			// �㏈���p�̃R�}���h�Q
};