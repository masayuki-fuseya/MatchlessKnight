//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	TitleScene.cpp
//!
//!	@brief	�^�C�g���V�[���N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/12/16
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "TitleScene.h"
#include "SceneManager.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace MasaboLib;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

// �ÓI�����o�ϐ��̒�` ====================================================
const int TitleScene::MAX_SELECTION_ITEM = 2;


//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
TitleScene::TitleScene()
{
}



//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void TitleScene::Initialize()
{
	m_isPressedSpace = false;
	m_animationTime = 0.0f;
	m_selectionItem = 0;

	// �e�N�X�`���̐����Ɠǂݍ���
	TextureManager::GetInstance()->Initialize(L"Assets\\CSV\\textureData.csv");
	//RECT rect;
	//rect = { 0, 0, 1000, 750 };
	//m_backgroundTexture = std::make_unique<Texture>();
	//m_backgroundTexture->CreateTexture(L"background.png", rect);
	//rect = { 0, 0, 650, 144 };
	//m_titleTexture = std::make_unique<Texture>();
	//m_titleTexture->CreateTexture(L"title.png", rect);
	//rect = { 0, 0, 384, 96 };
	//m_pushSpaceTexture = std::make_unique<Texture>();
	//m_pushSpaceTexture->CreateTexture(L"push_space.png", rect);
	//rect = { 0, 0, 384, 160 };
	//m_selectionItemTexture = std::make_unique<Texture>();
	//m_selectionItemTexture->CreateTexture(L"selection_item.png", rect);
	//rect = { 0, 0, 64, 64 };
	//m_arrowTexture = std::make_unique<Texture>();
	//m_arrowTexture->CreateTexture(L"arrow.png", rect);
}



//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�^�C�}�[
//!
//!	@return		�Ȃ�
//**********************************************************************
void TitleScene::Update(const StepTimer& timer)
{
	auto keyTracker = Input::GetInstance()->GetKeyboardTracker();
	// �X�y�[�X�L�[�������ꂽ��
	if (!m_isPressedSpace && keyTracker->IsKeyPressed(Keyboard::Keys::Space))
	{
		// ���ڂ̑I����Ԃɂ���
		m_isPressedSpace = true;
		// �A�j���[�V�������鎞�Ԃ����Z�b�g����
		m_animationTime = 0.0f;
	}
	// ���ڂ̑I����Ԃ̏ꍇ
	if (m_isPressedSpace)
	{
		// ��L�[�ň��ɃJ�[�\�������炷
		// ��ԏ�ŉ������ꍇ�͈�ԉ��Ɉړ�����
		if (keyTracker->IsKeyPressed(Keyboard::Keys::Up))
		{
			m_selectionItem = (m_selectionItem + MAX_SELECTION_ITEM - 1) % MAX_SELECTION_ITEM;
		}
		// ���L�[�ň���ɃJ�[�\�������炷
		// ��ԉ��ŉ������ꍇ�͈�ԏ�Ɉړ�����
		if (keyTracker->IsKeyPressed(Keyboard::Keys::Down))
		{
			m_selectionItem = (m_selectionItem + 1) % MAX_SELECTION_ITEM;
		}

		// �X�y�[�X�L�[��������Ă����ԂŃG���^�[�L�[�������ꂽ��
		if (keyTracker->IsKeyPressed(Keyboard::Keys::Enter))
		{
			if (m_selectionItem == 0)
			{
				// �v���C�V�[���Ɉړ�����
				SceneManager::GetInstance()->ChangePostScene();
				SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::PLAY);
				SceneManager::GetInstance()->ChangePreScene();
			}
			else
			{
				// �Q�[�����I������
				SceneManager::GetInstance()->ChangePostScene();
				SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::NONE);
			}

			// �A�j���[�V�������鎞�Ԃ����Z�b�g����
			m_animationTime = 0.0f;
		}
	}

	// �w�i�摜�̈ړ�
	//m_bgPos.x += 1.0f;
	//if (m_bgPos.x >= m_backgroundTexture->GetSize().right)
	//{
	//	m_bgPos.x = 0.0f;
	//}
}



//**********************************************************************
//!	@brief		�`�悷��
//!
//!	@param[in]	�^�C�}�[,�@�X�v���C�g�o�b�`,�@�X�v���C�g�t�H���g
//!
//!	@return		�Ȃ�
//**********************************************************************
void TitleScene::Render(const StepTimer& timer, SpriteBatch* batch, SpriteFont* font)
{
	auto graphics = Graphics::GetInstance();
	int width = graphics->GetWidth();
	int height = graphics->GetHeight();

	// �S�Ẵe�N�X�`����`�悷��
	TextureManager::GetInstance()->Render(batch);

	//// �w�i�̕\��
	//m_backgroundTexture->Render(batch, m_bgPos);
	//m_backgroundTexture->Render(batch, Vector2(m_bgPos.x - m_backgroundTexture->GetSize().right, m_bgPos.y));

	//// �^�C�g���̕\��
	//m_titleTexture->Render(batch, Vector2(width / 2.0f - 330, height / 2.0f - 270));
	//
	//// �X�y�[�X�L�[��������Ă��邩
	//if (m_isPressedSpace)
	//{
	//	Vector2 pos(width / 2.0f - 192, height / 2.0f + 118);
	//	m_selectionItemTexture->Render(batch, pos);
	//	m_animationTime += 0.03f;
	//	pos.x = MyMath::Lerp(width / 2.0f - 270, width / 2.0f - 290, m_animationTime);
	//	pos.y = height / 2.0f + 140 + 64 * m_selectionItem;
	//	m_arrowTexture->Render(batch, pos);
	//}
	//else
	//{
	//	m_animationTime += 0.015f;
	//	Vector4 color(1.0f, 1.0f, 1.0f, 1.0f);
	//	color.w = MyMath::Lerp(1.0f, 0.0f, m_animationTime);
	//	m_pushSpaceTexture->Render(batch, Vector2(width / 2.0f - 192, height / 2.0f + 150), color);
	//}
}



//**********************************************************************
//!	@brief		�I����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void TitleScene::Finalize()
{
}
