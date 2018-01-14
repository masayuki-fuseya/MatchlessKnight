//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayScene.h
//!
//!	@brief	プレイシーンクラスのヘッダファイル
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef MASABO_PLAY_SCENE
#define MASABO_PLAY_SCENE

// ヘッダファイルの読み込み ================================================
#include "BaseScene.h"
#include <Effects.h>
#include <memory>


namespace MasaboLib
{
	class PlayScene :public BaseScene
	{
	private:
		// カメラ
		std::unique_ptr<DebugCamera> m_camera;
		// エフェクトファクトリー
		std::unique_ptr<DirectX::EffectFactory> m_factory;
	public:
		PlayScene();
		~PlayScene() {}

		void Initialize();
		void Update(const DX::StepTimer& timer);
		void Render(const DX::StepTimer& timer, DirectX::SpriteBatch* batch, DirectX::SpriteFont* font);
		void Finalize();
	};
}

#endif // !MASABO_PLAY_SCENE
