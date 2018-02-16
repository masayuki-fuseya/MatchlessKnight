//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Enemy.cpp
//!
//!	@brief	�G�N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/07/24
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Enemy.h"
#include "..\..\..\ADX2\ADX2Le.h"
#include "..\..\..\ADX2\PlayerSE.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace DirectX;
using namespace DirectX::SimpleMath;

// �ÓI�����o�ϐ��̒�` ====================================================
const float Enemy::SPEED = 0.1f;
const float Enemy::ANGLE_DELTA_MAX = DirectX::XMConvertToRadians(30.0f);
const int Enemy::LIFE_TIME = 120;
const float Enemy::EPSILON = 1.0e-2f;


//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
Enemy::Enemy()
	: m_target(nullptr)
	, m_lifeTime(0)
{
	m_isAlive = false;
}



//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Enemy::Initialize()
{
	// ���W�����߂�
	DesidePos();

	// �v���C���[�̒ǔ����J�n����
	StartPursue(Vector3(0.01f, 0.0f, 0.01f));

	// �����蔻��m�[�h������������
	m_collisionNodeBody.Initialize();
	// �G��e�ɐݒ肷��
	m_collisionNodeBody.SetParent(this);
	// ���W��ݒ肷��
	m_collisionNodeBody.SetTranslation(Vector3(0.0f, 3.0f, 0.0f));
	// ���a��ݒ肷��
	m_collisionNodeBody.SetLocalRadius(1.5f);
}



//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Enemy::Update()
{
	// �v���C���[��ǔ�����
	Pursue();

	// ���W�ړ�
	m_translation += m_velocity;

	// �����蔻��m�[�h�̍X�V������
	m_collisionNodeBody.Update();

	// �s��X�V����
	CalcMatrix();
}



//**********************************************************************
//!	@brief		�N����Ԃ̍X�V������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Enemy::UpdateStanding()
{
}



//**********************************************************************
//!	@brief		�U����Ԃ̍X�V������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Enemy::UpdateAttacking()
{
}



//**********************************************************************
//!	@brief		�N����Ԃ̕`�������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Enemy::RenderStanding()
{
}



//**********************************************************************
//!	@brief		�U����Ԃ̕`�������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Enemy::RenderAttacking()
{
}



//**********************************************************************
//!	@brief		���W�������_���Ō��߂�
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Enemy::DesidePos()
{
	// �ǂ̑O�̃����_���Ȉʒu�ɔz�u
	float x = (float)(rand() % 80 - 40);
	float z = -45.0f;
	m_translation = Vector3(x, 0, z);
}



//**********************************************************************
//!	@brief		�v���C���[��ǔ����鏀��������
//!
//!	@param[in]	���x�̌���
//!
//!	@return		�Ȃ�
//**********************************************************************
void Enemy::StartPursue(const Vector3& direction)
{
	// ����
	m_lifeTime = LIFE_TIME;
	// ���x
	m_velocity = direction;
	m_velocity.Normalize();
	m_velocity *= SPEED;

	// �����̉�]����i�s��������Z�o����
	{
		Vector3 Zminus = -Vector3::UnitZ;
		// ���ς̌�������A2�x�N�g���̓��ς��p�x���̃R�T�C���l
		// A: �f�t�H���g�̐i�s�����x�N�g��(Z�}�C�i�X����)
		// B: �U���Ώۂ̕����x�N�g��
		float cosine = Zminus.Dot(direction);
		// 2�x�N�g���p�x��<���W�A��>�����߂�
		float delta = acosf(cosine);

		// 2�x�N�g���̊p�x�����قƂ�ǂȂ����
		if (delta > EPSILON)
		{
			// A����B�։񂷍ۂ̉�]�����O�ςŋ��߂�
			Vector3 axis = Zminus.Cross(direction);
			axis.Normalize();
			// �w�肵����]������Ɏw�胉�W�A�������񂷃N�H�[�^�j�I���𓾂�
			Quaternion q = Quaternion::CreateFromAxisAngle(axis, delta);
			// ������]���Z�b�g
			m_quaternion = q;
			m_useQuaternion = true;
		}
	}
}



//**********************************************************************
//!	@brief		�v���C���[��ǔ�����
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Enemy::Pursue()
{
	bool death = false;

	if (m_lifeTime > 0)
	{
		if (--m_lifeTime <= 0)
		{
			//death = true;
		}
	}

	// �U���Ώۂ������
	if (!death && m_target)
	{
		// ���݂̐i�s�����x�N�g�������߂�i�P�ɑ��x�x�N�g���𐳋K���������́j
		Vector3 moveDir;
		m_velocity.Normalize(moveDir);

		// ���W�̍����x�N�g�������߂�
		Vector3 targetDir = m_target->GetTranslation() - GetTranslation();
		float distance = targetDir.Length();
		if (distance >= 1.0f)
		{
			targetDir.Normalize();

			// ���ς̌�������A2�x�N�g���̓��ς��p�x���̃R�T�C���l
			// A: ���݂̐i�s�����x�N�g��
			// B: �U���Ώۂ̕����x�N�g��
			float cosine = moveDir.Dot(targetDir);
			// 2�x�N�g���p�x��<���W�A��>�����߂�
			float delta = acosf(cosine);
			// 2�x�N�g���̊p�x�����قƂ�ǂȂ����
			if (delta > EPSILON)
			{
				// ���̃t���[���ł̉�]�p<���W�A��>������
				float angle;
				if (distance <= 2.0f)
				{// �������߂��ƗU�����\��������
					angle = min(delta, ANGLE_DELTA_MAX);
				}
				else
				{
					// �������Z���ƗU�����\��������
					float rate = 1.0f - (float)m_lifeTime / LIFE_TIME;
					angle = min(delta, rate * ANGLE_DELTA_MAX);
				}

				// A����B�։񂷍ۂ̉�]�����O�ςŋ��߂�
				Vector3 axis = moveDir.Cross(targetDir);
				axis.Normalize();
				// �w�肵����]������Ɏw�胉�W�A�������񂷃N�H�[�^�j�I���𓾂�
				Quaternion qDelta = Quaternion::CreateFromAxisAngle(axis, angle);
				// ����̉�]���𔽉f
				m_quaternion *= qDelta;
				m_useQuaternion = true;
				// ���x�x�N�g������]
				m_velocity = Vector3::Transform(Vector3(0, 0, SPEED), m_quaternion);
			}
		}
		else
		{
			// �ǐՏI��
			death = true;

			m_isAlive = false;
		}
	}

	if (death)
	{
		// �v���C���[�Ɠ�����������SE�̍Đ�
		ADX2Le::Play(CRI_PLAYER_DAMAGE);

		// �v���C���[�̗̑͂����炷
		m_target->ReduceLife(2);

		m_target = nullptr;
	}

	// ���x���ړ�����
	m_translation += m_velocity;

	//return false;
}
