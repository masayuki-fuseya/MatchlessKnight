//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerRightHand.h
//!
//!	@brief	プレイヤーの右手のヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER_RIGHT_HAND
#define PLAYER_RIGHT_HAND

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerRightHand :public Player
{
public:
	PlayerRightHand();
	~PlayerRightHand() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_RIGHT_HAND
