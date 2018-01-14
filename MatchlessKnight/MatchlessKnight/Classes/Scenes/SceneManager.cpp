//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	SceneManager.cpp
//!
//!	@brief	�V�[���Ǘ��N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "SceneManager.h"
#include "PlayScene.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace MasaboLib;
using namespace DirectX;
using namespace DX;

// �ÓI�����o�ϐ��̒�` ====================================================
std::unique_ptr<SceneManager> SceneManager::m_instance = nullptr;


//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�X�e�b�v�^�C�}�[
//!
//!	@return		�Ȃ�
//**********************************************************************
void SceneManager::Update(const StepTimer& timer)
{
	m_scene[m_id]->Update(timer);
}



//**********************************************************************
//!	@brief		�`�悷��
//!
//!	@param[in]	�X�e�b�v�^�C�}�[,�@�X�v���C�g�o�b�`,�@�X�v���C�g�t�H���g
//!
//!	@return		�Ȃ�
//**********************************************************************
void SceneManager::Render(const StepTimer& timer, SpriteBatch* batch, SpriteFont* font)
{
	m_scene[m_id]->Render(timer, batch, font);
}



//**********************************************************************
//!	@brief		�V�[����o�^����
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void SceneManager::RegisterScene()
{
	m_scene[SCENE_ID::LOGO];
	m_scene[SCENE_ID::TITLE];
	m_scene[SCENE_ID::PLAY] = std::make_unique<PlayScene>();
	m_scene[SCENE_ID::CLEAR];
	m_scene[SCENE_ID::OVER];
}



//**********************************************************************
//!	@brief		�V�[����ύX����
//!
//!	@param[in]	�V�[��ID
//!
//!	@return		�Ȃ�
//**********************************************************************
void SceneManager::ChangeScene(SCENE_ID id)
{
	auto itr = m_scene.find(id);
	// ����������
	if (itr != m_scene.end())
	{
		// �V�[���̐؂�ւ�
		m_id = id;
	}
	// NONE���w�肳�ꂽ��Q�[�����I������
	else if (id == SCENE_ID::NONE)
	{
		PostQuitMessage(WM_QUIT);
	}
}



//**********************************************************************
//!	@brief		�V�[��������������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void SceneManager::ChangePreScene()
{
	m_scene[m_id]->Initialize();
}



//**********************************************************************
//!	@brief		�V�[���̏I������������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void SceneManager::ChangePostScene()
{
	m_scene[m_id]->Finalize();
}
