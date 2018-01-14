//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Game.cpp
//!
//!	@brief	�Q�[���N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/12/27
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Game.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace MasaboLib;
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;


//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�E�B���h�E�̉���
//!	@param[in]	�E�B���h�E�̍���
//!
//!	@return		�Ȃ�
//**********************************************************************
Game::Game(int width, int height)
{
	m_width = max(width, 1);
	m_height = max(height, 1);
}



//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::Initialize()
{
	m_window = make_unique<Window>();
	m_window->Initialize(L"MatchlessKnight", m_width, m_height);

	auto graphics = Graphics::GetInstance();
	
	graphics->SetWidth(m_width);
	graphics->SetHeight(m_height);

	// �f�o�C�X�𐶐�����
	graphics->CreateDevice();
	// ���\�[�X�𐶐�����
	graphics->CreateResources();

	// �f�t�H���g�ϐ�timestep���[�h�ȊO�̂��̂��K�v�ȏꍇ�^�C�}�[�ݒ��ύX����
	// �Ⴆ�� 60 FPS�Œ�^�C���X�e�b�v�X�V���W�b�N�ɑ΂��Ă͈ȉ����Ăяo��
    //m_timer.SetFixedTimeStep(true);
    //m_timer.SetTargetElapsedSeconds(1.0 / 60);
	
	m_batch = make_unique<SpriteBatch>(graphics->GetContext());
	m_font = make_unique<SpriteFont>(graphics->GetDevice(), L"myfile.spritefont");
	m_commonStates = make_unique<CommonStates>(graphics->GetDevice());
	m_effectFactory = make_unique<EffectFactory>(graphics->GetDevice());
}



//**********************************************************************
//!	@brief		�Q�[�����[�v�����s����
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
MSG Game::Run()
{
	// ���C�����b�Z�[�W���[�v
	MSG msg = { 0 };

	Initialize();

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// �Q�[�����X�V����
			m_timer.Tick([&]()
			{
				Update(m_timer);
			});
			// �V�[����`�悷��
			m_timer.Tick([&]()
			{
				Render(m_timer);
			});
		}
	}

	Finalize();
	
	return msg;
}



//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�^�C�}�[
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::Update(const StepTimer& timer)
{
}



//**********************************************************************
//!	@brief		�`�悷��
//!
//!	@param[in]	�^�C�}�[
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::Render(const StepTimer& timer)
{
}



//**********************************************************************
//!	@brief		��ʂ��N���A����
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::Clear()
{
	auto graphics = Graphics::GetInstance();

	graphics->GetContext()->ClearRenderTargetView(graphics->GetRenderTargetView().Get(), Colors::Black);
	graphics->GetContext()->ClearDepthStencilView(graphics->GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	graphics->GetContext()->OMSetRenderTargets(1, graphics->GetRenderTargetView().GetAddressOf(), graphics->GetDepthStencilView().Get());

	CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_width), static_cast<float>(m_height));
	graphics->GetContext()->RSSetViewports(1, &viewport);
}



//**********************************************************************
//!	@brief		�o�b�N�o�b�t�@���X�N���[���ɑ���
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::Present()
{
	auto graphics = Graphics::GetInstance();

	HRESULT hr = graphics->GetSwapChain()->Present(1, 0);

	// �f�o�C�X�����Z�b�g���ꂽ�ꍇ�����_�����ď���������K�v������ 
	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
	{
		graphics->OnDeviceLost();
	}
	else
	{
		//graphics->ThrowIfFailed(hr);
	}
}



//**********************************************************************
//!	@brief		�I������������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::Finalize()
{
}



//**********************************************************************
//!	@brief		�Q�[�����A�N�e�B�u�ȃE�B���h�E�ɂȂ������̏���
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::OnActivated()
{
}



//**********************************************************************
//!	@brief		�Q�[�����o�b�N�O���E���h�E�B���h�E�ɂȂ������̏���
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::OnDeactivated()
{
}



//**********************************************************************
//!	@brief		�Q�[�����p���[�T�X�y���f�b�h�ɂȂ������̏���
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::OnSuspending()
{
}



//**********************************************************************
//!	@brief		�Q�[�����p���[���W���[���ɂȂ������̏���
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::OnResuming()
{
	m_timer.ResetElapsedTime();
}



//**********************************************************************
//!	@brief		�Q�[���E�B���h�E�̃T�C�Y���ĕύX���ꂽ���̏���
//!
//!	@param[in]	�E�B���h�E�̉���
//!	@param[in]	�E�B���h�E�̍���
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::OnWindowSizeChanged(int width, int height)
{
    m_width = max(width, 1);
    m_height = max(height, 1);
	
	Graphics::GetInstance()->CreateResources();
}



//**********************************************************************
//!	@brief		�f�t�H���g�E�B���h�E�T�C�Y�ɕύX����(�ŏ��T�C�Y��320*200)
//!
//!	@param[in]	�E�B���h�E�̉���
//!	@param[in]	�E�B���h�E�̍���
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::GetDefaultSize(int& width, int& height) const
{
    width = 800;
    height = 600;
}



//**********************************************************************
//!	@brief		�Q�[�����I���
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::Exit()
{
	PostQuitMessage(WM_QUIT);
}



//**********************************************************************
//!	@brief		FPS��`�悷��
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Game::DrawFPS()
{
	wstring fpsString = L"fps = " + to_wstring((unsigned int)m_timer.GetFramesPerSecond());
	m_font->DrawString(m_batch.get(), fpsString.c_str(), Vector2(0, 0), Colors::White);
}
