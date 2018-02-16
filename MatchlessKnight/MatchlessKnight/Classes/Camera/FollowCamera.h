//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	FolloCamera.h
//!
//!	@brief	プレイヤーに追従するカメラクラスのヘッダファイル
//!
//!	@date	2017/05/15
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef FOLLOW_CAMERA
#define FOLLOW_CAMERA

// ヘッダファイルの読み込み ================================================
#include "MasaboLib.h"
#include "..\Objects\Character\Player\Player.h"
#include <d3d11.h>
#include <SimpleMath.h>


class FollowCamera :public MasaboLib::Camera
{
public:
	// プレイヤーとの距離
	static const float CAMERA_DISTANCE;
private:
	// 追従対象
	Player* m_target;
	// 追従対象の座標
	DirectX::SimpleMath::Vector3 m_targetPos;
	// 追従対象の角度
	float m_targetAngle;
public:
	FollowCamera(int width, int height);
	~FollowCamera() {}

	void Initialize();
	void Update() override;

	// セッター //////////////////////////////////

	// 追従対象を設定する
	void SetTarget(Player* target)
	{
		m_target = target;
	}

	//////////////////////////////////////////////
};

#endif // !FOLLOW_CAMERA
