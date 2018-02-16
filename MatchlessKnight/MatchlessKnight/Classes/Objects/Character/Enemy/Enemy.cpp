//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Enemy.cpp
//!
//!	@brief	敵クラスのソースファイル
//!
//!	@date	2017/07/24
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "Enemy.h"
#include "..\..\..\ADX2\ADX2Le.h"
#include "..\..\..\ADX2\PlayerSE.h"

// ネームスペースの省略 ====================================================
using namespace DirectX;
using namespace DirectX::SimpleMath;

// 静的メンバ変数の定義 ====================================================
const float Enemy::SPEED = 0.1f;
const float Enemy::ANGLE_DELTA_MAX = DirectX::XMConvertToRadians(30.0f);
const int Enemy::LIFE_TIME = 120;
const float Enemy::EPSILON = 1.0e-2f;


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
Enemy::Enemy()
	: m_target(nullptr)
	, m_lifeTime(0)
{
	m_isAlive = false;
}



//**********************************************************************
//!	@brief		初期化する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Enemy::Initialize()
{
	// 座標を決める
	DesidePos();

	// プレイヤーの追尾を開始する
	StartPursue(Vector3(0.01f, 0.0f, 0.01f));

	// 当たり判定ノードを初期化する
	m_collisionNodeBody.Initialize();
	// 敵を親に設定する
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
void Enemy::Update()
{
	// プレイヤーを追尾する
	Pursue();

	// 座標移動
	m_translation += m_velocity;

	// 当たり判定ノードの更新をする
	m_collisionNodeBody.Update();

	// 行列更新する
	CalcMatrix();
}



//**********************************************************************
//!	@brief		起立状態の更新をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Enemy::UpdateStanding()
{
}



//**********************************************************************
//!	@brief		攻撃状態の更新をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Enemy::UpdateAttacking()
{
}



//**********************************************************************
//!	@brief		起立状態の描画をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Enemy::RenderStanding()
{
}



//**********************************************************************
//!	@brief		攻撃状態の描画をする
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Enemy::RenderAttacking()
{
}



//**********************************************************************
//!	@brief		座標をランダムで決める
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Enemy::DesidePos()
{
	// 壁の前のランダムな位置に配置
	float x = (float)(rand() % 80 - 40);
	float z = -45.0f;
	m_translation = Vector3(x, 0, z);
}



//**********************************************************************
//!	@brief		プレイヤーを追尾する準備をする
//!
//!	@param[in]	速度の向き
//!
//!	@return		なし
//**********************************************************************
void Enemy::StartPursue(const Vector3& direction)
{
	// 寿命
	m_lifeTime = LIFE_TIME;
	// 速度
	m_velocity = direction;
	m_velocity.Normalize();
	m_velocity *= SPEED;

	// 初期の回転情報を進行方向から算出する
	{
		Vector3 Zminus = -Vector3::UnitZ;
		// 内積の公式から、2ベクトルの内積が角度差のコサイン値
		// A: デフォルトの進行方向ベクトル(Zマイナス方向)
		// B: 誘導対象の方向ベクトル
		float cosine = Zminus.Dot(direction);
		// 2ベクトル角度差<ラジアン>を求める
		float delta = acosf(cosine);

		// 2ベクトルの角度差がほとんどなければ
		if (delta > EPSILON)
		{
			// AからBへ回す際の回転軸を外積で求める
			Vector3 axis = Zminus.Cross(direction);
			axis.Normalize();
			// 指定した回転軸周りに指定ラジアンだけ回すクォータニオンを得る
			Quaternion q = Quaternion::CreateFromAxisAngle(axis, delta);
			// 初期回転をセット
			m_quaternion = q;
			m_useQuaternion = true;
		}
	}
}



//**********************************************************************
//!	@brief		プレイヤーを追尾する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Enemy::Pursue()
{
	bool death = false;

	if (m_lifeTime > 0)
	{
		if (--m_lifeTime <= 0)
		{
			//death = true;
		}
	}

	// 誘導対象がいれば
	if (!death && m_target)
	{
		// 現在の進行方向ベクトルを求める（単に速度ベクトルを正規化したもの）
		Vector3 moveDir;
		m_velocity.Normalize(moveDir);

		// 座標の差分ベクトルを求める
		Vector3 targetDir = m_target->GetTranslation() - GetTranslation();
		float distance = targetDir.Length();
		if (distance >= 1.0f)
		{
			targetDir.Normalize();

			// 内積の公式から、2ベクトルの内積が角度差のコサイン値
			// A: 現在の進行方向ベクトル
			// B: 誘導対象の方向ベクトル
			float cosine = moveDir.Dot(targetDir);
			// 2ベクトル角度差<ラジアン>を求める
			float delta = acosf(cosine);
			// 2ベクトルの角度差がほとんどなければ
			if (delta > EPSILON)
			{
				// このフレームでの回転角<ラジアン>を決定
				float angle;
				if (distance <= 2.0f)
				{// 距離が近いと誘導性能があがる
					angle = min(delta, ANGLE_DELTA_MAX);
				}
				else
				{
					// 寿命が短いと誘導瀬能があがる
					float rate = 1.0f - (float)m_lifeTime / LIFE_TIME;
					angle = min(delta, rate * ANGLE_DELTA_MAX);
				}

				// AからBへ回す際の回転軸を外積で求める
				Vector3 axis = moveDir.Cross(targetDir);
				axis.Normalize();
				// 指定した回転軸周りに指定ラジアンだけ回すクォータニオンを得る
				Quaternion qDelta = Quaternion::CreateFromAxisAngle(axis, angle);
				// 今回の回転分を反映
				m_quaternion *= qDelta;
				m_useQuaternion = true;
				// 速度ベクトルを回転
				m_velocity = Vector3::Transform(Vector3(0, 0, SPEED), m_quaternion);
			}
		}
		else
		{
			// 追跡終了
			death = true;

			m_isAlive = false;
		}
	}

	if (death)
	{
		// プレイヤーと当たった時のSEの再生
		ADX2Le::Play(CRI_PLAYER_DAMAGE);

		// プレイヤーの体力を減らす
		m_target->ReduceLife(2);

		m_target = nullptr;
	}

	// 速度分移動する
	m_translation += m_velocity;

	//return false;
}
