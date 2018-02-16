//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	StandingState.h
//!
//!	@brief	起立状態クラスのヘッダファイル
//!
//!	@date	2017/08/28
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef STANDING_STATE
#define STANDING_STATE

// ヘッダファイルの読み込み ================================================
#include "MasaboLib.h"
#include "State.h"


class StandingState :public State, public MasaboLib::Singleton<StandingState>
{
private:
	friend class MasaboLib::Singleton<StandingState>;

	// 起立状態のキャラクター
	Character* m_character;
public:
	void Initialize(Character* character) override;
	void Execute() override;
	void Render() override;
private:
	StandingState() {}
};

#endif // !STANDING_STATE
