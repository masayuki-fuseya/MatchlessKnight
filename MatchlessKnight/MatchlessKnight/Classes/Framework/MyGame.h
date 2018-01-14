//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	MyGame.h
//!
//!	@brief	自分のゲームクラスのヘッダファイル
//!
//!	@date	2017/12/27
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef MYGAME
#define MYGAME

// ヘッダファイルの読み込み ================================================
#include "Game.h"
#include "MasaboLib.h"


class MyGame :public Game
{
public:
	MyGame(int width, int height);

	void Initialize() override;
	void Update(const MasaboLib::DX::StepTimer& timer) override;
	void Render(const MasaboLib::DX::StepTimer& timer) override;
	void Finalize() override;
};

#endif // MYGAME
