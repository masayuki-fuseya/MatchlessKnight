//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Player.h
//!
//!	@brief	プレイヤークラスのヘッダファイル
//!
//!	@date	2017/07/20
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER
#define PLAYER

// ヘッダファイルの読み込み ================================================
#include "..\Character.h"
#include "..\..\Sword\Sword.h"
#include "..\..\..\Collision\CollisionNode.h"
#include "..\..\..\Composite\CompositeVisitor.h"
#include "..\..\..\State\State.h"
#include <memory>


class INode;
class Sword;


class Player :public Character
{
private:
	// プレイヤーパーツの基パーツ
	std::shared_ptr<INode> m_rootParts;
	// 剣
	std::unique_ptr<Sword> m_sword;
	// 当たり判定ノード
	SphereNode m_collisionNodeBody;
public:
	// パーツ
	enum PARTS
	{
		HEAD,				// 頭
		BODY,				// 体
		RIGHT_UPPER_ARM,	// 右上腕
		RIGHT_FORE_ARM,		// 右前腕部
		RIGHT_HAND,			// 右手
		LEFT_UPPER_ARM,		// 左上腕
		LEFT_FORE_ARM,		// 左前腕部
		LEFT_HAND,			// 左手
		RIGHT_THIGH,		// 右大腿
		RIGHT_CALF,			// 右ふくらはぎ
		RIGHT_FOOT,			// 右足
		LEFT_THIGH,			// 左大腿
		LEFT_CALF,			// 左ふくらはぎ
		LEFT_FOOT,			// 左足

		PARTS_NUM			// 全体の数
	};

	Player();
	~Player() {}

	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	void Finalize();

	// 起立状態の更新をする
	void UpdateStanding() override;
	// 攻撃状態の更新をする
	void UpdateAttacking() override;
	// 起立状態の描画をする
	void RenderStanding() override;
	// 攻撃状態の描画をする
	void RenderAttacking() override;

	// 攻撃中か
	bool IsAttack();

	// ゲッター //////////////////////////////////

	// ルートパーツを取得する
	INode* GetRootParts()
	{
		return m_rootParts.get();
	}
	// 剣を取得する
	Sword* GetSword()
	{
		return m_sword.get();
	}
	// 当たり判定ノードを取得する
	const SphereNode& GetCollisionNodeSphere()
	{
		return m_collisionNodeBody;
	}

	//////////////////////////////////////////////
private:
	// プレイヤーパーツを追加する
	void AddParts();
};

#endif // !PLAYER
