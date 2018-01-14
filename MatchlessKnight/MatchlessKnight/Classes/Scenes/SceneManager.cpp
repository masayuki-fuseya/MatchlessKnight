//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	SceneManager.cpp
//!
//!	@brief	シーン管理クラスのヘッダファイル
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "SceneManager.h"
#include "PlayScene.h"

// ネームスペースの省略 ====================================================
using namespace MasaboLib;
using namespace DirectX;
using namespace DX;

// 静的メンバ変数の定義 ====================================================
std::unique_ptr<SceneManager> SceneManager::m_instance = nullptr;


//**********************************************************************
//!	@brief		更新する
//!
//!	@param[in]	ステップタイマー
//!
//!	@return		なし
//**********************************************************************
void SceneManager::Update(const StepTimer& timer)
{
	m_scene[m_id]->Update(timer);
}



//**********************************************************************
//!	@brief		描画する
//!
//!	@param[in]	ステップタイマー,　スプライトバッチ,　スプライトフォント
//!
//!	@return		なし
//**********************************************************************
void SceneManager::Render(const StepTimer& timer, SpriteBatch* batch, SpriteFont* font)
{
	m_scene[m_id]->Render(timer, batch, font);
}



//**********************************************************************
//!	@brief		シーンを登録する
//!
//!	@param[in]	なし
//!
//!	@return		なし
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
//!	@brief		シーンを変更する
//!
//!	@param[in]	シーンID
//!
//!	@return		なし
//**********************************************************************
void SceneManager::ChangeScene(SCENE_ID id)
{
	auto itr = m_scene.find(id);
	// 見つかったら
	if (itr != m_scene.end())
	{
		// シーンの切り替え
		m_id = id;
	}
	// NONEが指定されたらゲームを終了する
	else if (id == SCENE_ID::NONE)
	{
		PostQuitMessage(WM_QUIT);
	}
}



//**********************************************************************
//!	@brief		シーンを初期化する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void SceneManager::ChangePreScene()
{
	m_scene[m_id]->Initialize();
}



//**********************************************************************
//!	@brief		シーンの終了処理をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void SceneManager::ChangePostScene()
{
	m_scene[m_id]->Finalize();
}
