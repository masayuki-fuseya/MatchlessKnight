//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	WeakEnemy.h
//!
//!	@brief	�ア�G�̃N���X�̃w�b�_�t�@�C��
//!
//!	@date	2018/01/18
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef WEAK_ENEMY
#define WEAK_ENEMY

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Enemy.h"


class WeakEnemy :public Enemy
{
public:
	WeakEnemy();
	~WeakEnemy() {}

	void Initialize() override;
};

#endif // !WEAK_ENEMY
