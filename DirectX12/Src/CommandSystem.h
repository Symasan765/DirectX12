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

	std::shared_ptr <cCommandObject> GetBeginCommand() { return m_pBeginCommand; };
	std::shared_ptr <cCommandObject> GetEndCommand() { return m_pEndCommand; };

	void AllocReset(int frameIndex);
private:
	std::shared_ptr <cCommandObject[]> m_pGameCommand;		// ���C���Q�[���ŗ��p����R�}���h�Q
	std::shared_ptr <cCommandObject> m_pBeginCommand;		// �O�����p�̃R�}���h�Q
	std::shared_ptr <cCommandObject> m_pEndCommand;			// �㏈���p�̃R�}���h�Q
};