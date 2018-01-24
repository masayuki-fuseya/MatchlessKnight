//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	TitleScene.cpp
//!
//!	@brief	タイトルシーンクラスのソースファイル
//!
//!	@date	2017/12/16
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "TitleScene.h"
#include "SceneManager.h"

// ネームスペースの省略 ====================================================
using namespace MasaboLib;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

// 静的メンバ変数の定義 ====================================================
const int TitleScene::MAX_SELECTION_ITEM = 2;


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
TitleScene::TitleScene()
{
}



//**********************************************************************
//!	@brief		初期化する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void TitleScene::Initialize()
{
	m_isPressedSpace = false;
	m_animationTime = 0.0f;
	m_selectionItem = 0;

	// テクスチャの生成と読み込み
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
//!	@brief		更新する
//!
//!	@param[in]	タイマー
//!
//!	@return		なし
//**********************************************************************
void TitleScene::Update(const StepTimer& timer)
{
	auto keyTracker = Input::GetInstance()->GetKeyboardTracker();
	// スペースキーが押されたら
	if (!m_isPressedSpace && keyTracker->IsKeyPressed(Keyboard::Keys::Space))
	{
		// 項目の選択状態にする
		m_isPressedSpace = true;
		// アニメーションする時間をリセットする
		m_animationTime = 0.0f;
	}
	// 項目の選択状態の場合
	if (m_isPressedSpace)
	{
		// 上キーで一つ上にカーソルをずらす
		// 一番上で押した場合は一番下に移動する
		if (keyTracker->IsKeyPressed(Keyboard::Keys::Up))
		{
			m_selectionItem = (m_selectionItem + MAX_SELECTION_ITEM - 1) % MAX_SELECTION_ITEM;
		}
		// 下キーで一つ下にカーソルをずらす
		// 一番下で押した場合は一番上に移動する
		if (keyTracker->IsKeyPressed(Keyboard::Keys::Down))
		{
			m_selectionItem = (m_selectionItem + 1) % MAX_SELECTION_ITEM;
		}

		// スペースキーが押されている状態でエンターキーが押されたら
		if (keyTracker->IsKeyPressed(Keyboard::Keys::Enter))
		{
			if (m_selectionItem == 0)
			{
				// プレイシーンに移動する
				SceneManager::GetInstance()->ChangePostScene();
				SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::PLAY);
				SceneManager::GetInstance()->ChangePreScene();
			}
			else
			{
				// ゲームを終了する
				SceneManager::GetInstance()->ChangePostScene();
				SceneManager::GetInstance()->ChangeScene(SceneManager::SCENE_ID::NONE);
			}

			// アニメーションする時間をリセットする
			m_animationTime = 0.0f;
		}
	}

	// 背景画像の移動
	//m_bgPos.x += 1.0f;
	//if (m_bgPos.x >= m_backgroundTexture->GetSize().right)
	//{
	//	m_bgPos.x = 0.0f;
	//}
}



//**********************************************************************
//!	@brief		描画する
//!
//!	@param[in]	タイマー,　スプライトバッチ,　スプライトフォント
//!
//!	@return		なし
//**********************************************************************
void TitleScene::Render(const StepTimer& timer, SpriteBatch* batch, SpriteFont* font)
{
	auto graphics = Graphics::GetInstance();
	int width = graphics->GetWidth();
	int height = graphics->GetHeight();

	// 全てのテクスチャを描画する
	TextureManager::GetInstance()->Render(batch);

	//// 背景の表示
	//m_backgroundTexture->Render(batch, m_bgPos);
	//m_backgroundTexture->Render(batch, Vector2(m_bgPos.x - m_backgroundTexture->GetSize().right, m_bgPos.y));

	//// タイトルの表示
	//m_titleTexture->Render(batch, Vector2(width / 2.0f - 330, height / 2.0f - 270));
	//
	//// スペースキーが押されているか
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
//!	@brief		終了処理する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void TitleScene::Finalize()
{
}
