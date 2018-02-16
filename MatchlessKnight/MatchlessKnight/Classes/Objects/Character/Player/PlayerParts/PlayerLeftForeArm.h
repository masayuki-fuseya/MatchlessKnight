//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerLeftForeArm.h
//!
//!	@brief	プレイヤーの左前腕部のヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAEYR_LEFT_FORE_ARM
#define PLAEYR_LEFT_FORE_ARM

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerLeftForeArm :public Player
{
public:
	PlayerLeftForeArm();
	~PlayerLeftForeArm() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAEYR_LEFT_FORE_ARM
