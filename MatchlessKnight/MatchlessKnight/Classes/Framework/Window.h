//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Window.h
//!
//!	@brief	ウィンドウクラスのヘッダファイル
//!
//!	@date	2017/12/26
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef  WINDOW
#define  WINDOW

// ヘッダファイルの読み込み ================================================
#include <Windows.h>


class Window
{
private:
	// ウィンドウハンドル
	HWND m_hWnd;
	// インスタンスハンドル
	HINSTANCE m_hInstance;
	int m_nCmdShow;
public:
	Window();

	// クラスを登録しウィンドウを生成する
	void Initialize(const wchar_t* gameTitle, int width, int height);

	// ウィンドウプロシージャ
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	// クラスを登録する
	bool RegisterWindowClass();
	// ウィンドウを生成する
	bool CreateGameWindow(const wchar_t* gameTitle, int width, int height);
};

#endif	// WINDOW
