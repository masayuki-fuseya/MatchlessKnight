//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerLeftFoot.h
//!
//!	@brief	�v���C���[�̍����̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAEYR_LEFT_FOOT
#define PLAEYR_LEFT_FOOT

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Player.h"


class PlayerLeftFoot :public Player
{
public:
	PlayerLeftFoot();
	~PlayerLeftFoot() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAEYR_LEFT_FOOT
