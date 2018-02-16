//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	AttackingState.h
//!
//!	@brief	�U����ԃN���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/08/28
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef ATTACKING_STATE
#define ATTACKING_STATE

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "MasaboLib.h"
#include "State.h"
#include "..\Objects\Character\Character.h"


class AttackingState :public State, public MasaboLib::Singleton<AttackingState>
{
private:
	friend class MasaboLib::Singleton<AttackingState>;

	// �U����Ԃ̃L�����N�^�[
	Character* m_character;
public:
	void Initialize(Character* character) override;
	void Execute() override;
	void Render() override;
private:
	AttackingState() {}
};

#endif // !ATTACKING_STATE
