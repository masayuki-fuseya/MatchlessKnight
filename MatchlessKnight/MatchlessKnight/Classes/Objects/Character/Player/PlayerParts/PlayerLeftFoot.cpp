//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerLeftFoot.cpp
//!
//!	@brief	プレイヤーの左足のソースファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "PlayerLeftFoot.h"


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
PlayerLeftFoot::PlayerLeftFoot()
{
}



//**********************************************************************
//!	@brief		初期化する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void PlayerLeftFoot::Initialize()
{
	LoadModel(L"KnightLeftFoot");
}



//**********************************************************************
//!	@brief		更新する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void PlayerLeftFoot::Update()
{
}



//**********************************************************************
//!	@brief		描画する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void PlayerLeftFoot::Render()
{
	Obj3D::Render();
}
