#pragma once

/// <summary>
/// �`��ɗ��p���Ă���f�[�^���܂Ƃ߂Ă���
/// </summary>
namespace Render {
	constexpr int g_LatencyNum = 2;		// �`���x�点�鐔�B2�͈�O�̃t���[���f�[�^���g�����ƂɂȂ�
	constexpr int g_ThreadNum = 4;		// ���񉻂�����R�}���h���s�̐�

	constexpr unsigned g_MaxInstNum = 256;		// �C���X�^���V���O�`��o����ő�I�u�W�F�N�g��
}