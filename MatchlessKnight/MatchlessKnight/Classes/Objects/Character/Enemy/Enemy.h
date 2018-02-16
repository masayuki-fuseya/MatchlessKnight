//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Enemy.h
//!
//!	@brief	�G�N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/07/24
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef ENEMY
#define ENEMY

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Character.h"
#include "..\..\..\Collision\CollisionNode.h"
#include <d3d11.h>
#include <SimpleMath.h>


class Enemy :public Character
{
public:
	// �G�̎��
	enum ID
	{
		WEAK	// �ア�G
	};
private:
	// �ړ����x
	static const float SPEED;
	// 1�t���[���ł̊p�x�ω�����
	static const float ANGLE_DELTA_MAX;
	// ����
	static const int LIFE_TIME;
	// �덷
	static const float EPSILON;

	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �ǔ��Ώ�
	Character* m_target;
	// �c�����
	int m_lifeTime;
	// �����蔻��m�[�h
	SphereNode m_collisionNodeBody;
public:
	Enemy();
	~Enemy() {}

	virtual void Initialize();
	void Update() override;

	// �N����Ԃ̍X�V������
	void UpdateStanding() override;
	// �U����Ԃ̍X�V������
	void UpdateAttacking() override;
	// �N����Ԃ̕`�������
	void RenderStanding() override;
	// �U����Ԃ̕`�������
	void RenderAttacking() override;

	// ���W�������_���Ō��߂�
	void DesidePos();

	// �Q�b�^�[ //////////////////////////////////

	// �����Ă��邩���擾����
	const bool GetIsAlive()
	{
		return m_isAlive;
	}
	// �����蔻�苅���擾����
	const SphereNode& GetCollisionNodeSphere()
	{
		return m_collisionNodeBody;
	}

	//////////////////////////////////////////////

	// �Z�b�^�[ //////////////////////////////////

	// �����Ă��邩��ݒ肷��
	void SetIsAlive(const bool isAlive)
	{
		m_isAlive = isAlive;
	}
	// ���x��ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity)
	{
		m_velocity = velocity;
	}
	// �ǔ��Ώۂ�ݒ肷��
	void SetTarget(Character* target)
	{
		m_target = target;
	}

	//////////////////////////////////////////////
private:
	// �v���C���[��ǔ����鏀��������
	void StartPursue(const DirectX::SimpleMath::Vector3& direction);
	// �v���C���[��ǔ�����
	void Pursue();
};

#endif // !ENEMY
