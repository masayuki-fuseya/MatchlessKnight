//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerHead.h
//!
//!	@brief	�v���C���[�̓��̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAYER_HEAD
#define PLAYER_HEAD

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Player.h"


class PlayerHead :public Player
{
public:
	PlayerHead();
	~PlayerHead() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_HEAD
