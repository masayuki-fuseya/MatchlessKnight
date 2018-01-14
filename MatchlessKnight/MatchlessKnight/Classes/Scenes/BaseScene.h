//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	BaseScene.h
//!
//!	@brief	シーンの元クラスのヘッダファイル
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef MASABO_BASE_SCENE
#define MASABO_BASE_SCENE

// ヘッダファイルの読み込み ================================================
#include "MasaboLib.h"
#include <SpriteBatch.h>
#include <SpriteFont.h>


namespace MasaboLib
{
	class BaseScene
	{
	public:
		virtual ~BaseScene() {}

		virtual void Initialize() = 0;
		virtual void Update(const DX::StepTimer& timer) = 0;
		virtual void Render(const DX::StepTimer& timer, DirectX::SpriteBatch* batch, DirectX::SpriteFont* font) = 0;
		virtual void Finalize() = 0;
	};
}

#endif // !MASABO_BASE_SCENE
