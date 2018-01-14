//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	MyGame.h
//!
//!	@brief	�����̃Q�[���N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/12/27
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef MYGAME
#define MYGAME

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Game.h"
#include "MasaboLib.h"


class MyGame :public Game
{
public:
	MyGame(int width, int height);

	void Initialize() override;
	void Update(const MasaboLib::DX::StepTimer& timer) override;
	void Render(const MasaboLib::DX::StepTimer& timer) override;
	void Finalize() override;
};

#endif // MYGAME
