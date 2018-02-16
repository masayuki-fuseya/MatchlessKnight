//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Sword.cpp
//!
//!	@brief	剣クラスのソースファイル
//!
//!	@date	2017/07/25
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "Sword.h"

// ネームスペースの省略 ====================================================
using namespace DirectX;
using namespace DirectX::SimpleMath;

// 静的メンバ変数の定義 ====================================================
const int Sword::MAX_RECOVERY_TIME = 20;


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
Sword::Sword()
	: m_time(0.0f)
	, m_recoveryTime(0)
	, m_canWield(true)
{
}



//**********************************************************************
//!	@brief		初期化する
//!
//!	@param[in]	プレイヤー
//!
//!	@return		なし
//**********************************************************************
void Sword::Initialize(Player* player)
{
	// モデルを読み込む
	LoadModel(L"KnightSword");

	// プレイヤーを親として設定する
	m_parent = player;

	// 当たり判定ノードを初期化する
	m_collisionNode.Initialize();
	// 剣を親に設定する
	m_collisionNode.SetParent(this);
	// 座標を設定する
	m_collisionNode.SetTranslation(Vector3(-2.0f, 3.0f, 1.5f));
	// 半径を設定する
	m_collisionNode.SetLocalRadius(2.0f);
}



//**********************************************************************
//!	@brief		更新する
//!
//!	@param[in]	プレイヤー
//!
//!	@return		true:起立状態
//!	@return		false:剣を振り終わった
//**********************************************************************
bool Sword::Update(Player* player)
{
	// m_endTransの位置まで行ったら
	if (m_translation == m_endTrans)
	{
		// 剣を振り終わっていたら
		if (!m_canWield)
		{
			// 一定時間だけ再度剣を振れないようにする
			m_recoveryTime++;
			if (m_recoveryTime >= MAX_RECOVERY_TIME)
			{
				// 初期化する
				m_translation = Vector3::Zero;
				m_startTrans = Vector3::Zero;
				m_endTrans = Vector3::Zero;
				m_canWield = true;
			}
		}
	}
	else
	{
		if (m_time < 1.0f)
		{
			// m_startTransからm_endTransまで線形補間する
			m_time += 0.05f;
			m_translation = Vector3::Lerp(m_startTrans, m_endTrans, m_time);
		}
		else
		{
			// 線形補間終了
			m_time = 1.0f;
			m_translation = m_endTrans;
		}
	}

	Obj3D::Update();

	// 当たり判定ノードを更新する
	m_collisionNode.Update();

	if (m_canWield)
		return false;

	return true;
}



//**********************************************************************
//!	@brief		剣を振る
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Sword::Wield()
{
	// 剣を振ってる途中だったら再度振れない
	if (!m_canWield)
		return;

	// 剣の補間用変数を設定する
	m_translation = Vector3::Zero;
	m_startTrans = Vector3(0.0f, 1.6f, 0.0f);
	m_endTrans = Vector3(3.2f, -1.0f, 0.0f);
	m_time = 0.0f;
	m_recoveryTime = 0;
	m_canWield = false;
}
