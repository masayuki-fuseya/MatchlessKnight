//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerRightCalf.h
//!
//!	@brief	プレイヤーの右ふくらはぎのヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER_RIGHT_CALF
#define PLAYER_RIGHT_CALF

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerRightCalf :public Player
{
public:
	PlayerRightCalf();
	~PlayerRightCalf() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_RIGHT_CALF
