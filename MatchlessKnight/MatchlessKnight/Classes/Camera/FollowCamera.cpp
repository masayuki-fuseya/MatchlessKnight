//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	FollowCamera.cpp
//!
//!	@brief	プレイヤーに追従するカメラクラスのソースファイル
//!
//!	@date	2017/05/15
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "FollowCamera.h"

// ネームスペースの省略 ====================================================
using namespace DirectX::SimpleMath;

// 静的メンバ変数の定義 ====================================================
const float FollowCamera::CAMERA_DISTANCE = 7.0f;


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	横幅
//!	@param[in]	縦幅
//!
//!	@return		なし
//**********************************************************************
FollowCamera::FollowCamera(int width, int height)
	: MasaboLib::Camera(width, height)
	, m_targetAngle(0.0f)
	, m_target(nullptr)
{
}



//**********************************************************************
//!	@brief		初期化する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void FollowCamera::Initialize()
{
	if (m_target)
	{
		// 追従対象の座標を取得する
		m_targetPos = m_target->GetTranslation();
	}

	// 向く方向を計算する
	m_refPos = m_targetPos + Vector3(0.0f, 4.0f, 0.0f);

	// ベクトルを回転させる
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	// カメラの位置を計算する
	m_eyePos = m_refPos + cameraV;
}



//**********************************************************************
//!	@brief		更新する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void FollowCamera::Update()
{
	// 追従対象が設定されていなければ抜ける
	if (!m_target)
	{
		Camera::Update();
		return;
	}

	// 追従対象の座標と角度を取得する
	m_targetPos = m_target->GetTranslation();
	m_targetAngle = m_target->GetRotation().y;

	// 向く方向を計算する
	Vector3 refPos = m_targetPos + Vector3(0.0f, 4.0f, 0.0f);

	// ベクトルを回転させる
	Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANCE);
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	cameraV = Vector3::TransformNormal(cameraV, rotmat);
	// カメラの位置を計算する
	Vector3 eyePos = refPos + cameraV;

	// 視点を現在位置から補間する
	m_eyePos = m_eyePos + (eyePos - m_eyePos) * 0.05f;
	// 参照点を現在位置から補間する
	m_refPos = m_refPos + (refPos - m_refPos) * 0.2f;

	// 行列を更新する
	Camera::Update();
}
