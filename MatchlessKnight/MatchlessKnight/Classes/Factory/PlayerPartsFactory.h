//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerPartsFactory.h
//!
//!	@brief	�v���C���[�p�[�c�����H��N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAYER_PARTS_FACTORY
#define PLAYER_PARTS_FACTORY

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Objects\Character\Player\Player.h"
#include <memory>


class PlayerPartsFactory
{
public:
	// �v���C���[�p�[�c�𐶐�����
	std::unique_ptr<Player>&& Create(Player::PARTS parts);
};

#endif // !PLAYER_PARTS_FACTORY
