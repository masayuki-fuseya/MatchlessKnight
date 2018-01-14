//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Main.cpp
//!
//!	@brief	プロジェクトのエントリーポイント
//!
//!	@date	2017/12/26
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "MyGame.h"

// ネームスペースの省略 ====================================================
using namespace std;
using namespace DirectX;


//**********************************************************************
//!	@brief		エントリーポイント
//!
//!	@param[in]	インスタンスハンドル
//!	@param[in]	インスタンス
//!	@param[in]	コマンドライン
//!	@param[in]	ウィンドウの最小化、最大化、通常表示を指定するためのフラグ
//!
//!	@return		0:正常終了
//!	@return		1:異常終了
//**********************************************************************
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!XMVerifyCPUSupport())
        return 1;
	// COMライブラリを初期化する
    if (FAILED(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED)))
        return 1;

	// ウィンドウサイズ
	int width = 1024;
	int height = 768;

	// MyGameを生成する
	MyGame myGame(width, height);
	// ゲームを更新する
	MSG msg = myGame.Run();

	// Comライブラリを終了処理する
    CoUninitialize();

    return (int) msg.wParam;
}
