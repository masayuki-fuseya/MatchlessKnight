//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayScene.h
//!
//!	@brief	プレイシーンクラスのヘッダファイル
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef MASABO_PLAY_SCENE
#define MASABO_PLAY_SCENE

// ヘッダファイルの読み込み ================================================
#include "BaseScene.h"
#include "..\Camera\FollowCamera.h"
#include "..\Objects\Character\Player\Player.h"
#include "..\Objects\Character\Enemy\Enemy.h"
#include "..\Factory\EnemyFactory.h"
#include "..\LandShape\LandShape.h"
#include <Effects.h>
#include <memory>


namespace MasaboLib
{
	class PlayScene :public BaseScene
	{
	public:
		// 敵の最大数
		static const int MAX_ENEMY_NUM;
		// クリア目標となる倒した数
		static const int CLEAR_BEAT_NUM;
	private:
		// カメラ
		std::unique_ptr<FollowCamera> m_camera;

		// 床
		std::unique_ptr<Obj3D> m_floor;
		// 空
		std::unique_ptr<Obj3D> m_sky;
		// 壁
		std::unique_ptr<LandShape> m_wall;

		// プレイヤー
		std::unique_ptr<Player> m_player;
		// 敵
		std::vector<std::shared_ptr<Enemy>> m_enemies;
		// 敵生成用のファクトリー
		std::unique_ptr<EnemyFactory> m_enemyFactory;

		// HPバー

		// フレーム数
		float m_frameCount;
		// 制限時間
		int m_timeLimit;
		// 敵を倒した数
		int m_numBeat;
	public:
		PlayScene();
		~PlayScene() {}

		void Initialize();
		void Update(const DX::StepTimer& timer);
		void Render(const DX::StepTimer& timer, DirectX::SpriteBatch* batch, DirectX::SpriteFont* font);
		void Finalize();
	private:
		// プレイヤーと壁の当たり判定
		void CollisionPlayerAndWall();
		// プレイヤーの剣と敵の当たり判定
		void CollisionPlayerSwordAndEnemy();
	};
}

#endif // !MASABO_PLAY_SCENE
