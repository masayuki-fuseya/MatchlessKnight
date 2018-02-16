//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Sword.h
//!
//!	@brief	剣クラスのヘッダファイル
//!
//!	@date	2017/07/25
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef SWORD
#define SWORD

// ヘッダファイルの読み込み ================================================
#include "MasaboLib.h"
#include "..\Character\Player\Player.h"
#include "..\..\Collision\CollisionNode.h"
#include <d3d11.h>
#include <Model.h>
#include <memory>
#include <SimpleMath.h>


class Player;


class Sword :public MasaboLib::Obj3D
{
private:
	// 硬直時間が解除されるまでの時間
	static const int MAX_RECOVERY_TIME;

	// 補間する最初の座標
	DirectX::SimpleMath::Vector3 m_startTrans;
	// 保管する最後の座標
	DirectX::SimpleMath::Vector3 m_endTrans;
	// 当たり判定ノード
	SphereNode m_collisionNode;
	// 補間用の時間
	float m_time;
	// 攻撃した後の硬直時間が回復するまでカウントする時間
	int m_recoveryTime;
	// 振ることができるか
	bool m_canWield;
public:
	Sword();
	~Sword() {}

	void Initialize(Player* player);
	bool Update(Player* player);

	// 剣を振る
	void Wield();

	// ゲッター //////////////////////////////////

	// 当たり判定ノードを取得する
	const SphereNode& GetCollisionNode()
	{
		return m_collisionNode;
	}
	// 振ることができるかを取得する
	const bool GetCanWield()
	{
		return m_canWield;
	}

	//////////////////////////////////////////////
};

#endif // !SWORD
