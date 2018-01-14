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
			NONE,
			LOGO,
			TITLE,
			PLAY,
			CLEAR,
			OVER
		};
	private:
		friend class Singleton<SceneManager>;

		// インスタンス
		static std::unique_ptr<SceneManager> m_instance;

		// 全てのシーンを保持
		std::map<SCENE_ID, std::unique_ptr<BaseScene>> m_scene;
		// 現在のシーンID
		SCENE_ID m_id;
	public:
		// インスタンスを取得する
		static SceneManager* GetInstance()
		{
			// 生成されてなければ生成する
			if (!m_instance.get())
			{
				m_instance.reset(new SceneManager());
			}
			return m_instance.get();
		}

		void Update(const MasaboLib::DX::StepTimer& timer);
		void Render(const MasaboLib::DX::StepTimer& timer, DirectX::SpriteBatch* batch, DirectX::SpriteFont* font);

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
