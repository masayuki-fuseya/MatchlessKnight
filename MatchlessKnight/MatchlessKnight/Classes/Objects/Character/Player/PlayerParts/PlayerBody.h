//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerBody.h
//!
//!	@brief	プレイヤーの体のヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER_BODY
#define PLAYER_BODY

// ヘッダファイルの読み込み ================================================
#include "..\Player.h"


class PlayerBody :public Player
{
public:
	PlayerBody();
	~PlayerBody() {}

	void Initialize() override;
	void Update() override;
	void Render() override;
};

#endif // !PLAYER_BODY
