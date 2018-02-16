//--------------------------------------------------------------------------------------
// ファイル名: LandShape
// 作成者:
// 作成日:
// 説明:地形当たり
//--------------------------------------------------------------------------------------

// ヘッダファイルの読み込み ================================================
#include <algorithm>
#include <fstream>
#include <DirectXColors.h>
#include "LandShape.h"
#include "..\Collision\CollisionNode.h"

// ネームスペースの省略 ====================================================
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

// 静的メンバ変数の定義 ====================================================
std::unique_ptr<LandShapeCommon> LandShape::m_common;
std::map<std::wstring, std::unique_ptr<LandShapeData>> LandShape::m_dataArray;


LandShapeCommon::LandShapeCommon(LandShapeCommonDef def)
{
	auto graphics = MasaboLib::Graphics::GetInstance();

	// カメラ
	m_camera = def.camera;
	// 描画ステート
	m_commonStates.reset(new CommonStates(graphics->GetDevice()));
	// エフェクトファクトリ
	m_effectFactory.reset(new EffectFactory(graphics->GetDevice()));
	// プリミティブバッチ
	m_primitiveBatch.reset(new PrimitiveBatch<VertexPositionNormal>(graphics->GetContext(), BatchSize * 3, BatchSize));
	// エフェクト
	m_basicEffect.reset(new BasicEffect(graphics->GetDevice()));
	// ライティング有効
	m_basicEffect->SetLightingEnabled(true);
	// マテリアルカラー設定
	m_basicEffect->SetAmbientLightColor(Vector3(0, 0.0f, 0));
	m_basicEffect->SetDiffuseColor(Vector3(1.0f, 1.0f, 1.0f));
	// ライト0（グリーン）
	m_basicEffect->SetLightEnabled(0, true);
	m_basicEffect->SetLightDiffuseColor(0, Vector3(0.1f, 0.6f, 0.1f));
	m_basicEffect->SetLightDirection(0, Vector3(0, -1.0f, 0));
	// ライト1（ピンク）
	m_basicEffect->SetLightEnabled(1, true);
	m_basicEffect->SetLightDiffuseColor(1, Vector3(0.5f, 0.2f, 0.3f));
	m_basicEffect->SetLightDirection(1, Vector3(-1, 0, -2));
	// ライト2（水色）
	m_basicEffect->SetLightEnabled(2, true);
	m_basicEffect->SetLightDiffuseColor(2, Vector3(0.3f, 0.3f, 0.6f));
	m_basicEffect->SetLightDirection(2, Vector3(1, 0, 2));
	// フォグ（灰色） ※遠近感を強調するために使う
	m_basicEffect->SetFogEnabled(true);
	m_basicEffect->SetFogColor(Colors::White);
	m_basicEffect->SetFogStart(2.f);
	m_basicEffect->SetFogEnd(10.f);


	void const* shaderByteCode;
	size_t byteCodeLength;

	// シェーダーの取得
	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// 入力レイアウトの作成
	graphics->GetDevice()->CreateInputLayout(VertexPositionNormal::InputElements,
		VertexPositionNormal::InputElementCount,
		shaderByteCode, byteCodeLength,
		&m_inputLayout);
}

LandShapeCommon::~LandShapeCommon()
{
	// 入力レイアウトの解放
	if (m_inputLayout)
	{
		m_inputLayout->Release();
		m_inputLayout = nullptr;
	}
}

/**
*	@brief エフェクトファクトリー生成
*/
void LandShape::InitializeCommon(LandShapeCommonDef def)
{
	// 既に初期化済み
	if (m_common)	return;

	// 共通データ生成
	m_common.reset(new LandShapeCommon(def));
}

//--------------------------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------------------------
LandShape::LandShape()
	: m_data(nullptr)
{

}

//--------------------------------------------------------------------------------------
// 初期化
//--------------------------------------------------------------------------------------
void LandShape::Initialize(const wstring& filename_bin, const wstring& filename_cmo)
{
	// ファイル名が空白でなければ
	if (filename_bin.size() > 0)
	{
		// フルパスに補完
		wstring fullpath_bin = L"Resources/LandShape/" + filename_bin + L".landshape";

		if (m_dataArray.count(fullpath_bin) == 0)
		{
			// モデルの読み込み
			m_dataArray[fullpath_bin] = LandShapeData::CreateFromFile(fullpath_bin.c_str());
		}
		// 地形データをセット
		m_data = m_dataArray[fullpath_bin].get();
	}

	// ファイル名が空白でなければ
	if (filename_cmo.size() > 0)
	{
		// オブジェクト初期化
		m_obj.LoadModel(filename_cmo);
	}
}

//--------------------------------------------------------------------------------------
// ワールド行列の計算
//--------------------------------------------------------------------------------------
void LandShape::Update()
{
	m_obj.Update();
	// 逆行列を計算
	const Matrix& localworld = m_obj.GetWorld();
	m_worldLocal = localworld.Invert();
}

//--------------------------------------------------------------------------------------
// 地形データの描画
//--------------------------------------------------------------------------------------
void LandShape::Draw()
{
	if (CollisionNode::GetDebugVisible() == false)
	{
		// モデル描画
		m_obj.Render();
	}
	else if (m_data)
	{
		// デバッグ描画
		const Matrix& view = m_common->m_camera->GetView();
		const Matrix& projection = m_common->m_camera->GetProj();

		// 作成した行列をエフェクトにセット
		m_common->m_basicEffect->SetWorld(m_obj.GetWorld());
		m_common->m_basicEffect->SetView(view);
		m_common->m_basicEffect->SetProjection(projection);

		auto graphics = MasaboLib::Graphics::GetInstance();

		auto context = graphics->GetContext();

		// エフェクトの設定（各行列やテクスチャなどを設定している）
		m_common->m_basicEffect->Apply(context);

		// 深度ステンシル ステートを設定する
		context->OMSetDepthStencilState(m_common->m_commonStates->DepthDefault(), 0);

		// ブレンディング ステートを設定する
		context->OMSetBlendState(m_common->m_commonStates->NonPremultiplied(), nullptr, 0xFFFFFFFF);

		// ラスタライザ ステートを設定する 時計回りを非表示
		context->RSSetState(m_common->m_commonStates->CullNone());

		// サンプラーステートを設定する
		auto samplerState = m_common->m_commonStates->PointWrap();
		context->PSSetSamplers(0, 1, &samplerState);

		// 入力レイアウトを設定する
		context->IASetInputLayout(m_common->m_inputLayout);

		// 描画開始
		m_common->m_primitiveBatch->Begin();

		const uint16_t* pIndex = &m_data->m_Indices[0];
		int numIndex = m_data->m_Indices.size();

		const VertexPositionNormal* pVertex = (VertexPositionNormal*)&m_data->m_Vertices[0];
		int numVertex = m_data->m_Vertices.size();

		// 三角形プリミティブの描画
		m_common->m_primitiveBatch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, pIndex, numIndex, pVertex, numVertex);

		// 描画終了
		m_common->m_primitiveBatch->End();
	}
}

void LandShape::DisableLighting()
{
	m_obj.DisableLighting();
}

//--------------------------------------------------------------------------------------
// 地形と球の交差判定
// sphere : 判定球
// reject : 押し出すベクトル
//--------------------------------------------------------------------------------------
bool LandShape::IntersectSphere(const Sphere& sphere, Vector3* reject)
{
	if (m_data == nullptr) return false;

	// ヒットフラグを初期化
	bool hit = false;
	// 大きい数字で初期化
	float over_length = 1.0e5;
	Vector3 l_inter;
	Vector3 l_normal;
	Vector3 l_down;
	// スケールを取得
	float scale = GetScale();

	// 球をコピー
	Sphere localsphere = sphere;

	// スケール0の場合、判定しない
	if (scale <= 1.0e-10) return false;

	// 球の中心点をワールド座標からモデル座標系に引き込む
	localsphere.m_center = Vector3::Transform(sphere.m_center, m_worldLocal);
	// 半径をワールドをワールド座標系からモデル座標系に変換
	localsphere.m_radius = sphere.m_radius / scale;

	// 三角形の数
	int nTri = m_data->m_Triangles.size();
	// 全ての三角形について
	for (int i = 0; i < nTri; i++)
	{
		float temp_over_length;
		Vector3 temp_inter;

		const Triangle& tri = m_data->m_Triangles[i];

		// 三角形と球の当たり判定
		if (CheckSphere2Triangle(localsphere, tri, &temp_inter))
		{// ヒットした
			hit = true;
			// 衝突点から球の中心へのベクトル
			Vector3 sub = localsphere.m_center - temp_inter;
			// 球の中心が三角形にめりこんでいる距離を計算
			temp_over_length = sub.Dot(-tri.Normal);

			// めりこみ具合がここまでで最小なら
			if (temp_over_length < over_length)
			{
				// ヒット座標、法線、めりこみ距離を記録
				l_inter = temp_inter;
				l_normal = tri.Normal;
				over_length = temp_over_length;
			}
		}
	}

	if (hit)
	{
		// 距離をモデル座標系からワールド座標系での長さに変換
		over_length *= scale;

		// ワールド行列を取得
		const Matrix& localworld = m_obj.GetWorld();

		// 排斥ベクトルの計算
		if (reject != nullptr)
		{
			// 地形の法線方向をモデル座標系からワールド座標系に変換
			*reject = Vector3::TransformNormal(l_normal, localworld);
			reject->Normalize();
			// めり込み分だけ押し出すベクトルを計算
			const float extra = 0.05f;
			float reject_distance = sphere.m_radius + over_length + extra;
			*reject = (*reject) * reject_distance;
		}
	}

	return hit;
}

//--------------------------------------------------------------------------------------
// 地形と線分の交差判定
// segment : 線分
// （出力）inter : 交点（ポリゴンの平面上で、点との再接近点の座標を返す）
//--------------------------------------------------------------------------------------
bool LandShape::IntersectSegment(const Segment& segment, Vector3* inter)
{
	if (m_data == nullptr) return false;

	// ヒットフラグを初期化
	bool hit = false;
	// 大きい数字で初期化
	float distance = 1.0e5;
	// 角度判定用に地面とみなす角度の限界値<度>
	const float limit_angle = XMConvertToRadians(30.0f);
	Vector3 l_inter;

	// コピー
	Segment localSegment = segment;
	// 線分をワールド座標からモデル座標系に引き込む
	localSegment.m_start = Vector3::Transform(localSegment.m_start, m_worldLocal);
	localSegment.m_end = Vector3::Transform(localSegment.m_end, m_worldLocal);
	// 線分の方向ベクトルを取得
	Vector3 segmentNormal = localSegment.m_end - localSegment.m_start;
	segmentNormal.Normalize();

	// 三角形の数
	int nTri = m_data->m_Triangles.size();
	// 全ての三角形について
	for (int i = 0; i < nTri; i++)
	{
		float temp_distance;
		Vector3 temp_inter;

		// 上方向ベクトルと法線の内積
		// 長さが１のベクトル２同士の内積は、コサイン（ベクトルの内積の定義より）
		float cosine = -segmentNormal.Dot(m_data->m_Triangles[i].Normal);
		//// コサイン値から、上方向との角度差を計算
		//float angle = acosf(cosine);
		//// 上方向との角度が限界角より大きければ、面の傾きが大きいので、地面とみなさずスキップ
		//if ( angle > limit_angle ) continue;

		//--高速版--
		const float limit_cosine = cosf(limit_angle);
		// コサインが１のときにベクトル間の角度は0度であり、ベクトルの角度差が大きいほど、コサインは小さいので、
		// コサイン値のまま比較すると、角度の比較の場合と大小関係が逆である
		// つまり、コサイン値が一定値より小さければ、面の傾きが大きいので、地面とみなさずスキップ
		if (cosine < limit_cosine) continue;
		//--高速版ここまで--

		// 線分と三角形（ポリゴン）の交差判定
		if (CheckSegment2Triangle(localSegment, m_data->m_Triangles[i], &temp_inter))
		{
			hit = true;
			// 線分の始点と衝突点の距離を計算（めりこみ距離）
			temp_distance = Vector3::Distance(localSegment.m_start, temp_inter);
			// めりこみ具合がここまでで最小なら
			if (temp_distance < distance)
			{
				// 衝突点の座標、めりこみ距離を記録
				l_inter = temp_inter;
				distance = temp_distance;
			}
		}
	}

	if (hit && inter != nullptr)
	{
		// 衝突点の座標をモデル座標系からワールド座標系に変換
		const Matrix& localworld = m_obj.GetWorld();
		*inter = Vector3::Transform(l_inter, localworld);
	}

	return hit;
}