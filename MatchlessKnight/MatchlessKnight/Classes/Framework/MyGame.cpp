//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	MyGame.cpp
//!
//!	@brief	�����̃Q�[���N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/12/27
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "MyGame.h"
#include "..\Scenes\SceneManager.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace MasaboLib;
using namespace std;
using namespace DirectX;
using namespace DX;


//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�E�B���h�E�̉���
//!	@param[in]	�E�B���h�E�̍���
//!
//!	@return		�Ȃ�
//**********************************************************************
MyGame::MyGame(int width, int height)
	: Game(width, height)
{
}



//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void MyGame::Initialize()
{
	Game::Initialize();

	// �L�[�{�[�h�𐶐�����
	Input::GetInstance()->CreateKeyboard();
	// �}�E�X�𐶐�����
	Input::GetInstance()->CreateMouse();

	// �V�[����o�^����
	SceneManager::GetInstance()->RegisterScene();
	// �����V�[����ݒ肵�Ă��珉��������
	SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::PLAY);
	SceneManager::GetInstance()->ChangePreScene();
}



//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�^�C�}�[
//!
//!	@return		�Ȃ�
//**********************************************************************
void MyGame::Update(const StepTimer& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	Input::GetInstance()->Update();

	// �V�[���N���X���X�V����
	SceneManager::GetInstance()->Update(timer);
}



//**********************************************************************
//!	@brief		�`�悷��
//!
//!	@param[in]	�^�C�}�[
//!
//!	@return		�Ȃ�
//**********************************************************************
void MyGame::Render(const StepTimer& timer)
{
	// �ŏ��̍X�V�̑O�͉����`�悵�Ȃ��悤�ɂ���
	if (timer.GetFrameCount() == 0)
	{
		return;
	}

	auto graphics = Graphics::GetInstance();

	// ��ʂ��N���A����
	Clear();

	m_batch->Begin();

	// �V�[���N���X��`�悷��
	SceneManager::GetInstance()->Render(timer, m_batch.get(), m_font.get());

	// FPS��`�悷��
	DrawFPS();

	m_batch->End();

	// �o�b�N�o�b�t�@���X�N���[���ɑ���
	Present();
}



//**********************************************************************
//!	@brief		�I������������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void MyGame::Finalize()
{
	Game::Finalize();
}
