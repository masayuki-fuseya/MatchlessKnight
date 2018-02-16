//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Character.cpp
//!
//!	@brief	キャラクタークラスのソースファイル
//!
//!	@date	2017/08/28
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "Character.h"


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
Character::Character()
	: m_life(0)
	, m_isAlive(true)
{
}



//**********************************************************************
//!	@brief		行列を計算する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void Character::CalcMatrix()
{
	Obj3D::Update();
}



//**********************************************************************
//!	@brief		状態を変える
//!
//!	@param[in]	変更後の状態
//!
//!	@return		なし
//**********************************************************************
void Character::ChangeState(State* currentState)
{
	m_currentState = currentState;
}



//**********************************************************************
//!	@brief		体力を減らす
//!
//!	@param[in]	受けたダメージ
//!
//!	@return		なし
//**********************************************************************
void Character::ReduceLife(const int damage)
{
	if (m_life - damage < 0)
	{
		m_life = 0;
		m_isAlive = false;
	}
	else
	{
		m_life -= damage;
	}
}
