//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	FollowCamera.cpp
//!
//!	@brief	�v���C���[�ɒǏ]����J�����N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/05/15
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "FollowCamera.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace DirectX::SimpleMath;

// �ÓI�����o�ϐ��̒�` ====================================================
const float FollowCamera::CAMERA_DISTANCE = 7.0f;


//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	����
//!	@param[in]	�c��
//!
//!	@return		�Ȃ�
//**********************************************************************
FollowCamera::FollowCamera(int width, int height)
	: MasaboLib::Camera(width, height)
	, m_targetAngle(0.0f)
	, m_target(nullptr)
{
}



//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void FollowCamera::Initialize()
{
	if (m_target)
	{
		// �Ǐ]�Ώۂ̍��W���擾����
		m_targetPos = m_target->GetTranslation();
	}

	// �����������v�Z����
	m_refPos = m_targetPos + Vector3(0.0f, 4.0f, 0.0f);

	// �x�N�g������]������
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	// �J�����̈ʒu���v�Z����
	m_eyePos = m_refPos + cameraV;
}



//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void FollowCamera::Update()
{
	// �Ǐ]�Ώۂ��ݒ肳��Ă��Ȃ���Δ�����
	if (!m_target)
	{
		Camera::Update();
		return;
	}

	// �Ǐ]�Ώۂ̍��W�Ɗp�x���擾����
	m_targetPos = m_target->GetTranslation();
	m_targetAngle = m_target->GetRotation().y;

	// �����������v�Z����
	Vector3 refPos = m_targetPos + Vector3(0.0f, 4.0f, 0.0f);

	// �x�N�g������]������
	Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANCE);
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	cameraV = Vector3::TransformNormal(cameraV, rotmat);
	// �J�����̈ʒu���v�Z����
	Vector3 eyePos = refPos + cameraV;

	// ���_�����݈ʒu�����Ԃ���
	m_eyePos = m_eyePos + (eyePos - m_eyePos) * 0.05f;
	// �Q�Ɠ_�����݈ʒu�����Ԃ���
	m_refPos = m_refPos + (refPos - m_refPos) * 0.2f;

	// �s����X�V����
	Camera::Update();
}
