//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	SceneManager.h
//!
//!	@brief	シーン管理クラスのヘッダファイル
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef MASABO_SCENE_MANAGER
#define MASABO_SCENE_MANAGER

// ヘッダファイルの読み込み ================================================
#include "BaseScene.h"
#include "MasaboLib.h"
#include <map>
#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>


namespace MasaboLib
{
	class SceneManager :public Singleton<SceneManager>
	{
	public:
		enum SCENE_ID
		{
			NONE,		// なし(ゲーム終了)
			LOGO,		// ロゴシーン
			TITLE,		// タイトルシーン
			PLAY,		// プレイシーン
			CLEAR,		// ゲームクリアシーン
			OVER		// ゲームオーバーシーン
		};
	private:
		friend class Singleton<SceneManager>;

		// 全てのシーンを保持
		std::map<SCENE_ID, std::unique_ptr<BaseScene>> m_scene;
		// 現在のシーンID
		SCENE_ID m_id;
	public:
		void Update(const DX::StepTimer& timer);
		void Render(const DX::StepTimer& timer, DirectX::SpriteBatch* batch, DirectX::SpriteFont* font);
		void Finalize();

		// シーンを登録する
		void RegisterScene();
		// シーンを変更する
		void ChangeScene(SCENE_ID id);
		// シーンを初期化する
		void ChangePreScene();
		// シーンの終了処理をする
		void ChangePostScene();
	private:
		SceneManager() {}
	};
}

#endif // !MASABO_SCENE_MANAGER
