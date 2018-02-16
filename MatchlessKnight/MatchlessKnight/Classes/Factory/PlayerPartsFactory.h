//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerPartsFactory.h
//!
//!	@brief	プレイヤーパーツ生成工場クラスのヘッダファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef PLAYER_PARTS_FACTORY
#define PLAYER_PARTS_FACTORY

// ヘッダファイルの読み込み ================================================
#include "..\Objects\Character\Player\Player.h"
#include <memory>


class PlayerPartsFactory
{
public:
	// プレイヤーパーツを生成する
	std::unique_ptr<Player>&& Create(Player::PARTS parts);
};

#endif // !PLAYER_PARTS_FACTORY
