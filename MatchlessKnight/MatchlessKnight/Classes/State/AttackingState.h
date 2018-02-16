//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	AttackingState.h
//!
//!	@brief	攻撃状態クラスのヘッダファイル
//!
//!	@date	2017/08/28
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef ATTACKING_STATE
#define ATTACKING_STATE

// ヘッダファイルの読み込み ================================================
#include "MasaboLib.h"
#include "State.h"
#include "..\Objects\Character\Character.h"


class AttackingState :public State, public MasaboLib::Singleton<AttackingState>
{
private:
	friend class MasaboLib::Singleton<AttackingState>;

	// 攻撃状態のキャラクター
	Character* m_character;
public:
	void Initialize(Character* character) override;
	void Execute() override;
	void Render() override;
private:
	AttackingState() {}
};

#endif // !ATTACKING_STATE
