//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerLeftThigh.h
//!
//!	@brief	�v���C���[�̍���ڂ̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAYER_LEFT_THIGH
#define PLAYER_LEFT_THIGH

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Player.h"


class PlayerLeftThigh :public Player
{
public:
	PlayerLeftThigh();
	~PlayerLeftThigh() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_LEFT_THIGH
