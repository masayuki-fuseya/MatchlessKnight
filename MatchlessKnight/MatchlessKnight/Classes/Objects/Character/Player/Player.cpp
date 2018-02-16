//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Player.cpp
//!
//!	@brief	プレイヤークラスのソースファイル
//!
//!	@date	2017/07/20
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "MasaboLib.h"
#include "Player.h"
#include "PlayerParts\PlayerBody.h"
#include "PlayerParts\PlayerHead.h"
#include "PlayerParts\PlayerLeftCalf.h"
#include "PlayerParts\PlayerLeftFoot.h"
#include "PlayerParts\PlayerLeftForeArm.h"
#include "PlayerParts\PlayerLeftHand.h"
#include "PlayerParts\PlayerLeftThigh.h"
#include "PlayerParts\PlayerLeftUpperArm.h"
#include "PlayerParts\PlayerRightCalf.h"
#include "PlayerParts\PlayerRightFoot.h"
#include "PlayerParts\PlayerRightForeArm.h"
#include "PlayerParts\PlayerRightHand.h"
#include "PlayerParts\PlayerRightThigh.h"
#include "PlayerParts\PlayerRightUpperArm.h"
#include "..\..\..\ADX2\ADX2Le.h"
#include "..\..\..\ADX2\PlayerSE.h"
#include "..\..\..\State\AttackingState.h"
#include "..\..\..\State\StandingState.h"
#include <d3d11.h>
#include <SimpleMath.h>

// ネームスペースの省略 ====================================================
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
Player::Player()
{
}



//**********************************************************************
//!	@brief		初期化する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Player::Initialize()
{
	// ライフを初期化する
	m_life = 100;

	//パーツを追加する
	AddParts();

	// ルートパーツを初期化する
	m_rootParts->Initialize();

	m_scale = Vector3(0.7f);
	m_rotation = Vector3(0.0f, XM_PI, 0.0f);
	m_translation = Vector3(0.0f, 0.0f, 40.0f);

	// 剣を初期化する
	m_sword = make_unique<Sword>();
	m_sword->Initialize(this);

	// ステートパターンを初期化する
	StandingState::GetInstance()->Initialize(this);
	AttackingState::GetInstance()->Initialize(this);

	// 最初は起立状態にする
	ChangeState(StandingState::GetInstance());

	// 初期位置を更新する
	Update();

	// 当たり判定ノードを初期化する
	m_collisionNodeBody.Initialize();
	// プレイヤーを親に設定する
	m_collisionNodeBody.SetParent(this);
	// 座標を設定する
	m_collisionNodeBody.SetTranslation(Vector3(0.0f, 3.0f, 0.0f));
	// 半径を設定する
	m_collisionNodeBody.SetLocalRadius(1.5f);
}



//**********************************************************************
//!	@brief		更新する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Player::Update()
{
	// 現在の状態を更新する
	m_currentState->Execute();

	// 当たり判定ノードを更新する
	m_collisionNodeBody.Update();

	// 剣を振り終えたら起立状態にする
	if (!m_sword->Update(this))
	{
		ChangeState(StandingState::GetInstance());
	}

	// 行列更新する
	CalcMatrix();

	// 全てのパーツを更新する
	m_rootParts->Update(m_scale, m_rotation, m_translation);
}



//**********************************************************************
//!	@brief		描画する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Player::Render()
{
	// 現在の状態を描画する
	m_currentState->Render();
}



//**********************************************************************
//!	@brief		終了処理する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Player::Finalize()
{
	m_rootParts->Finalize();
}



//**********************************************************************
//!	@brief		起立状態の更新をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Player::UpdateStanding()
{
	// キーボードステートを取得する
	Keyboard::State state = MasaboLib::Input::GetInstance()->GetKeyboard()->GetState();

	Vector3 moveV;
	// 左回転
	if (state.IsKeyDown(Keyboard::Keys::Left))
	{
		//float angle = m_rotation.y + 0.02f;
		//m_rotation = Vector3(0.0f, angle, 0.0f);
		m_rotation.y += 0.02f;
	}
	// 右回転
	if (state.IsKeyDown(Keyboard::Keys::Right))
	{
		//float angle = m_rotation.y - 0.02f;
		//m_rotation = Vector3(0.0f, angle, 0.0f);
		m_rotation.y -= 0.02f;
	}
	// 前進
	if (state.IsKeyDown(Keyboard::Keys::Up))
	{
		moveV = Vector3(0.0f, 0.0f, 0.4f);
		// 移動ベクトルを回転させる
		moveV = Vector3::TransformNormal(moveV, GetWorld());
	}
	// 後進
	if (state.IsKeyDown(Keyboard::Keys::Down))
	{
		moveV = Vector3(0.0f, 0.0f, -0.4f);
		// 移動ベクトルを回転させる
		moveV = Vector3::TransformNormal(moveV, GetWorld());
	}
	// 攻撃状態に移行
	if (MasaboLib::Input::GetInstance()->GetKeyboardTracker()->IsKeyPressed(Keyboard::Keys::Z))
	{
		// 剣を振るSEの再生
		ADX2Le::Play(CRI_PLAYER_ATTACK);

		ChangeState(AttackingState::GetInstance());
		m_sword->Wield();
	}

	// 座標移動
	m_translation += moveV;
}



//**********************************************************************
//!	@brief		攻撃状態の更新をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Player::UpdateAttacking()
{
}



//**********************************************************************
//!	@brief		起立状態の描画をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Player::RenderStanding()
{
	// ルートパーツを描画する
	m_rootParts->Render();
	// 剣を描画する
	m_sword->Render();
}



//**********************************************************************
//!	@brief		攻撃状態の描画をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Player::RenderAttacking()
{
	// ルートパーツを描画する
	m_rootParts->Render();
	// 剣を描画する
	m_sword->Render();
}



//**********************************************************************
//!	@brief		攻撃中か
//!
//!	@param[in]	なし
//!
//!	@return		true:攻撃中
//!	@return		false:攻撃していない
//**********************************************************************
bool Player::IsAttack()
{
	// 攻撃中だったらtrueを返す
	if (!m_sword->GetCanWield())
	{
		return true;
	}
	return false;
}



//**********************************************************************
//!	@brief		パーツを追加する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Player::AddParts()
{
	// 体
	m_rootParts = make_shared<Node>(new PlayerBody());

	// 頭
	shared_ptr<INode> body = make_shared<Node>(new PlayerHead());
	m_rootParts->Add(move(body));

	// 右腕
	shared_ptr<INode> rightUpperArm = make_shared<Node>(new PlayerRightUpperArm());
	body->Add(move(rightUpperArm));
	shared_ptr<INode> rightForeArm = make_shared<Node>(new PlayerRightForeArm());
	rightUpperArm->Add(move(rightForeArm));
	rightForeArm->Add(make_shared<Leaf>(new PlayerRightHand()));

	// 左腕
	shared_ptr<INode> leftUpperArm = make_shared<Node>(new PlayerLeftUpperArm());
	body->Add(move(leftUpperArm));
	shared_ptr<INode> leftForeArm = make_shared<Node>(new PlayerLeftForeArm());
	leftUpperArm->Add(move(leftForeArm));
	leftForeArm->Add(make_shared<Leaf>(new PlayerLeftHand()));

	// 右脚
	shared_ptr<INode> rightThigh = make_shared<Node>(new PlayerRightThigh());
	body->Add(move(rightThigh));
	shared_ptr<INode> rightCalf = make_shared<Node>(new PlayerRightCalf());
	rightThigh->Add(move(rightCalf));
	rightCalf->Add(make_shared<Leaf>(new PlayerRightFoot()));

	// 左脚
	shared_ptr<INode> leftThigh = make_shared<Node>(new PlayerLeftThigh());
	body->Add(move(leftThigh));
	shared_ptr<INode> leftCalf = make_shared<Node>(new PlayerLeftCalf());
	leftThigh->Add(move(leftCalf));
	leftCalf->Add(make_shared<Leaf>(new PlayerLeftFoot()));
}
