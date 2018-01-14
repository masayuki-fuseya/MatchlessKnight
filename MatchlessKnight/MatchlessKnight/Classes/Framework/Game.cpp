//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Game.cpp
//!
//!	@brief	ゲームクラスのソースファイル
//!
//!	@date	2017/12/27
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "Game.h"

// ネームスペースの省略 ====================================================
using namespace MasaboLib;
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	ウィンドウの横幅
//!	@param[in]	ウィンドウの高さ
//!
//!	@return		なし
//**********************************************************************
Game::Game(int width, int height)
{
	m_width = max(width, 1);
	m_height = max(height, 1);
}



//**********************************************************************
//!	@brief		初期化する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Game::Initialize()
{
	m_window = make_unique<Window>();
	m_window->Initialize(L"MatchlessKnight", m_width, m_height);

	auto graphics = Graphics::GetInstance();
	
	graphics->SetWidth(m_width);
	graphics->SetHeight(m_height);

	// デバイスを生成する
	graphics->CreateDevice();
	// リソースを生成する
	graphics->CreateResources();

	// デフォルト変数timestepモード以外のものが必要な場合タイマー設定を変更する
	// 例えば 60 FPS固定タイムステップ更新ロジックに対しては以下を呼び出す
    //m_timer.SetFixedTimeStep(true);
    //m_timer.SetTargetElapsedSeconds(1.0 / 60);
	
	m_batch = make_unique<SpriteBatch>(graphics->GetContext());
	m_font = make_unique<SpriteFont>(graphics->GetDevice(), L"myfile.spritefont");
	m_commonStates = make_unique<CommonStates>(graphics->GetDevice());
	m_effectFactory = make_unique<EffectFactory>(graphics->GetDevice());
}



//**********************************************************************
//!	@brief		ゲームループを実行する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
MSG Game::Run()
{
	// メインメッセージループ
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
			// ゲームを更新する
			m_timer.Tick([&]()
			{
				Update(m_timer);
			});
			// シーンを描画する
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
//!	@brief		更新する
//!
//!	@param[in]	タイマー
//!
//!	@return		なし
//**********************************************************************
void Game::Update(const StepTimer& timer)
{
}



//**********************************************************************
//!	@brief		描画する
//!
//!	@param[in]	タイマー
//!
//!	@return		なし
//**********************************************************************
void Game::Render(const StepTimer& timer)
{
}



//**********************************************************************
//!	@brief		画面をクリアする
//!
//!	@param[in]	なし
//!
//!	@return		なし
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
//!	@brief		バックバッファをスクリーンに送る
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Game::Present()
{
	auto graphics = Graphics::GetInstance();

	HRESULT hr = graphics->GetSwapChain()->Present(1, 0);

	// デバイスがリセットされた場合レンダラを再初期化する必要がある 
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
//!	@brief		終了処理をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Game::Finalize()
{
}



//**********************************************************************
//!	@brief		ゲームがアクティブなウィンドウになった時の処理
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Game::OnActivated()
{
}



//**********************************************************************
//!	@brief		ゲームがバックグラウンドウィンドウになった時の処理
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Game::OnDeactivated()
{
}



//**********************************************************************
//!	@brief		ゲームがパワーサスペンデッドになった時の処理
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Game::OnSuspending()
{
}



//**********************************************************************
//!	@brief		ゲームがパワーレジュームになった時の処理
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Game::OnResuming()
{
	m_timer.ResetElapsedTime();
}



//**********************************************************************
//!	@brief		ゲームウィンドウのサイズが再変更された時の処理
//!
//!	@param[in]	ウィンドウの横幅
//!	@param[in]	ウィンドウの高さ
//!
//!	@return		なし
//**********************************************************************
void Game::OnWindowSizeChanged(int width, int height)
{
    m_width = max(width, 1);
    m_height = max(height, 1);
	
	Graphics::GetInstance()->CreateResources();
}



//**********************************************************************
//!	@brief		デフォルトウィンドウサイズに変更する(最小サイズは320*200)
//!
//!	@param[in]	ウィンドウの横幅
//!	@param[in]	ウィンドウの高さ
//!
//!	@return		なし
//**********************************************************************
void Game::GetDefaultSize(int& width, int& height) const
{
    width = 800;
    height = 600;
}



//**********************************************************************
//!	@brief		ゲームを終わる
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Game::Exit()
{
	PostQuitMessage(WM_QUIT);
}



//**********************************************************************
//!	@brief		FPSを描画する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Game::DrawFPS()
{
	wstring fpsString = L"fps = " + to_wstring((unsigned int)m_timer.GetFramesPerSecond());
	m_font->DrawString(m_batch.get(), fpsString.c_str(), Vector2(0, 0), Colors::White);
}
