//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerHead.h
//!
//!	@brief	プレイヤーの頭のヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER_HEAD
#define PLAYER_HEAD

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerHead :public Player
{
public:
	PlayerHead();
	~PlayerHead() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_HEAD
