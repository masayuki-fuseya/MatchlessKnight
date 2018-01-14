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
			NONE,
			LOGO,
			TITLE,
			PLAY,
			CLEAR,
			OVER
		};
	private:
		friend class Singleton<SceneManager>;

		// �C���X�^���X
		static std::unique_ptr<SceneManager> m_instance;

		// �S�ẴV�[����ێ�
		std::map<SCENE_ID, std::unique_ptr<BaseScene>> m_scene;
		// ���݂̃V�[��ID
		SCENE_ID m_id;
	public:
		// �C���X�^���X���擾����
		static SceneManager* GetInstance()
		{
			// ��������ĂȂ���ΐ�������
			if (!m_instance.get())
			{
				m_instance.reset(new SceneManager());
			}
			return m_instance.get();
		}

		void Update(const MasaboLib::DX::StepTimer& timer);
		void Render(const MasaboLib::DX::StepTimer& timer, DirectX::SpriteBatch* batch, DirectX::SpriteFont* font);

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
