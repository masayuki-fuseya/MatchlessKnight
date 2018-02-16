//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Sword.h
//!
//!	@brief	���N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/07/25
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef SWORD
#define SWORD

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "MasaboLib.h"
#include "..\Character\Player\Player.h"
#include "..\..\Collision\CollisionNode.h"
#include <d3d11.h>
#include <Model.h>
#include <memory>
#include <SimpleMath.h>


class Player;


class Sword :public MasaboLib::Obj3D
{
private:
	// �d�����Ԃ����������܂ł̎���
	static const int MAX_RECOVERY_TIME;

	// ��Ԃ���ŏ��̍��W
	DirectX::SimpleMath::Vector3 m_startTrans;
	// �ۊǂ���Ō�̍��W
	DirectX::SimpleMath::Vector3 m_endTrans;
	// �����蔻��m�[�h
	SphereNode m_collisionNode;
	// ��ԗp�̎���
	float m_time;
	// �U��������̍d�����Ԃ��񕜂���܂ŃJ�E���g���鎞��
	int m_recoveryTime;
	// �U�邱�Ƃ��ł��邩
	bool m_canWield;
public:
	Sword();
	~Sword() {}

	void Initialize(Player* player);
	bool Update(Player* player);

	// ����U��
	void Wield();

	// �Q�b�^�[ //////////////////////////////////

	// �����蔻��m�[�h���擾����
	const SphereNode& GetCollisionNode()
	{
		return m_collisionNode;
	}
	// �U�邱�Ƃ��ł��邩���擾����
	const bool GetCanWield()
	{
		return m_canWield;
	}

	//////////////////////////////////////////////
};

#endif // !SWORD
