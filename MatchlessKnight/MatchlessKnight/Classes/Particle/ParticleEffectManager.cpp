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
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

// 静的メンバ変数の定義 ====================================================
// パーティクルの最大数
const int ParticleEffectManager::PARTICLE_NUM_MAX = 10000;
// 入力レイアウトの定義
const std::vector<D3D11_INPUT_ELEMENT_DESC> ParticleEffectManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,									D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(Vector3),						D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(Vector3) + sizeof(Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

std::unique_ptr<ParticleEffectManager> ParticleEffectManager::m_instance = nullptr;


//**********************************************************************
//!	@brief		初期化処理
//!
//!	@param[in]	なし
//!
//!	@return		なし
//**********************************************************************
void ParticleEffectManager::Initialize()
{
	auto graphics = MasaboLib::Graphics::GetInstance();

	// コンパイルされたシェーダファイルを読み込み
	auto VSData = BinLoader::Load(L"Resources/Shaders/ParticleVS.cso");
	auto GSData = BinLoader::Load(L"Resources/Shaders/ParticleGS.cso");
	auto PSData = BinLoader::Load(L"Resources/Shaders/ParticlePS.cso");


	auto device = graphics->GetDevice();
	//ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();

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

	// やってみよう① /////////////////////////////////////////////////////

	// 線
	//for (int i = 0; i < 1000; i++)
	//{
	//	// 1つ分の頂点データ
	//	VertexPositionColorTexture vertexData;
	//	vertexData.position = Vector3(-0.5f + i / 1000.0f, 0, 0);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate = Vector2(0, 0);
	//	m_Vertices.push_back(vertexData);
	//}

	// 十字
	//for (int i = 0; i < 4000; i++)
	//{
	//	// 1つ分の頂点データ
	//	VertexPositionColorTexture vertexData;
	//	// 横線
	//	if (i < 2000)
	//	{
	//		vertexData.position = Vector3(-1.0f + i / 1000.0f, 0, 0);
	//	}
	//	// 縦線
	//	else
	//	{
	//		vertexData.position = Vector3(0, -1.0f + (i - 2000) / 1000.0f, 0);
	//	}
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate = Vector2(0, 0);
	//	m_Vertices.push_back(vertexData);
	//}

	// ×字
	//for (int i = 0; i < 4000; i++)
	//{
	//	// 1つ分の頂点データ
	//	VertexPositionColorTexture vertexData;
	//	// 左下から右上
	//	if (i < 2000)
	//	{
	//		vertexData.position = Vector3(-1.0f + i / 1000.0f, -1.0f + i / 1000.0f, 0);
	//	}
	//	// 左上から右下
	//	else
	//	{
	//		vertexData.position = Vector3(-1.0f + (i - 2000) / 1000.0f, 1.0f - (i - 2000) / 1000.0f, 0);
	//	}
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate = Vector2(0, 0);
	//	m_Vertices.push_back(vertexData);
	//}

	// 楕円
	//for (int i = 0; i < 4000; i++)
	//{
	//	float radian = XM_PIDIV2 * i / 1000.0f;
	//
	//	// 1つ分の頂点データ
	//	VertexPositionColorTexture vertexData;
	//	vertexData.position = Vector3(sin(radian) * 0.5f, cos(radian) * 0.5f, 0);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate = Vector2(0, 0);
	//	m_Vertices.push_back(vertexData);
	//}

	// 真円
	//for (int i = 0; i < 4000; i++)
	//{
	//	RECT rect = DeviceResources::GetInstance()->GetOutputSize();
	//	float width = rect.right - rect.left;
	//	float height = rect.top - rect.bottom;
	//	float aspect = height / width;
	//	float radian = XM_PIDIV2 * i / 1000.0f;

	//	// 1つ分の頂点データ
	//	VertexPositionColorTexture vertexData;
	//	vertexData.position = Vector3(sin(radian) * 0.5f * aspect, cos(radian) * 0.5f, 0);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate = Vector2(0, 0);
	//	m_Vertices.push_back(vertexData);
	//}

	///////////////////////////////////////////////////////////////////////

	//VertexPositionColorTexture vertexData;
	// やってみよう⑥ ////////////////////////////////

	// 横に5つ表示
	//for (int i = 0; i < 5; i++)
	//{
	//	vertexData.position = Vector3(-3.0f + i * 1.5f, 0, 1);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate.x = 1;
	//	vertexData.textureCoordinate.y = 1;
	//	m_Vertices.push_back(vertexData);
	//}

	// 円形に表示
	//for (int i = 0; i < 20; i++)
	//{
	//	vertexData.position = Vector3(cos(XM_2PI * i / 20.0f), sin(XM_2PI * i / 20.0f), 1);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate.x = 1;
	//	vertexData.textureCoordinate.y = 0;
	//	m_Vertices.push_back(vertexData);
	//}

	// 8の字に表示
	//for (int i = 0; i < 20; i++)
	//{
	//	vertexData.position = Vector3(cos(XM_2PI * i / 20.0f), sin(XM_2PI * i / 20.0f * 2) / 2.0f, 1);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate.x = 1;
	//	vertexData.textureCoordinate.y = 0;
	//	m_Vertices.push_back(vertexData);
	//}

	//////////////////////////////////////////////////

	// やってみよう⑦ ////////////////////////////////
	// 円形に表示
	//for (int i = 0; i < 100; i++)
	//{
	//	vertexData.position = Vector3(cos(XM_2PI * i / 100.0f), sin(XM_2PI * i / 100.0f), 1);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	// 薄赤い月
	//	//vertexData.color = Vector4(1, 0, 0, 1);
	//	vertexData.textureCoordinate.x = 1;
	//	vertexData.textureCoordinate.y = 0;
	//	m_Vertices.push_back(vertexData);
	//}
	//////////////////////////////////////////////////

	//vertexData.position = Vector3(0, 0, 1);
	//vertexData.color = Vector4(1, 1, 1, 1);
	//vertexData.textureCoordinate.x = 1;
	//vertexData.textureCoordinate.y = 1;
	//m_Vertices.push_back(vertexData);

	//vertexData.position = Vector3(1.5f, 0, 1);
	//vertexData.color = Vector4(1, 1, 1, 1);
	//vertexData.textureCoordinate.x = 0.5;
	//vertexData.textureCoordinate.y = 0;
	//m_Vertices.push_back(vertexData);

	//// 1点目 左下
	//VertexPositionColorTexture vertexData;
	//vertexData.position = Vector3(0, -1.0f, 1);
	//vertexData.color = Vector4(1, 1, 1, 1);
	//// やってみよう② ///////////////////
	////vertexData.color = Vector4(1, 0, 0, 1);
	///////////////////////////////////////
	//vertexData.textureCoordinate = Vector2(0, 1);
	//// やってみよう④ ///////////////////

	//// 左上だけ表示
	////vertexData.textureCoordinate = Vector2(0, 0.5f);

	//// 2×3で表示
	////vertexData.textureCoordinate = Vector2(0, 2.0f);

	///////////////////////////////////////
	//m_Vertices.push_back(vertexData);

	//// 2点目 右下
	//vertexData.position = Vector3(1.0f, -1.0f, 1);
	//vertexData.color = Vector4(1, 1, 1, 1);
	//// やってみよう② ///////////////////
	////vertexData.color = Vector4(1, 0, 0, 1);
	///////////////////////////////////////
	//vertexData.textureCoordinate = Vector2(1, 1);
	//// やってみよう④ ///////////////////

	//// 左上だけ表示
	////vertexData.textureCoordinate = Vector2(0.5f, 0.5f);

	//// 2×3で表示
	////vertexData.textureCoordinate = Vector2(3.0f, 2.0f);

	///////////////////////////////////////
	//m_Vertices.push_back(vertexData);

	//// 3点目 左上
	//vertexData.position = Vector3(0, 0, 1);
	//vertexData.color = Vector4(1, 1, 1, 1);
	//// やってみよう② ///////////////////
	////vertexData.color = Vector4(1, 0, 0, 1);
	///////////////////////////////////////
	//vertexData.textureCoordinate = Vector2(0, 0);
	//// やってみよう④ ///////////////////

	//// 左上だけ表示
	////vertexData.textureCoordinate = Vector2(0, 0);

	//// 2×3で表示
	////vertexData.textureCoordinate = Vector2(0, 0);

	///////////////////////////////////////
	//m_Vertices.push_back(vertexData);

	//// 4点目 右上
	//vertexData.position = Vector3(1.0f, 0, 1);
	//vertexData.color = Vector4(1, 1, 1, 1);
	//vertexData.textureCoordinate = Vector2(1, 0);
	//// やってみよう④ ///////////////////

	//// 左上だけ表示
	////vertexData.textureCoordinate = Vector2(0.5f, 0);

	//// 2×3で表示
	////vertexData.textureCoordinate = Vector2(3.0f, 0);

	///////////////////////////////////////
	//m_Vertices.push_back(vertexData);
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
	// やってみよう② ///////////////////////////////////////////

	// 右に移動
	//for (auto itr = m_Vertices.begin(); itr != m_Vertices.end(); itr++)
	//{
	//	itr->position = itr->position + Vector3(0.01f, 0.0f, 0.0f);
	//}

	// 赤から青
	//for (auto itr = m_Vertices.begin(); itr != m_Vertices.end(); itr++)
	//{
	//	itr->color.x -= 0.01f;
	//	itr->color.z += 0.01f;
	//}

	/////////////////////////////////////////////////////////////

	// やってみよう④ ///////////////////////////////////////////

	// 右から左に流れるアニメーション
	//for (auto itr = m_Vertices.begin(); itr != m_Vertices.end(); itr++)
	//{
	//	itr->textureCoordinate.x += 0.05f;
	//}

	// 画像の真ん中を中心に回転
	//static float radian = 0.05f;
	//for (auto itr = m_Vertices.begin(); itr != m_Vertices.end(); itr++)
	//{
	//	Vector2 tmp = itr->textureCoordinate - Vector2(0.5f, 0.5f);
	//	float x = tmp.x * cos(radian) - tmp.y * sin(radian);
	//	float y = tmp.x * sin(radian) + tmp.y * cos(radian);
	//	x += 0.5f;
	//	y += 0.5f;
	//	itr->textureCoordinate = Vector2(x, y);
	//}

	/////////////////////////////////////////////////////////////

	// やってみよう⑥ ///////////////////////////////////////////

	// 左から右にウェーブ
	//static float param = 0.0f;
	//param += XMConvertToRadians(6.0f);
	//int i = 0;
	//for (VertexPositionColorTexture& vertex : m_Vertices)
	//{
	//	vertex.textureCoordinate.x = (sin(param - i * XMConvertToRadians(72.0f)) + 1) / 2.0f;
	//	i++;
	//}

	// 円形にウェーブ
	//static float param = 0.0f;
	//param += XMConvertToRadians(6.0f);
	//int i = 0;
	//for (VertexPositionColorTexture& vertex : m_Vertices)
	//{
	//	vertex.textureCoordinate.x = (sin(param - i * XMConvertToRadians(18.0f)) + 1) / 10;
	//	i++;
	//}

	// 8の字にウェーブ
	//static float param = 0.0f;
	//param += XMConvertToRadians(6.0f);
	//int i = 0;
	//for (VertexPositionColorTexture& vertex : m_Vertices)
	//{
	//	vertex.textureCoordinate.x = (sin(param - i * XMConvertToRadians(18.0f)) + 1) / 10;
	//	i++;
	//}

	/////////////////////////////////////////////////////////////

	// やってみよう⑦ ///////////////////////////////////////////

	// 月の形
	//static float param = 0.0f;
	//param += XMConvertToRadians(6.0f);
	//int i = 0;
	//for (VertexPositionColorTexture& vertex : m_Vertices)
	//{
	//	// スケール
	//	vertex.textureCoordinate.x = (sin(param - i * XMConvertToRadians(3.6f)) + 1) / 4.0f;
	//	// 回転
	//	//vertex.textureCoordinate.y += XMConvertToRadians(2.0f);

	//	// グラデーション //////////////////////////////
	//	vertex.color.x = (cos(param - i * XMConvertToRadians(3.6f)));
	//	vertex.color.y = 0.0f;
	//	vertex.color.z = (sin(param - i * XMConvertToRadians(3.6f)));
	//	////////////////////////////////////////////////

	//	i++;
	//}

	/////////////////////////////////////////////////////////////

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
		(*itr)->Render(m_camera);
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
void ParticleEffectManager::Entry(std::unique_ptr<ParticleEffect>&& particle)
{
	if (m_particles.size() < PARTICLE_NUM_MAX)
	{
		m_particles.push_back(std::move(particle));
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
