//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	ParticleEffect.h
//!
//!	@brief	パーティクルエフェクトクラスのヘッダファイル
//!
//!	@date	2017/11/10
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef MASABO_PARTICLE_EFFECT
#define MASABO_PARTICLE_EFFECT

// ヘッダファイルの読み込み ================================================
#include "MasaboLib.h"
#include <CommonStates.h>
#include <d3d11.h>
#include <memory>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <SimpleMath.h>
#include <wrl.h>


namespace MasaboLib
{
	class ParticleEffect
	{
	public:
		// パーティクルデータ
		struct ParticleData
		{
			// 座標
			DirectX::SimpleMath::Vector3 m_pos;
			// 速度
			DirectX::SimpleMath::Vector3 m_velocity;
			// 加速度
			DirectX::SimpleMath::Vector3 m_accel;
			// 色
			DirectX::SimpleMath::Vector4 m_startColor;
			DirectX::SimpleMath::Vector4 m_endColor;
			// 大きさ
			float m_startScale;
			float m_endScale;
			// 角度
			float m_startRadian;
			float m_endRadian;
			// 消滅時間
			float m_disappearanceTime;

			ParticleData()
				: m_startColor(1, 1, 1, 1)
				, m_endColor(1, 1, 1, 1)
				, m_startScale(1.0f)
				, m_endScale(1.0f)
				, m_startRadian(0.0f)
				, m_endRadian(0.0f)
				, m_disappearanceTime(1.0f) {}

			void Initialize()
			{
				m_pos = DirectX::SimpleMath::Vector3::Zero;
				m_velocity = DirectX::SimpleMath::Vector3::Zero;
				m_accel = DirectX::SimpleMath::Vector3::Zero;
				m_startColor = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
				m_endColor = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
				m_startScale = 1.0f;
				m_endScale = 1.0f;
				m_startRadian = 0.0f;
				m_endRadian = 0.0f;
				m_disappearanceTime = 1.0f;
			}
		};
	private:
		// プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
		// 頂点データ
		std::unique_ptr<DirectX::VertexPositionColorTexture> m_vertice;
		// 汎用描画設定
		std::unique_ptr<DirectX::CommonStates> m_commonStates;
		// テクスチャ
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		// テクスチャサンプラー
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

		// 減算描画ステート
		Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendStateSubtract;

		// パーティクルデータ
		std::unique_ptr<ParticleData> m_data;
		// フレーム数
		int m_frameCount;
	public:
		ParticleEffect();
		~ParticleEffect() {}

		void Initialize(ParticleData& data);
		void Update(const MasaboLib::DX::StepTimer& timer);
		void Render();
		void Finalize();

		bool IsEnded();

		void SetTexture(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& texture)
		{
			m_texture = texture;
		}
	};
}

#endif // !MASABO_PARTICLE_EFFECT
