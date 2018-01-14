//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Game.h
//!
//!	@brief	ゲームクラスのヘッダファイル
//!
//!	@date	2017/12/27
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef GAME
#define GAME

// ヘッダファイルの読み込み ================================================
#include "Window.h"
#include "MasaboLib.h"
#include <CommonStates.h>
#include <d3d11.h>
#include <Effects.h>
#include <memory>
#include <SpriteBatch.h>
#include <SpriteFont.h>

class Window;


class Game
{
private:
	// 出力幅
	int m_width;
	// 出力高
	int m_height;

	// ウィンドウ
	std::unique_ptr<Window> m_window;
protected:
	// ステップタイマー
	MasaboLib::DX::StepTimer m_timer;
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_batch;
	// フォント
	std::unique_ptr<DirectX::SpriteFont> m_font;
	// エフェクトファクトリインターフェース
	std::unique_ptr<DirectX::IEffectFactory> m_effectFactory;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
public:
	Game(int width, int height);

    virtual void Initialize();
    // ゲームループを実行する
	MSG Run();
	virtual void Update(const MasaboLib::DX::StepTimer& timer);
	virtual void Render(const MasaboLib::DX::StepTimer& timer);
	virtual void Finalize();

	// 画面をクリアする
	virtual void Clear();
	// バックバッファをスクリーンに送る
	virtual void Present();

	// メッセージハンドラ
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

	// デフォルトウィンドウサイズに変更する
    void GetDefaultSize(int& width, int& height) const;

	// ゲームを終わる
	void Exit();
protected:
	// FPSを描画する
	void DrawFPS();
};

#endif	// GAME
