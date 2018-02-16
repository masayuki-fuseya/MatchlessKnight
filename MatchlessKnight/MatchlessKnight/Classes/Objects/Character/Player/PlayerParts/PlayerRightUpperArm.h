//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerRightUpperArm.h
//!
//!	@brief	プレイヤーの右上腕のヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER_RIGHT_UPPER_ARM
#define PLAYER_RIGHT_UPPER_ARM

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerRightUpperArm :public Player
{
public:
	PlayerRightUpperArm();
	~PlayerRightUpperArm() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_RIGHT_UPPER_ARM
