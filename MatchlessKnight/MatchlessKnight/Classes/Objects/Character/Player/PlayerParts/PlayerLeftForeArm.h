//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerLeftForeArm.h
//!
//!	@brief	�v���C���[�̍��O�r���̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAEYR_LEFT_FORE_ARM
#define PLAEYR_LEFT_FORE_ARM

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Player.h"


class PlayerLeftForeArm :public Player
{
public:
	PlayerLeftForeArm();
	~PlayerLeftForeArm() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAEYR_LEFT_FORE_ARM
