//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerLeftFoot.h
//!
//!	@brief	プレイヤーの左足のヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAEYR_LEFT_FOOT
#define PLAEYR_LEFT_FOOT

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerLeftFoot :public Player
{
public:
	PlayerLeftFoot();
	~PlayerLeftFoot() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAEYR_LEFT_FOOT
