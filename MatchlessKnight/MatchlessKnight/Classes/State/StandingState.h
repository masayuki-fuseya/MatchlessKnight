//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	StandingState.h
//!
//!	@brief	�N����ԃN���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/08/28
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef STANDING_STATE
#define STANDING_STATE

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "MasaboLib.h"
#include "State.h"


class StandingState :public State, public MasaboLib::Singleton<StandingState>
{
private:
	friend class MasaboLib::Singleton<StandingState>;

	// �N����Ԃ̃L�����N�^�[
	Character* m_character;
public:
	void Initialize(Character* character) override;
	void Execute() override;
	void Render() override;
private:
	StandingState() {}
};

#endif // !STANDING_STATE
