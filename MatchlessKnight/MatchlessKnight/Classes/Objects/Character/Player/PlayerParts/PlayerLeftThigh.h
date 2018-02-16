//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerLeftThigh.h
//!
//!	@brief	プレイヤーの左大腿のヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER_LEFT_THIGH
#define PLAYER_LEFT_THIGH

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerLeftThigh :public Player
{
public:
	PlayerLeftThigh();
	~PlayerLeftThigh() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_LEFT_THIGH
