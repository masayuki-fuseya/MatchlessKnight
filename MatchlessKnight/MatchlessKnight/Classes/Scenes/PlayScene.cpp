//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayScene.cpp
//!
//!	@brief	プレイシーンクラスのヘッダファイル
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "PlayScene.h"

// ネームスペースの省略 ====================================================
using namespace MasaboLib;
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
PlayScene::PlayScene()
{
}



//**********************************************************************
//!	@brief		初期化する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void PlayScene::Initialize()
{
	m_camera = make_unique<DebugCamera>(Graphics::GetInstance()->GetWidth(), Graphics::GetInstance()->GetHeight());

	// オブジェクトの静的変数を初期化する
	Obj3D::InitializeStatic(m_camera.get());

	// ファクトリーを生成する
	m_factory = make_unique<EffectFactory>(Graphics::GetInstance()->GetDevice());
	m_factory->SetDirectory(L"Resources");

	// テクスチャを登録する
	TextureManager::GetInstance()->Initialize(L"Assets\\CSV\\textureData.csv");
}



//**********************************************************************
//!	@brief		更新する
//!
//!	@param[in]	タイマー
//!
//!	@return		なし
//**********************************************************************
void PlayScene::Update(const StepTimer& timer)
{
	m_camera->Update();
}



//**********************************************************************
//!	@brief		描画する
//!
//!	@param[in]	タイマー,　スプライトバッチ,　スプライトフォント
//!
//!	@return		なし
//**********************************************************************
void PlayScene::Render(const StepTimer& timer, SpriteBatch* batch, SpriteFont* font)
{
	// ビュー行列を取得する
	Matrix view = m_camera->GetView();
	// プロジェクション行列を取得する
	Matrix proj = m_camera->GetProj();

	// テクスチャを描画する
	TextureManager::GetInstance()->Render(batch);
}



//**********************************************************************
//!	@brief		終了処理をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void PlayScene::Finalize()
{
}
