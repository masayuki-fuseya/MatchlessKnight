//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerLeftCalf.h
//!
//!	@brief	プレイヤーの左ふくらはぎのヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER_LEFT_CALF
#define PLAYER_LEFT_CALF

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerLeftCalf :public Player
{
public:
	PlayerLeftCalf();
	~PlayerLeftCalf() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_LEFT_CALF
