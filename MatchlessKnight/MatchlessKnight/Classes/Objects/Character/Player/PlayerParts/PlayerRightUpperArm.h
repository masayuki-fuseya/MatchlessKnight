//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerRightUpperArm.h
//!
//!	@brief	�v���C���[�̉E��r�̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAYER_RIGHT_UPPER_ARM
#define PLAYER_RIGHT_UPPER_ARM

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Player.h"


class PlayerRightUpperArm :public Player
{
public:
	PlayerRightUpperArm();
	~PlayerRightUpperArm() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_RIGHT_UPPER_ARM
