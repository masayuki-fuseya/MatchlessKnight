//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	EnemyFactory.cpp
//!
//!	@brief	敵生成工場クラスのソースファイル
//!
//!	@date	2017/07/24
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "EnemyFactory.h"
#include "..\Scenes\PlayScene.h"
#include "..\Objects\Character\Enemy\WeakEnemy.h"

// ネームスペースの省略 ====================================================
using namespace std;


//**********************************************************************
//!	@brief		初期化する
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void EnemyFactory::Initialize()
{
	// 敵の最大数分生成する
	m_enemies.resize(MasaboLib::PlayScene::MAX_ENEMY_NUM);
	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr)
	{
		(*itr) = make_shared<WeakEnemy>();
		(*itr)->Initialize();
	}
}



//**********************************************************************
//!	@brief		生きていない敵を返す
//!
//!	@param[in]	敵の種類
//!
//!	@return		敵のポインタ
//**********************************************************************
shared_ptr<Enemy> EnemyFactory::Reallocate(Enemy::ID id)
{
	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr)
	{
		// 生きていない敵がいれば位置を決めて返す
		if (!(*itr)->GetIsAlive())
		{
			(*itr)->SetIsAlive(true);
			(*itr)->DesidePos();
			return (*itr);
		}
	}

	return nullptr;
}
