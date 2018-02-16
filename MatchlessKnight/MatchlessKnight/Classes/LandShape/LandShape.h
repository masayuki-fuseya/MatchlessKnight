//--------------------------------------------------------------------------------------
// �t�@�C����: LandShape
// �쐬��:
// �쐬��:
// ����:�n�`������
//--------------------------------------------------------------------------------------

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "LandShapeData.h"
#include "MasaboLib.h"
#include "..\Collision\Collision.h"
#include <CommonStates.h>
#include <Effects.h>
#include <map>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>



// ���p�f�[�^�������p�\����
struct LandShapeCommonDef
{
	// �J����
	MasaboLib::Camera* camera;

	LandShapeCommonDef()
	{
		camera = nullptr;
	}
};

// ���p�f�[�^
class LandShapeCommon
{
protected:
	// LandShape�N���X���烁���o�ϐ��ɃA�N�Z�X�ł���悤�ɂ���
	friend class LandShape;

	// ���ʃJ����
	MasaboLib::Camera* m_camera;
	// �R�����X�e�[�g�ւ̃|�C���^
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	// �G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory>	m_effectFactory;
	// �x�[�V�b�N�G�t�F�N�g�ւ̃|�C���^
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// �v���~�e�B�u�o�b�`�ւ̃|�C���^
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>>	m_primitiveBatch;
	// ���̓��C�A�E�g�ւ̃|�C���^
	ID3D11InputLayout*	m_inputLayout;
public:
	// �f�o�b�O�\���p�̍ő咸�_��
	static const size_t BatchSize = 6144;
	// �R���X�g���N�^
	LandShapeCommon(LandShapeCommonDef def);
	// �f�X�g���N�^
	~LandShapeCommon();
};


// �n�`������
class LandShape
{
protected:
	// ���ʃf�[�^
	static std::unique_ptr<LandShapeCommon> m_common;
	// �n�`������f�[�^�}�b�v
	static std::map<std::wstring, std::unique_ptr<LandShapeData>> m_dataArray;

	// �\���I�u�W�F�N�g
	MasaboLib::Obj3D m_obj;
	// �n�`������f�[�^
	const LandShapeData* m_data;
	// ���[���h�����f���s��
	DirectX::SimpleMath::Matrix m_worldLocal;
public:
	// �G�t�F�N�g�t�@�N�g������
	static void InitializeCommon(LandShapeCommonDef def);

	// �R���X�g���N�^
	LandShape();
	// ������
	void Initialize(const std::wstring& filename_bin, const std::wstring& filename_cmo);
	// ���[���h�s��̌v�Z
	void Update();
	// �f�o�b�O�`��
	void Draw();
	// ���C�e�B���O�𖳌��ɂ���
	void DisableLighting();

	bool IntersectSphere(const Sphere& sphere, DirectX::SimpleMath::Vector3* reject);
	bool IntersectSegment(const Segment& segment, DirectX::SimpleMath::Vector3* inter);

	// �A�N�Z�b�T
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