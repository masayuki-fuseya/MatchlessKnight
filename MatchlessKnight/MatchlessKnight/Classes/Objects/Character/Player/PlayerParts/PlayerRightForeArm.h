//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerRightForeArm.h
//!
//!	@brief	プレイヤーの右前腕部のヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER_RIGHT_FORE_ARM
#define PLAYER_RIGHT_FORE_ARM

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerRightForeArm :public Player
{
public:
	PlayerRightForeArm();
	~PlayerRightForeArm() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_RIGHT_FORE_ARM
