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
	MasaboLib::Camera* camera;

	LandShapeCommonDef()
	{
		camera = nullptr;
	}
};

// 共用データ
class LandShapeCommon
{
protected:
	// LandShapeクラスからメンバ変数にアクセスできるようにする
	friend class LandShape;

	// 共通カメラ
	MasaboLib::Camera* m_camera;
	// コモンステートへのポインタ
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	// エフェクトファクトリ
	std::unique_ptr<DirectX::EffectFactory>	m_effectFactory;
	// ベーシックエフェクトへのポインタ
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// プリミティブバッチへのポインタ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>>	m_primitiveBatch;
	// 入力レイアウトへのポインタ
	ID3D11InputLayout*	m_inputLayout;
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
	static std::unique_ptr<LandShapeCommon> m_common;
	// 地形当たりデータマップ
	static std::map<std::wstring, std::unique_ptr<LandShapeData>> m_dataArray;

	// 表示オブジェクト
	MasaboLib::Obj3D m_obj;
	// 地形当たりデータ
	const LandShapeData* m_data;
	// ワールド→モデル行列
	DirectX::SimpleMath::Matrix m_worldLocal;
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
	// ライティングを無効にする
	void DisableLighting();

	bool IntersectSphere(const Sphere& sphere, DirectX::SimpleMath::Vector3* reject);
	bool IntersectSegment(const Segment& segment, DirectX::SimpleMath::Vector3* inter);

	// アクセッサ
	const DirectX::SimpleMath::Vector3& GetTrans()
	{
		return m_obj.GetTranslation();
	}
	const DirectX::SimpleMath::Vector3& GetRot()
	{
		return m_obj.GetRotation();
	}
	float GetScale()
	{
		return m_obj.GetScale().x;
	}
	const DirectX::SimpleMath::Matrix& GetLocalWorld()
	{
		return m_obj.GetWorld();
	}

	void SetTrans(const DirectX::SimpleMath::Vector3& trans)
	{
		m_obj.SetTranslation(trans);
	}
	void SetRot(const DirectX::SimpleMath::Vector3& rot)
	{
		m_obj.SetRotation(rot);
	}
	void SetScale(float scale)
	{
		m_obj.SetScale(DirectX::SimpleMath::Vector3(scale));
	}
	void SetLocalWorld(const DirectX::SimpleMath::Matrix& mat)
	{
		m_obj.SetWorld(mat);
	}
};