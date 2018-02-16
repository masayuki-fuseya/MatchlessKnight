//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	Character.h
//!
//!	@brief	キャラクタークラスのヘッダファイル
//!
//!	@date	2017/08/28
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef CHARACTER
#define CHARACTER

// ヘッダファイルの読み込み ================================================
#include "MasaboLib.h"
#include "..\..\State\State.h"
#include <d3d11.h>
#include <memory>
#include <SimpleMath.h>


class State;


class Character :public MasaboLib::Obj3D
{
protected:
	// 現在の状態
	State* m_currentState;
	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 残りライフ
	int m_life;
	// 生きているか
	bool m_isAlive;
public:
	Character();
	virtual ~Character() {}

	// 行列を計算する
	void CalcMatrix();

	// 起立状態の更新をする
	virtual void UpdateStanding() = 0;
	// 攻撃状態の更新をする
	virtual void UpdateAttacking() = 0;
	// 起立状態の描画をする
	virtual void RenderStanding() = 0;
	// 攻撃状態の描画をする
	virtual void RenderAttacking() = 0;

	// 状態を変える
	void ChangeState(State* currentState);
	// 体力を減らす
	void ReduceLife(const int damage);
};

#endif // !CHARACTER
