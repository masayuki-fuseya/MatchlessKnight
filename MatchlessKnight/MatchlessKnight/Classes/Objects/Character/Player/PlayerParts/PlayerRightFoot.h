//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerRightFoot.h
//!
//!	@brief	�v���C���[�̉E���̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAYER_RIGHT_FOOT
#define PLAYER_RIGHT_FOOT

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Player.h"


class PlayerRightFoot :public Player
{
public:
	PlayerRightFoot();
	~PlayerRightFoot() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_RIGHT_FOOT
