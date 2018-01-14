//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Game.h
//!
//!	@brief	�Q�[���N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/12/27
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef GAME
#define GAME

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Window.h"
#include "MasaboLib.h"
#include <CommonStates.h>
#include <d3d11.h>
#include <Effects.h>
#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>

class Window;


class Game
{
private:
	// �o�͕�
	int m_width;
	// �o�͍�
	int m_height;

	// �E�B���h�E
	std::unique_ptr<Window> m_window;
protected:
	// �X�e�b�v�^�C�}�[
	MasaboLib::DX::StepTimer m_timer;
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_batch;
	// �t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_font;
	// �G�t�F�N�g�t�@�N�g���C���^�[�t�F�[�X
	std::unique_ptr<DirectX::IEffectFactory> m_effectFactory;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
public:
	Game(int width, int height);

    virtual void Initialize();
    // �Q�[�����[�v�����s����
	MSG Run();
	virtual void Update(const MasaboLib::DX::StepTimer& timer);
	virtual void Render(const MasaboLib::DX::StepTimer& timer);
	virtual void Finalize();

	// ��ʂ��N���A����
	virtual void Clear();
	// �o�b�N�o�b�t�@���X�N���[���ɑ���
	virtual void Present();

	// ���b�Z�[�W�n���h��
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

	// �f�t�H���g�E�B���h�E�T�C�Y�ɕύX����
    void GetDefaultSize(int& width, int& height) const;

	// �Q�[�����I���
	void Exit();
protected:
	// FPS��`�悷��
	void DrawFPS();
};

#endif	// GAME
