//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	WeakEnemy.h
//!
//!	@brief	弱い敵のクラスのヘッダファイル
//!
//!	@date	2018/01/18
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef WEAK_ENEMY
#define WEAK_ENEMY

// ヘッダファイルの読み込み ================================================
#include "Enemy.h"


class WeakEnemy :public Enemy
{
public:
	WeakEnemy();
	~WeakEnemy() {}

	void Initialize() override;
};

#endif // !WEAK_ENEMY
