//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerLeftCalf.h
//!
//!	@brief	�v���C���[�̍��ӂ���͂��̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAYER_LEFT_CALF
#define PLAYER_LEFT_CALF

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Player.h"


class PlayerLeftCalf :public Player
{
public:
	PlayerLeftCalf();
	~PlayerLeftCalf() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_LEFT_CALF
