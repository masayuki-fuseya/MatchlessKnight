//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Enemy.h
//!
//!	@brief	敵クラスのヘッダファイル
//!
//!	@date	2017/07/24
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef ENEMY
#define ENEMY

// ヘッダファイルの読み込み ================================================
#include "..\Character.h"
#include "..\..\..\Collision\CollisionNode.h"
#include <d3d11.h>
#include <SimpleMath.h>


class Enemy :public Character
{
public:
	// 敵の種類
	enum ID
	{
		WEAK	// 弱い敵
	};
private:
	// 移動速度
	static const float SPEED;
	// 1フレームでの角度変化制限
	static const float ANGLE_DELTA_MAX;
	// 寿命
	static const int LIFE_TIME;
	// 誤差
	static const float EPSILON;

	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 追尾対象
	Character* m_target;
	// 残り寿命
	int m_lifeTime;
	// 当たり判定ノード
	SphereNode m_collisionNodeBody;
public:
	Enemy();
	~Enemy() {}

	virtual void Initialize();
	void Update() override;

	// 起立状態の更新をする
	void UpdateStanding() override;
	// 攻撃状態の更新をする
	void UpdateAttacking() override;
	// 起立状態の描画をする
	void RenderStanding() override;
	// 攻撃状態の描画をする
	void RenderAttacking() override;

	// 座標をランダムで決める
	void DesidePos();

	// ゲッター //////////////////////////////////

	// 生きているかを取得する
	const bool GetIsAlive()
	{
		return m_isAlive;
	}
	// 当たり判定球を取得する
	const SphereNode& GetCollisionNodeSphere()
	{
		return m_collisionNodeBody;
	}

	//////////////////////////////////////////////

	// セッター //////////////////////////////////

	// 生きているかを設定する
	void SetIsAlive(const bool isAlive)
	{
		m_isAlive = isAlive;
	}
	// 速度を設定する
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity)
	{
		m_velocity = velocity;
	}
	// 追尾対象を設定する
	void SetTarget(Character* target)
	{
		m_target = target;
	}

	//////////////////////////////////////////////
private:
	// プレイヤーを追尾する準備をする
	void StartPursue(const DirectX::SimpleMath::Vector3& direction);
	// プレイヤーを追尾する
	void Pursue();
};

#endif // !ENEMY
