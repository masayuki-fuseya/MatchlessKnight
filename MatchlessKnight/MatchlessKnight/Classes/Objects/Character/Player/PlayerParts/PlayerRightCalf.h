//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerRightCalf.h
//!
//!	@brief	�v���C���[�̉E�ӂ���͂��̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAYER_RIGHT_CALF
#define PLAYER_RIGHT_CALF

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Player.h"


class PlayerRightCalf :public Player
{
public:
	PlayerRightCalf();
	~PlayerRightCalf() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_RIGHT_CALF
