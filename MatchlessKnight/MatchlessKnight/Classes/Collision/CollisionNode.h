//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	CollisionNode.h
//!
//!	@brief	�����蔻��m�[�h�̃w�b�_�t�@�C��
//!
//!	@date	2017/06/19
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

#include "Collision.h"
#include "MasaboLib.h"
#include <d3d11.h>
#include <SimpleMath.h>

class CollisionNode
{
protected:
	static bool m_debugVisible;

	// �f�o�b�O�\���I�u�W�F�N�g
	MasaboLib::Obj3D m_obj;
	// �e����̃I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_translation;
public:
	static bool GetDebugVisible()
	{
		return m_debugVisible;
	}

	static void SetDebugVisible(bool debugVisible)
	{
		m_debugVisible = debugVisible;
	}
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	void SetParent(MasaboLib::Obj3D* parent);
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation)
	{
		m_translation = translation;
	}
};

// ���p�̓����蔻��m�[�h
class SphereNode :public CollisionNode, public Sphere
{
private:
	// ���[�J�����a
	float m_localRadius;
public:
	SphereNode();

	void Initialize();
	void Update();
	void Render();

	void SetLocalRadius(float localRadius)
	{
		m_localRadius = localRadius;
	}
};