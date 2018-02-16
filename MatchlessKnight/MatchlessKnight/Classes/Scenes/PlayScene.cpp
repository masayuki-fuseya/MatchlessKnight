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

	// プレイヤーを更新する
	m_player->Update();

	m_frameCount += (float)timer.GetElapsedSeconds();
	if (m_frameCount >= 0.2f)
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

		m_frameCount = 0.0f;
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
		//m_isClear = true;
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

	// 倒した敵の数を描画する

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
