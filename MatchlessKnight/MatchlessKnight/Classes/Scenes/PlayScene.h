//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayScene.h
//!
//!	@brief	�v���C�V�[���N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef MASABO_PLAY_SCENE
#define MASABO_PLAY_SCENE

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "BaseScene.h"
#include <Effects.h>
#include <memory>


namespace MasaboLib
{
	class PlayScene :public BaseScene
	{
	private:
		// �J����
		std::unique_ptr<DebugCamera> m_camera;
		// �G�t�F�N�g�t�@�N�g���[
		std::unique_ptr<DirectX::EffectFactory> m_factory;
	public:
		PlayScene();
		~PlayScene() {}

		void Initialize();
		void Update(const DX::StepTimer& timer);
		void Render(const DX::StepTimer& timer, DirectX::SpriteBatch* batch, DirectX::SpriteFont* font);
		void Finalize();
	};
}

#endif // !MASABO_PLAY_SCENE
