//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Character.h
//!
//!	@brief	�L�����N�^�[�N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/08/28
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef CHARACTER
#define CHARACTER

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "MasaboLib.h"
#include "..\..\State\State.h"
#include <d3d11.h>
#include <memory>
#include <SimpleMath.h>


class State;


class Character :public MasaboLib::Obj3D
{
protected:
	// ���݂̏��
	State* m_currentState;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �c�胉�C�t
	int m_life;
	// �����Ă��邩
	bool m_isAlive;
public:
	Character();
	virtual ~Character() {}

	// �s����v�Z����
	void CalcMatrix();

	// �N����Ԃ̍X�V������
	virtual void UpdateStanding() = 0;
	// �U����Ԃ̍X�V������
	virtual void UpdateAttacking() = 0;
	// �N����Ԃ̕`�������
	virtual void RenderStanding() = 0;
	// �U����Ԃ̕`�������
	virtual void RenderAttacking() = 0;

	// ��Ԃ�ς���
	void ChangeState(State* currentState);
	// �̗͂����炷
	void ReduceLife(const int damage);
};

#endif // !CHARACTER
