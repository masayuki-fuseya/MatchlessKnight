//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	EnemyFactory.h
//!
//!	@brief	�G�����H��N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/07/24
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef ENEMY_FACTORY
#define ENEMY_FACTORY

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Objects\Character\Enemy\Enemy.h"
#include <memory>
#include <vector>


class EnemyFactory
{
private:
	// �G
	std::vector<std::shared_ptr<Enemy>> m_enemies;
public:
	void Initialize();

	// �����Ă��Ȃ��G��Ԃ�
	std::shared_ptr<Enemy> Reallocate(Enemy::ID id);
};

#endif // !ENEMY_FACTORY
