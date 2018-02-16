//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerRightFoot.h
//!
//!	@brief	プレイヤーの右足のヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER_RIGHT_FOOT
#define PLAYER_RIGHT_FOOT

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerRightFoot :public Player
{
public:
	PlayerRightFoot();
	~PlayerRightFoot() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_RIGHT_FOOT
