//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	MyGame.cpp
//!
//!	@brief	自分のゲームクラスのソースファイル
//!
//!	@date	2017/12/27
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "MyGame.h"
#include "..\Scenes\SceneManager.h"

// ネームスペースの省略 ====================================================
using namespace MasaboLib;
using namespace std;
using namespace DirectX;
using namespace DX;


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	ウィンドウの横幅
//!	@param[in]	ウィンドウの高さ
//!
//!	@return		なし
//**********************************************************************
MyGame::MyGame(int width, int height)
	: Game(width, height)
{
}



//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void MyGame::Initialize()
{
	Game::Initialize();

	// キーボードを生成する
	Input::GetInstance()->CreateKeyboard();
	// マウスを生成する
	Input::GetInstance()->CreateMouse();

	// シーンを登録する
	SceneManager::GetInstance()->RegisterScene();
	// 初期シーンを設定してから初期化する
	SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::PLAY);
	SceneManager::GetInstance()->ChangePreScene();
}



//**********************************************************************
//!	@brief		更新する
//!
//!	@param[in]	タイマー
//!
//!	@return		なし
//**********************************************************************
void MyGame::Update(const StepTimer& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	Input::GetInstance()->Update();

	// シーンクラスを更新する
	SceneManager::GetInstance()->Update(timer);
}



//**********************************************************************
//!	@brief		描画する
//!
//!	@param[in]	タイマー
//!
//!	@return		なし
//**********************************************************************
void MyGame::Render(const StepTimer& timer)
{
	// 最初の更新の前は何も描画しないようにする
	if (timer.GetFrameCount() == 0)
	{
		return;
	}

	auto graphics = Graphics::GetInstance();

	// 画面をクリアする
	Clear();

	m_batch->Begin();

	// シーンクラスを描画する
	SceneManager::GetInstance()->Render(timer, m_batch.get(), m_font.get());

	// FPSを描画する
	DrawFPS();

	m_batch->End();

	// バックバッファをスクリーンに送る
	Present();
}



//**********************************************************************
//!	@brief		終了処理をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void MyGame::Finalize()
{
	Game::Finalize();
}
