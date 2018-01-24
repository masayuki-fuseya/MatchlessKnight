//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	CollisionNode.cpp
//!
//!	@brief	�����蔻��m�[�h�̃\�[�X�t�@�C��
//!
//!	@date	2017/06/19
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "CollisionNode.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace DirectX::SimpleMath;

// �ÓI�����o�ϐ��̒�` ====================================================
bool CollisionNode::m_debugVisible = false;


//**********************************************************************
//!	@brief		�e��ݒ肷��
//!
//!	@param[in]	�e
//!
//!	@return		�Ȃ�
//**********************************************************************
void CollisionNode::SetParent(MasaboLib::Obj3D* parent)
{
	m_obj.SetParent(parent);
}



//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
SphereNode::SphereNode()
{
	m_localRadius = 1.0f;
}



//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void SphereNode::Initialize()
{
	m_obj.LoadModel(L"SphereNode");
}



//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void SphereNode::Update()
{
	m_obj.SetTranslation(m_translation);
	m_obj.SetScale(Vector3(m_localRadius));

	m_obj.Update();

	{// �����蔻�苅�̗v�f���v�Z
		const Matrix& worldm = m_obj.GetWorld();

		// ���f�����W�n�ł̒��S�_
		Vector3 center = Vector3::Zero;
		Vector3 right(1.0f, 0.0f, 0.0f);

		// ���[���h���W�ɕϊ�
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		Sphere::m_center = center;
		Sphere::m_radius = Vector3::Distance(center, right);
	}
}



//**********************************************************************
//!	@brief		�`�揈��
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void SphereNode::Render()
{
	m_obj.Render();
}
