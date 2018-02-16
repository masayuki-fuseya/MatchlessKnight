//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	EnemyFactory.h
//!
//!	@brief	敵生成工場クラスのヘッダファイル
//!
//!	@date	2017/07/24
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef ENEMY_FACTORY
#define ENEMY_FACTORY

// ヘッダファイルの読み込み ================================================
#include "..\Objects\Character\Enemy\Enemy.h"
#include <memory>
#include <vector>


class EnemyFactory
{
private:
	// 敵
	std::vector<std::shared_ptr<Enemy>> m_enemies;
public:
	void Initialize();

	// 生きていない敵を返す
	std::shared_ptr<Enemy> Reallocate(Enemy::ID id);
};

#endif // !ENEMY_FACTORY
