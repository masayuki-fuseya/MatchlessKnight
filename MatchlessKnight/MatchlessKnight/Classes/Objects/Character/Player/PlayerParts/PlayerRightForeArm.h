//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerRightForeArm.h
//!
//!	@brief	�v���C���[�̉E�O�r���̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAYER_RIGHT_FORE_ARM
#define PLAYER_RIGHT_FORE_ARM

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Player.h"


class PlayerRightForeArm :public Player
{
public:
	PlayerRightForeArm();
	~PlayerRightForeArm() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_RIGHT_FORE_ARM
