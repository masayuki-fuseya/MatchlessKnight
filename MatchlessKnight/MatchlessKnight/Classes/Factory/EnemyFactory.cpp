//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	EnemyFactory.cpp
//!
//!	@brief	�G�����H��N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/07/24
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "EnemyFactory.h"
#include "..\Scenes\PlayScene.h"
#include "..\Objects\Character\Enemy\WeakEnemy.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace std;


//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void EnemyFactory::Initialize()
{
	// �G�̍ő吔����������
	m_enemies.resize(MasaboLib::PlayScene::MAX_ENEMY_NUM);
	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr)
	{
		(*itr) = make_shared<WeakEnemy>();
		(*itr)->Initialize();
	}
}



//**********************************************************************
//!	@brief		�����Ă��Ȃ��G��Ԃ�
//!
//!	@param[in]	�G�̎��
//!
//!	@return		�G�̃|�C���^
//**********************************************************************
shared_ptr<Enemy> EnemyFactory::Reallocate(Enemy::ID id)
{
	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr)
	{
		// �����Ă��Ȃ��G������Έʒu�����߂ĕԂ�
		if (!(*itr)->GetIsAlive())
		{
			(*itr)->SetIsAlive(true);
			(*itr)->DesidePos();
			return (*itr);
		}
	}

	return nullptr;
}
