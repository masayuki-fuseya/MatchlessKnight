//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	PlayerRightForeArm.cpp
//!
//!	@brief	プレイヤーの右前腕部のソースファイル
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "PlayerRightForeArm.h"


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
PlayerRightForeArm::PlayerRightForeArm()
{
}



//**********************************************************************
//!	@brief		初期化する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void PlayerRightForeArm::Initialize()
{
	LoadModel(L"KnightRightForeArm");
}



//**********************************************************************
//!	@brief		更新する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void PlayerRightForeArm::Update()
{
}



//**********************************************************************
//!	@brief		描画する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void PlayerRightForeArm::Render()
{
	Obj3D::Render();
}
