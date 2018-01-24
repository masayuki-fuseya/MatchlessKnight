//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayScene.cpp
//!
//!	@brief	�v���C�V�[���N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "PlayScene.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace MasaboLib;
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;


//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
PlayScene::PlayScene()
{
}



//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void PlayScene::Initialize()
{
	m_camera = make_unique<DebugCamera>(Graphics::GetInstance()->GetWidth(), Graphics::GetInstance()->GetHeight());

	// �I�u�W�F�N�g�̐ÓI�ϐ�������������
	Obj3D::InitializeStatic(m_camera.get());

	// �t�@�N�g���[�𐶐�����
	m_factory = make_unique<EffectFactory>(Graphics::GetInstance()->GetDevice());
	m_factory->SetDirectory(L"Resources");

	// �e�N�X�`����o�^����
	TextureManager::GetInstance()->Initialize(L"Assets\\CSV\\textureData.csv");
}



//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�^�C�}�[
//!
//!	@return		�Ȃ�
//**********************************************************************
void PlayScene::Update(const StepTimer& timer)
{
	m_camera->Update();
}



//**********************************************************************
//!	@brief		�`�悷��
//!
//!	@param[in]	�^�C�}�[,�@�X�v���C�g�o�b�`,�@�X�v���C�g�t�H���g
//!
//!	@return		�Ȃ�
//**********************************************************************
void PlayScene::Render(const StepTimer& timer, SpriteBatch* batch, SpriteFont* font)
{
	// �r���[�s����擾����
	Matrix view = m_camera->GetView();
	// �v���W�F�N�V�����s����擾����
	Matrix proj = m_camera->GetProj();

	// �e�N�X�`����`�悷��
	TextureManager::GetInstance()->Render(batch);
}



//**********************************************************************
//!	@brief		�I������������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void PlayScene::Finalize()
{
}
