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

// 静的メンバ変数の定義 ====================================================
const int PlayScene::MAX_ENEMY_NUM = 100;
const int PlayScene::CLEAR_BEAT_NUM = 30;


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
	// テクスチャを登録する
	TextureManager::GetInstance()->Initialize(L"Assets\\CSV\\TitleTexture.csv");

	// カメラを生成する
	m_camera = make_unique<FollowCamera>(Graphics::GetInstance()->GetWidth(), Graphics::GetInstance()->GetHeight());

	// オブジェクトの静的変数を初期化する
	Obj3D::InitializeStatic(m_camera.get());

	// 地形を初期化する
	LandShapeCommonDef def;
	def.camera = m_camera.get();
	LandShape::InitializeCommon(def);

	// 床を生成する
	m_floor = make_unique<Obj3D>();
	m_floor->LoadModel(L"floor");
	m_floor->DisableLighting();

	// 空を生成する
	m_sky = make_unique<Obj3D>();
	m_sky->LoadModel(L"skydome");
	m_sky->DisableLighting();

	// 壁を生成する
	m_wall = make_unique<LandShape>();
	m_wall->Initialize(L"wall", L"wall");
	m_wall->DisableLighting();

	// プレイヤーを生成する
	m_player = make_unique<Player>();
	m_player->Initialize();

	// プレイヤーをカメラの追従対象にする
	m_camera->SetTarget(m_player.get());
	m_camera->Initialize();

	// 敵の生成する最大数を設定する
	m_enemies.reserve(MAX_ENEMY_NUM);

	// 敵生成用のファクトリーを初期化する
	m_enemyFactory = make_unique<EnemyFactory>();
	m_enemyFactory->Initialize();

	m_frameCount = 0.0f;
	m_timeLimit = 1800;
	m_numBeat = 0;

	m_isStart = false;
	m_isClear = false;
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
	// カメラを更新する
	m_camera->Update();

	// 床を更新する
	m_floor->Update();
	// 空を更新する
	m_sky->Update();
	// 壁を更新する
	m_wall->Update();

	// まだスタートしていなければ
	if (!m_isStart)
	{
		// 3秒経ったらスタート
		m_frameCount += (float)timer.GetElapsedSeconds();
		if (m_frameCount >= 3.0f)
		{
			m_isStart = true;
			m_frameCount = 0.0f;
		}

		return;
	}

	// プレイヤーを更新する
	m_player->Update();

	m_frameCount += (float)timer.GetElapsedSeconds();
	if ((int)(m_frameCount * 10) % 10 == 0)
	{
		// 敵がまだ生成できるなら生成する
		shared_ptr<Enemy> enemy;
		enemy = m_enemyFactory->Reallocate(Enemy::ID::WEAK);
		if (enemy)
		{
			m_enemies.push_back(enemy);
			// 追尾対象をプレイヤーに設定する
			(m_enemies.end() - 1)->get()->SetTarget(m_player.get());
		}

		//m_frameCount = 0.0f;
	}

	// 敵を更新する
	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr)
	{
		(*itr)->Update();
	}

	// 当たり判定 ////////////////////////////////////

	// 壁と自機の当たり判定
	CollisionPlayerAndWall();

	// プレイヤーの剣と敵の当たり判定
	CollisionPlayerSwordAndEnemy();

	//////////////////////////////////////////////////

	// 敵が生きていなければ消す
	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); )
	{
		if (!(*itr)->GetIsAlive())
		{
			itr = m_enemies.erase(itr);
		}
		else
		{
			++itr;
		}
	}

	// 0秒より下回らないようにする
	m_timeLimit > 0 ? m_timeLimit-- : 0;

	// 時間切れでクリア目標以上だったら
	if (m_timeLimit == 0 && m_numBeat >= CLEAR_BEAT_NUM)
	{
		m_isClear = true;
	}
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
	// 空を描画する
	m_sky->Render();
	// 床を描画する
	m_floor->Render();
	// 壁を描画する
	m_wall->Draw();

	// プレイヤーを描画する
	m_player->Render();
	// 敵を描画する
	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr)
	{
		(*itr)->Render();
	}

	// 制限時間を描画する
	RenderTimeLimit(batch, font);

	// 倒した敵の数を描画する
	wstring w = L"Enemy Kill:" + to_wstring(m_numBeat);
	font->DrawString(batch, w.c_str(), Vector2(40.0f, 40.0f), Colors::White, 0.0f, g_XMZero, 1.5f);

	// カウントダウンの表示
	if (!m_isStart)
	{
		int width = Graphics::GetInstance()->GetWidth();
		int height = Graphics::GetInstance()->GetHeight();

		int second = 3 - (int)m_frameCount;
		w = to_wstring(second);
		font->DrawString(batch, w.c_str(), Vector2(width / 2.0f - 70.0f, height / 2.0f - 100.0f), Colors::DeepSkyBlue, 0.0f, g_XMZero, 8.0f);
	}

	// 始まって1秒だけスタートを表示する
	if (m_isStart && m_frameCount <= 1.0f)
	{
		int width = Graphics::GetInstance()->GetWidth();
		int height = Graphics::GetInstance()->GetHeight();

		font->DrawString(batch, L"S T A R T", Vector2(width / 2.0f - 420.0f, height / 2.0f - 100.0f), Colors::DeepSkyBlue, 0.0f, g_XMZero, 8.0f);
	}

	// リザルト表示 /////////////////////////////////

	// クリアしていたら
	if (m_isClear)
	{
		// ゲームクリアを表示する
		font->DrawString(batch, L"GAME CLEAR!!", Vector2(Graphics::GetInstance()->GetWidth() / 2.0f - 230.0f,
			Graphics::GetInstance()->GetHeight() / 2.0f - 50.0f), Colors::Gold, 0.0f, g_XMZero, 3.0f);
	}
	else if (m_timeLimit == 0)
	{
		// ゲームオーバーを表示する
		font->DrawString(batch, L"GAME OVER", Vector2(Graphics::GetInstance()->GetWidth() / 2.0f - 200.0f,
			Graphics::GetInstance()->GetHeight() / 2.0f - 50.0f), Colors::Red, 0.0f, g_XMZero, 3.0f);
	}

	/////////////////////////////////////////////////

	// テクスチャを描画する
	//TextureManager::GetInstance()->Render(batch);
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
	m_player->Finalize();
}



//**********************************************************************
//!	@brief		プレイヤーと壁の当たり判定をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void PlayScene::CollisionPlayerAndWall()
{
	Sphere sphere = m_player->GetCollisionNodeSphere();
	Vector3 trans = m_player->GetTranslation();
	// 当たり判定球の中心からプレイヤーの足元へのベクトル
	Vector3 sphere2player = trans - sphere.m_center;

	// 排斥ベクトル
	Vector3 reject;
	// 地形と球の当たり判定
	if (m_wall->IntersectSphere(sphere, &reject))
	{
		// めり込み分押し出す
		sphere.m_center += reject;
	}

	// 押し出された座標を設定する
	m_player->SetTranslation(sphere.m_center += sphere2player);

	// ワールド行列だけずらす
	m_player->CalcMatrix();
}



//**********************************************************************
//!	@brief		プレイヤーの剣と敵の当たり判定をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void PlayScene::CollisionPlayerSwordAndEnemy()
{
	// 攻撃中だったら
	if (m_player->IsAttack())
	{
		Sphere swordSphere = m_player->GetSword()->GetCollisionNode();
		for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr)
		{
			Sphere enemySphere = (*itr)->GetCollisionNodeSphere();

			// 球同士の当たり判定
			if (CheckSphere2Sphere(swordSphere, enemySphere))
			{
				// 敵の体力を減らす
				(*itr)->ReduceLife(10);

				// 敵が死んでいたら
				if (!(*itr)->GetIsAlive())
				{
					// 制限時間内で未クリアだったら敵を倒した数を増やす
					if (m_timeLimit != 0)
					{
						m_numBeat++;
					}
				}
			}
		}
	}
}



//**********************************************************************
//!	@brief		制限時間を描画する
//!
//!	@param[in]	スプライトバッチ,　スプライトフォント
//!
//!	@return		なし
//**********************************************************************
void PlayScene::RenderTimeLimit(SpriteBatch* batch, SpriteFont* font)
{
	// 秒数
	int minute = m_timeLimit / 3600;
	// 分数
	int second = (m_timeLimit % 3600) / 60;
	// 00:00の表記にする
	wstring w;
	// 10未満だったら数字の前に0を付け足す
	minute >= 10 ? w = to_wstring(minute) : w = L"0" + to_wstring(minute);
	w = w + L":";
	second >= 10 ? w = w + to_wstring(second) : w = w + L"0" + to_wstring(second);

	// 制限時間を表示する
	font->DrawString(batch, w.c_str(), Vector2(40.0f, 10.0f), Colors::White, 0.0f, g_XMZero, 1.5f);
}
