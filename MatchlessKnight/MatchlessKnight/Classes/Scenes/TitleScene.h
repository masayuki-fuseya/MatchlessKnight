//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	TitleScene.h
//!
//!	@brief	�^�C�g���V�[���N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/12/16
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef MASABO_TITLE_SCENE
#define MASABO_TITLE_SCENE

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "BaseScene.h"
#include <d3d11.h>
#include <memory>
#include <SimpleMath.h>
#include <wrl.h>


namespace MasaboLib
{
	class TitleScene :public BaseScene
	{
	private:
		// �ő�I������
		static const int MAX_SELECTION_ITEM;

		// �w�i�摜
		std::unique_ptr<Texture> m_backgroundTexture;
		// �^�C�g���摜
		std::unique_ptr<Texture> m_titleTexture;
		// "PUSH SPACE"�̉摜
		std::unique_ptr<Texture> m_pushSpaceTexture;
		// �I�����ډ摜
		std::unique_ptr<Texture> m_selectionItemTexture;
		// ���̉摜
		std::unique_ptr<Texture> m_arrowTexture;
		// �w�i�摜�̍��W
		DirectX::SimpleMath::Vector2 m_bgPos;
		// �X�y�[�X�L�[��������Ă��邩
		bool m_isPressedSpace;
		// "PUSH SPACE"�̃A�j���[�V�����p�^�C��
		float m_animationTime;
		// ���݂̑I������
		int m_selectionItem;
	public:
		TitleScene();
		~TitleScene() {}

		void Initialize() override;
		void Update(const DX::StepTimer& timer) override;
		void Render(const DX::StepTimer& timer, DirectX::SpriteBatch* batch, DirectX::SpriteFont* font) override;
		void Finalize() override;
	};
}

#endif // !MASABO_TITLE_SCENE
