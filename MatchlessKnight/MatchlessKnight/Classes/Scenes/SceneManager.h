//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	SceneManager.h
//!
//!	@brief	�V�[���Ǘ��N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef MASABO_SCENE_MANAGER
#define MASABO_SCENE_MANAGER

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "BaseScene.h"
#include "MasaboLib.h"
#include <map>
#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>


namespace MasaboLib
{
	class SceneManager :public Singleton<SceneManager>
	{
	public:
		enum SCENE_ID
		{
			NONE,		// �Ȃ�(�Q�[���I��)
			LOGO,		// ���S�V�[��
			TITLE,		// �^�C�g���V�[��
			PLAY,		// �v���C�V�[��
			CLEAR,		// �Q�[���N���A�V�[��
			OVER		// �Q�[���I�[�o�[�V�[��
		};
	private:
		friend class Singleton<SceneManager>;

		// �S�ẴV�[����ێ�
		std::map<SCENE_ID, std::unique_ptr<BaseScene>> m_scene;
		// ���݂̃V�[��ID
		SCENE_ID m_id;
	public:
		void Update(const DX::StepTimer& timer);
		void Render(const DX::StepTimer& timer, DirectX::SpriteBatch* batch, DirectX::SpriteFont* font);
		void Finalize();

		// �V�[����o�^����
		void RegisterScene();
		// �V�[����ύX����
		void ChangeScene(SCENE_ID id);
		// �V�[��������������
		void ChangePreScene();
		// �V�[���̏I������������
		void ChangePostScene();
	private:
		SceneManager() {}
	};
}

#endif // !MASABO_SCENE_MANAGER
