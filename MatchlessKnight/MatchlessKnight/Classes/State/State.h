//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	State.h
//!
//!	@brief	状態遷移の基底クラスのヘッダファイル
//!
//!	@date	2017/08/04
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef STATE
#define STATE

// ヘッダファイルの読み込み ================================================
#include "..\Objects\Character\Character.h"


class  Character;


class State
{
public:
	virtual void Initialize(Character* character) = 0;
	virtual void Execute() = 0;
	virtual void Render() = 0;
};

#endif // !STATE
