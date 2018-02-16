//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	State.h
//!
//!	@brief	��ԑJ�ڂ̊��N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/08/04
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef STATE
#define STATE

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "..\Objects\Character\Character.h"


class  Character;


class State
{
public:
	virtual void Initialize(Character* character) = 0;
	virtual void Execute() = 0;
	virtual void Render() = 0;
};

#endif // !STATE
