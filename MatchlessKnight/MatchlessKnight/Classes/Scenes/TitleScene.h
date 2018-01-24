//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	TitleScene.h
//!
//!	@brief	タイトルシーンクラスのヘッダファイル
//!
//!	@date	2017/12/16
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef MASABO_TITLE_SCENE
#define MASABO_TITLE_SCENE

// ヘッダファイルの読み込み ================================================
#include "BaseScene.h"
#include <d3d11.h>
#include <memory>
#include <SimpleMath.h>
#include <wrl.h>


namespace MasaboLib
{
	class TitleScene :public BaseScene
	{
	private:
		// 最大選択項目
		static const int MAX_SELECTION_ITEM;

		// 背景画像
		std::unique_ptr<Texture> m_backgroundTexture;
		// タイトル画像
		std::unique_ptr<Texture> m_titleTexture;
		// "PUSH SPACE"の画像
		std::unique_ptr<Texture> m_pushSpaceTexture;
		// 選択項目画像
		std::unique_ptr<Texture> m_selectionItemTexture;
		// 矢印の画像
		std::unique_ptr<Texture> m_arrowTexture;
		// 背景画像の座標
		DirectX::SimpleMath::Vector2 m_bgPos;
		// スペースキーが押されているか
		bool m_isPressedSpace;
		// "PUSH SPACE"のアニメーション用タイム
		float m_animationTime;
		// 現在の選択項目
		int m_selectionItem;
	public:
		TitleScene();
		~TitleScene() {}

		void Initialize() override;
		void Update(const DX::StepTimer& timer) override;
		void Render(const DX::StepTimer& timer, DirectX::SpriteBatch* batch, DirectX::SpriteFont* font) override;
		void Finalize() override;
	};
}

#endif // !MASABO_TITLE_SCENE
