//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	ParticleFactory.h
//!
//!	@brief	パーティクルファクトリークラスのヘッダファイル
//!
//!	@date	2017/11/13
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef MASABO_PARTICLE_FACTORY
#define MASABO_PARTICLE_FACTORY

// ヘッダファイルの読み込み ================================================
#include "ParticleEffect.h"
#include <memory>


namespace MasaboLib
{
	class ParticleFactory
	{
	public:
		// パーティクルを生成する
		static std::unique_ptr<ParticleEffect>&& Create(int textureNumber, ParticleEffect::ParticleData& data, const wchar_t* filepath);
	};
}

#endif // !MASABO_PARTICLE_FACTORY
