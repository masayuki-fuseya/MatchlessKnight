//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerLeftUpperArm.h
//!
//!	@brief	プレイヤーの左上腕のヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER_LEFT_UPPER_ARM
#define PLAYER_LEFT_UPPER_ARM

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerLeftUpperArm :public Player
{
public:
	PlayerLeftUpperArm();
	~PlayerLeftUpperArm() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_LEFT_UPPER_ARM
