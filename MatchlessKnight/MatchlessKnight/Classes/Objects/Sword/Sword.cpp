//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Sword.cpp
//!
//!	@brief	���N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/07/25
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Sword.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace DirectX;
using namespace DirectX::SimpleMath;

// �ÓI�����o�ϐ��̒�` ====================================================
const int Sword::MAX_RECOVERY_TIME = 20;


//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
Sword::Sword()
	: m_time(0.0f)
	, m_recoveryTime(0)
	, m_canWield(true)
{
}



//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�v���C���[
//!
//!	@return		�Ȃ�
//**********************************************************************
void Sword::Initialize(Player* player)
{
	// ���f����ǂݍ���
	LoadModel(L"KnightSword");

	// �v���C���[��e�Ƃ��Đݒ肷��
	m_parent = player;

	// �����蔻��m�[�h������������
	m_collisionNode.Initialize();
	// ����e�ɐݒ肷��
	m_collisionNode.SetParent(this);
	// ���W��ݒ肷��
	m_collisionNode.SetTranslation(Vector3(-2.0f, 3.0f, 1.5f));
	// ���a��ݒ肷��
	m_collisionNode.SetLocalRadius(2.0f);
}



//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�v���C���[
//!
//!	@return		true:�N�����
//!	@return		false:����U��I�����
//**********************************************************************
bool Sword::Update(Player* player)
{
	// m_endTrans�̈ʒu�܂ōs������
	if (m_translation == m_endTrans)
	{
		// ����U��I����Ă�����
		if (!m_canWield)
		{
			// ��莞�Ԃ����ēx����U��Ȃ��悤�ɂ���
			m_recoveryTime++;
			if (m_recoveryTime >= MAX_RECOVERY_TIME)
			{
				// ����������
				m_translation = Vector3::Zero;
				m_startTrans = Vector3::Zero;
				m_endTrans = Vector3::Zero;
				m_canWield = true;
			}
		}
	}
	else
	{
		if (m_time < 1.0f)
		{
			// m_startTrans����m_endTrans�܂Ő��`��Ԃ���
			m_time += 0.05f;
			m_translation = Vector3::Lerp(m_startTrans, m_endTrans, m_time);
		}
		else
		{
			// ���`��ԏI��
			m_time = 1.0f;
			m_translation = m_endTrans;
		}
	}

	Obj3D::Update();

	// �����蔻��m�[�h���X�V����
	m_collisionNode.Update();

	if (m_canWield)
		return false;

	return true;
}



//**********************************************************************
//!	@brief		����U��
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Sword::Wield()
{
	// ����U���Ă�r����������ēx�U��Ȃ�
	if (!m_canWield)
		return;

	// ���̕�ԗp�ϐ���ݒ肷��
	m_translation = Vector3::Zero;
	m_startTrans = Vector3(0.0f, 1.6f, 0.0f);
	m_endTrans = Vector3(3.2f, -1.0f, 0.0f);
	m_time = 0.0f;
	m_recoveryTime = 0;
	m_canWield = false;
}
