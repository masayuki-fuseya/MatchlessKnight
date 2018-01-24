//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	ParticleEffectManager.h
//!
//!	@brief	パーティクルエフェクト管理クラスのヘッダファイル
//!
//!	@date	2017/11/06
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// 多重インクルードの防止 ==================================================
#pragma once
#ifndef MASABO_PARTICLE_EFFECT_MANAGER
#define MASABO_PARTICLE_EFFECT_MANAGER

// ヘッダファイルの読み込み ================================================
#include "MasaboLib.h"
#include "ParticleEffect.h"
#include <d3d11.h>
#include <map>
#include <memory>
#include <SimpleMath.h>
#include <vector>
#include <wrl.h>


namespace MasaboLib
{
	class ParticleEffectManager :public Singleton<ParticleEffectManager>
	{
	public:
		// パーティクルの最大数
		static const int PARTICLE_NUM_MAX;
		// 入力レイアウトの定義
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
		
		// 定数バッファ
		struct Constants
		{
			//World View Projection 合成行列
			DirectX::SimpleMath::Matrix WVP;
			// ビルボード行列
			DirectX::SimpleMath::Matrix Billboard;
		};
	private:
		friend class Singleton<ParticleEffectManager>;

		// インスタンス
		static std::unique_ptr<ParticleEffectManager> m_instance;

		// 頂点シェーダ
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		// ジオメトリシェーダ
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;
		// ピクセルシェーダ
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

		// 入力レイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		// 定数バッファオブジェクト
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

		// テクスチャ
		std::map<int, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;

		// カメラ
		MasaboLib::Camera* m_camera;

		// パーティクルの集合体
		std::vector<std::unique_ptr<ParticleEffect>> m_particles;
	public:
		// インスタンスを取得する
		static ParticleEffectManager* GetInstance()
		{
			// 生成されてなければ生成する
			if (!m_instance.get())
			{
				m_instance.reset(new ParticleEffectManager());
			}
			return m_instance.get();
		}

		void Initialize();
		void Update(const MasaboLib::DX::StepTimer& timer);
		void Render();

		// パーティクル登録
		void Entry(std::unique_ptr<ParticleEffect>&& particle);

		// テクスチャを生成する
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> CreateTexture(int textureNumber, const wchar_t* filepath);

		// ゲッター ////////////////////////////////////////////

		// 入力レイアウトを取得する
		Microsoft::WRL::ComPtr<ID3D11InputLayout> GetInputLayout()
		{
			return m_inputLayout;
		}

		////////////////////////////////////////////////////////

		// セッター ////////////////////////////////////////////

		// カメラを設定する
		void SetCamera(MasaboLib::Camera* camera)
		{
			m_camera = camera;
		}

		////////////////////////////////////////////////////////
	private:
		ParticleEffectManager();
	};
}

#endif // !MASABO_PARTICLE_EFFECT_MANAGER
