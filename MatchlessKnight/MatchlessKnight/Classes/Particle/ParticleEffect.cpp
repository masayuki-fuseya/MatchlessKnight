//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	ParticleEffect.cpp
//!
//!	@brief	パーティクルエフェクトクラスのソースファイル
//!
//!	@date	2017/11/10
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "ParticleEffect.h"
#include "ParticleEffectManager.h"
#include <WICTextureLoader.h>


using namespace MasaboLib;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;


//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
ParticleEffect::ParticleEffect()
	: m_frameCount(0)
{
}



//**********************************************************************
//!	@brief		初期化処理
//!
//!	@param[in]	パーティクルの情報が入った構造体
//!
//!	@return		なし
//**********************************************************************
void ParticleEffect::Initialize(ParticleData& data)
{
	auto graphics = Graphics::GetInstance();

	auto device = graphics->GetDevice();
	auto context = graphics->GetContext();

	// プリミティブバッチ作成
	// 各頂点に含まれる情報が、位置・色・テクスチャUV
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context, 1, ParticleEffectManager::PARTICLE_NUM_MAX);

	m_data = std::make_unique<ParticleData>(data);

	// 頂点データ追加
	VertexPositionColorTexture vertexData;
	vertexData.color = m_data->m_startColor;
	vertexData.position = m_data->m_pos;
	vertexData.textureCoordinate = Vector2(m_data->m_startScale, m_data->m_startRadian);
	m_vertice = std::make_unique<VertexPositionColorTexture>(vertexData);

	m_commonStates = std::make_unique<CommonStates>(device);

	// テクスチャサンプラー作成
	D3D11_SAMPLER_DESC sam;
	// 全ての変数に0を入れる(構造体にのみ使用)
	ZeroMemory(&sam, sizeof(sam));
	sam.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sam.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sam.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sam.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	if (FAILED(device->CreateSamplerState(&sam, m_sampler.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"CreateSamplerState Failed.", NULL, MB_OK);
		return;
	}

	// 減算描画用のブレンドステートを作成
	D3D11_BLEND_DESC desc;
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_REV_SUBTRACT;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	if (FAILED(device->CreateBlendState(&desc, m_blendStateSubtract.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"CreateBlendState Failed.", NULL, MB_OK);
		return;
	}
}



//**********************************************************************
//!	@brief		更新処理
//!
//!	@param[in]	ステップタイマー
//!
//!	@return		なし
//**********************************************************************
void ParticleEffect::Update(const StepTimer& timer)
{
	m_frameCount++;

	// 加速度
	m_data->m_velocity += m_data->m_accel;
	// 移動
	m_vertice->position = m_vertice->position + m_data->m_velocity;
	// 色のアニメーション
	m_vertice->color = m_data->m_startColor + (m_data->m_endColor - m_data->m_startColor) *
		(m_frameCount / (60.0f * m_data->m_disappearanceTime));
	// 大きさのアニメーション
	m_vertice->textureCoordinate.x = m_data->m_startScale + (m_data->m_endScale - m_data->m_startScale) *
		(m_frameCount / (60.0f * m_data->m_disappearanceTime));
	// 角度のアニメーション
	m_vertice->textureCoordinate.y = m_data->m_startRadian + (m_data->m_endRadian - m_data->m_startRadian) *
		(m_frameCount / (60.0f * m_data->m_disappearanceTime));
}



//**********************************************************************
//!	@brief		描画処理
//!
//!	@param[in]	カメラ
//!
//!	@return		なし
//**********************************************************************
void ParticleEffect::Render(Camera* camera)
{
	auto graphics = Graphics::GetInstance();

	auto device = graphics->GetDevice();
	auto context = graphics->GetContext();

	context->IASetInputLayout(ParticleEffectManager::GetInstance()->GetInputLayout().Get());

	// 陰面消去
	context->RSSetState(m_commonStates->CullNone());
	// アルファブレンド設定
	//context->OMSetBlendState(m_commonStates->NonPremultiplied(), nullptr, 0xffffffff);
	// 加算描画
	context->OMSetBlendState(m_commonStates->Additive(), nullptr, 0xffffffff);
	// 減算描画
	//context->OMSetBlendState(m_BlendStateSubtract.Get(), nullptr, 0xffffff);
	// 深度テスト設定
	context->OMSetDepthStencilState(m_commonStates->DepthNone(), 0);

	context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	// 頂点データをすべて渡して描画する
	m_primitiveBatch->Begin();
	m_primitiveBatch->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, m_vertice.get(), 1);
	m_primitiveBatch->End();
}



//**********************************************************************
//!	@brief		終了処理
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void ParticleEffect::Finalize()
{
}



//**********************************************************************
//!	@brief		消滅時間を過ぎたか
//!
//!	@param[in]	なし
//!
//!	@return		true:過ぎた
//!	@return		false:過ぎていない
//**********************************************************************
bool ParticleEffect::IsEnded()
{
	if (m_data->m_disappearanceTime * 60.0f < m_frameCount)
	{
		return true;
	}

	return false;
}
