//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡
//!	@file	ParticleEffectManager.cpp
//!
//!	@brief	パーティクルエフェクト管理クラスのソースファイル
//!
//!	@date	2017/11/06
//!
//!	@author	Masayuki Fuseya
//≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡

// ヘッダファイルの読み込み ================================================
#include "ParticleEffectManager.h"
#include <WICTextureLoader.h>

// ネームスペースの省略 ====================================================
using namespace MasaboLib;
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

// 静的メンバ変数の定義 ====================================================
// パーティクルの最大数
const int ParticleEffectManager::PARTICLE_NUM_MAX = 10000;
// 入力レイアウトの定義
const vector<D3D11_INPUT_ELEMENT_DESC> ParticleEffectManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,									D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(Vector3),						D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(Vector3) + sizeof(Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

unique_ptr<ParticleEffectManager> ParticleEffectManager::m_instance = nullptr;


//**********************************************************************
//!	@brief		初期化処理
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void ParticleEffectManager::Initialize()
{
	auto graphics = Graphics::GetInstance();

	// コンパイルされたシェーダファイルを読み込み
	auto VSData = BinLoader::Load(L"Resources/CSO/ParticleVS.cso");
	auto GSData = BinLoader::Load(L"Resources/CSO/ParticleGS.cso");
	auto PSData = BinLoader::Load(L"Resources/CSO/ParticlePS.cso");


	auto device = graphics->GetDevice();

	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.data(), VSData.size(), NULL, m_VertexShader.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.data(), GSData.size(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}

	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.data(), PSData.size(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	// 頂点フォーマットを指定して入力レイアウト作成
	device->CreateInputLayout(&INPUT_LAYOUT[0], INPUT_LAYOUT.size(), VSData.data(), VSData.size(), m_inputLayout.GetAddressOf());

	// パーティクルの最大数を決める
	m_particles.reserve(PARTICLE_NUM_MAX);

	// シェーダに共通データを渡すための定数バッファを作成
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Constants);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	if (FAILED(device->CreateBuffer(&cb, nullptr, m_constantBuffer.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"CreateBuffer Failed.", NULL, MB_OK);
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
void ParticleEffectManager::Update(const StepTimer& timer)
{
	for (auto itr = m_particles.begin(); itr != m_particles.end(); )
	{
		(*itr)->Update(timer);

		if ((*itr)->IsEnded())
		{
			itr = m_particles.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}



//**********************************************************************
//!	@brief		描画処理
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void ParticleEffectManager::Render()
{
	auto graphics = Graphics::GetInstance();

	auto context = graphics->GetContext();

	Matrix world = Matrix::Identity;
	Matrix view = m_camera->GetView();
	Matrix proj = m_camera->GetProj();

	Matrix wvp = world * view * proj;
	// シェーダの定数バッファに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		Constants constants;

		constants.WVP = wvp;
		constants.Billboard = m_camera->GetBillboard();

		memcpy_s(pData.pData, pData.RowPitch, &constants, sizeof(Constants));

		context->Unmap(m_constantBuffer.Get(), 0);
	}

	// 定数バッファをどのシェーダで使うか
	context->VSSetConstantBuffers(0, 0, nullptr);
	context->GSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
	context->PSSetConstantBuffers(0, 0, nullptr);

	// デバイスコンテキストに、描画に使用するシェーダを指定
	context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_PixelShader.Get(), nullptr, 0);

	for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
	{
		(*itr)->Render();
	}

	// シェーダをクリア
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}



//**********************************************************************
//!	@brief		パーティクルを追加する
//!
//!	@param[in]	追加するパーティクル
//!
//!	@return		なし
//**********************************************************************
void ParticleEffectManager::Entry(unique_ptr<ParticleEffect>&& particle)
{
	if (m_particles.size() < PARTICLE_NUM_MAX)
	{
		m_particles.push_back(move(particle));
	}
}



//**********************************************************************
//!	@brief		テクスチャ生成
//!
//!	@param[in]	テクスチャ番号, ファイルのパス
//!
//!	@return		生成されたテクスチャ
//**********************************************************************
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ParticleEffectManager::CreateTexture(int textureNumber, const wchar_t* filepath)
{
	auto device = Graphics::GetInstance()->GetDevice();

	if (m_textures.count(textureNumber) == 0)
	{
		// テクスチャ読み込み
		if (FAILED(CreateWICTextureFromFile(device, filepath, nullptr, m_textures[textureNumber].ReleaseAndGetAddressOf())))
		{
			// エラー
			MessageBox(0, L"CreateWICTextureFromFile Failed.", NULL, MB_OK);
			return nullptr;
		}
	}

	return m_textures[textureNumber];
}



//**********************************************************************
//!	@brief		コンストラクタ
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
ParticleEffectManager::ParticleEffectManager()
	: m_camera(nullptr)
{
}
