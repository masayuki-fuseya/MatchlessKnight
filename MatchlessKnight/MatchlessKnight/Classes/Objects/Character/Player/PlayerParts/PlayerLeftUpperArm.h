//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerLeftUpperArm.h
//!
//!	@brief	�v���C���[�̍���r�̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAYER_LEFT_UPPER_ARM
#define PLAYER_LEFT_UPPER_ARM

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Player.h"


class PlayerLeftUpperArm :public Player
{
public:
	PlayerLeftUpperArm();
	~PlayerLeftUpperArm() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_LEFT_UPPER_ARM
