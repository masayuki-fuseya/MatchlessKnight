//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerRightThigh.h
//!
//!	@brief	�v���C���[�̉E��ڂ̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAYER_RIGHT_THIGH
#define PLAYER_RIGHT_THIGH

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Player.h"


class PlayerRightThigh :public Player
{
public:
	PlayerRightThigh();
	~PlayerRightThigh() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_RIGHT_THIGH
