//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Player.h
//!
//!	@brief	�v���C���[�N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/07/20
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef PLAYER
#define PLAYER

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Character.h"
#include "..\..\Sword\Sword.h"
#include "..\..\..\Collision\CollisionNode.h"
#include "..\..\..\Composite\CompositeVisitor.h"
#include "..\..\..\State\State.h"
#include <memory>


class INode;
class Sword;


class Player :public Character
{
private:
	// �v���C���[�p�[�c�̊�p�[�c
	std::shared_ptr<INode> m_rootParts;
	// ��
	std::unique_ptr<Sword> m_sword;
	// �����蔻��m�[�h
	SphereNode m_collisionNodeBody;
public:
	// �p�[�c
	enum PARTS
	{
		HEAD,				// ��
		BODY,				// ��
		RIGHT_UPPER_ARM,	// �E��r
		RIGHT_FORE_ARM,		// �E�O�r��
		RIGHT_HAND,			// �E��
		LEFT_UPPER_ARM,		// ����r
		LEFT_FORE_ARM,		// ���O�r��
		LEFT_HAND,			// ����
		RIGHT_THIGH,		// �E���
		RIGHT_CALF,			// �E�ӂ���͂�
		RIGHT_FOOT,			// �E��
		LEFT_THIGH,			// �����
		LEFT_CALF,			// ���ӂ���͂�
		LEFT_FOOT,			// ����

		PARTS_NUM			// �S�̂̐�
	};

	Player();
	~Player() {}

	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	void Finalize();

	// �N����Ԃ̍X�V������
	void UpdateStanding() override;
	// �U����Ԃ̍X�V������
	void UpdateAttacking() override;
	// �N����Ԃ̕`�������
	void RenderStanding() override;
	// �U����Ԃ̕`�������
	void RenderAttacking() override;

	// �U������
	bool IsAttack();

	// �Q�b�^�[ //////////////////////////////////

	// ���[�g�p�[�c���擾����
	INode* GetRootParts()
	{
		return m_rootParts.get();
	}
	// �����擾����
	Sword* GetSword()
	{
		return m_sword.get();
	}
	// �����蔻��m�[�h���擾����
	const SphereNode& GetCollisionNodeSphere()
	{
		return m_collisionNodeBody;
	}

	//////////////////////////////////////////////
private:
	// �v���C���[�p�[�c��ǉ�����
	void AddParts();
};

#endif // !PLAYER
