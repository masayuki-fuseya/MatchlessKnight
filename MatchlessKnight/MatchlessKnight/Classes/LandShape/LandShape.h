//--------------------------------------------------------------------------------------
// ファイル名: LandShape
// 作成者:
// 作成日:
// 説明:地形当たり
//--------------------------------------------------------------------------------------

// 多重インクルードの防止 ==================================================
#pragma once

// ヘッダファイルの読み込み ================================================
#include "LandShapeData.h"
#include "MasaboLib.h"
#include "..\Collision\Collision.h"
#include <CommonStates.h>
#include <Effects.h>
#include <map>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>



// 共用データ初期化用構造体
struct LandShapeCommonDef
{
	// カメラ
	MasaboLib::Camera* pCamera;

	LandShapeCommonDef()
	{
		pCamera = nullptr;
	}
};

// 共用データ
class LandShapeCommon
{
protected:
	// LandShapeクラスからメンバ変数にアクセスできるようにする
	friend class LandShape;

	// 共通カメラ
	MasaboLib::Camera* m_pCamera;
	// コモンステートへのポインタ
	std::unique_ptr<DirectX::CommonStates>	m_pStates;
	// エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory>	m_pEffectFactory;
	// ベーシックエフェクトへのポインタ
	std::unique_ptr<DirectX::BasicEffect>	m_pEffect;
	// プリミティブバッチへのポインタ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>>	m_pPrimitiveBatch;
	// 入力レイアウトへのポインタ
	ID3D11InputLayout*	m_pInputLayout;
public:
	// デバッグ表示用の最大頂点数
	static const size_t BatchSize = 6144;
	// コンストラクタ
	LandShapeCommon(LandShapeCommonDef def);
	// デストラクタ
	~LandShapeCommon();
};


// 地形当たり
class LandShape
{
protected:
	// 共通データ
	static std::unique_ptr<LandShapeCommon> s_pCommon;
	// 地形当たりデータマップ
	static std::map<std::wstring, std::unique_ptr<LandShapeData>> s_dataarray;

	// 表示オブジェクト
	MasaboLib::Obj3D m_Obj;
	// 地形当たりデータ
	const LandShapeData* m_pData;
	// ワールド→モデル行列
	DirectX::SimpleMath::Matrix m_WorldLocal;
public:
	// エフェクトファクトリ生成
	static void InitializeCommon(LandShapeCommonDef def);

	// コンストラクタ
	LandShape();
	// 初期化
	void Initialize(const std::wstring& filename_bin, const std::wstring& filename_cmo);
	// ワールド行列の計算
	void Update();
	// デバッグ描画
	void Draw();
	// ライティングカット
	void DisableLighting();

	bool IntersectSphere(const Sphere& sphere, DirectX::SimpleMath::Vector3* reject);
	bool IntersectSegment(const Segment& segment, DirectX::SimpleMath::Vector3* inter);

	// アクセッサ
	const DirectX::SimpleMath::Vector3& GetTrans()
	{
		return m_Obj.GetTranslation();
	}
	const DirectX::SimpleMath::Vector3& GetRot()
	{
		return m_Obj.GetRotation();
	}
	float GetScale()
	{
		return m_Obj.GetScale().x;
	}
	const DirectX::SimpleMath::Matrix& GetLocalWorld()
	{
		return m_Obj.GetWorld();
	}

	void SetTrans(const DirectX::SimpleMath::Vector3& trans)
	{
		m_Obj.SetTranslation(trans);
	}
	void SetRot(const DirectX::SimpleMath::Vector3& rot)
	{
		m_Obj.SetRotation(rot);
	}
	void SetScale(float scale)
	{
		m_Obj.SetScale(DirectX::SimpleMath::Vector3(scale));
	}
	void SetLocalWorld(const DirectX::SimpleMath::Matrix& mat)
	{
		m_Obj.SetWorld(mat);
	}
};