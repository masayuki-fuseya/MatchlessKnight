//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	ParticleFactory.cpp
//!
//!	@brief	パーティクルファクトリークラスのソースファイル
//!
//!	@date	2017/11/13
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "ParticleFactory.h"
#include "ParticleEffectManager.h"

// ネームスペースの省略 ====================================================
using namespace MasaboLib;
using namespace std;


//**********************************************************************
//!	@brief		パーティクルを生成する
//!
//!	@param[in]	テクスチャ番号, パーティクルの情報が入った構造体, ファイルのパス
//!
//!	@return		生成されたパーティクル
//**********************************************************************
unique_ptr<ParticleEffect>&& ParticleFactory::Create(int textureNumber, ParticleEffect::ParticleData& data, const wchar_t* filepath)
{
	std::unique_ptr<ParticleEffect> particle = make_unique<ParticleEffect>();
	particle->Initialize(data);
	auto texture = ParticleEffectManager::GetInstance()->CreateTexture(textureNumber, filepath);
	particle->SetTexture(texture);

	return move(particle);
}
