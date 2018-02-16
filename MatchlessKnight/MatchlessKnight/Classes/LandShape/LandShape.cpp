//--------------------------------------------------------------------------------------
// �t�@�C����: LandShape
// �쐬��:
// �쐬��:
// ����:�n�`������
//--------------------------------------------------------------------------------------

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <algorithm>
#include <fstream>
#include <DirectXColors.h>
#include "LandShape.h"
#include "..\Collision\CollisionNode.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

// �ÓI�����o�ϐ��̒�` ====================================================
std::unique_ptr<LandShapeCommon> LandShape::m_common;
std::map<std::wstring, std::unique_ptr<LandShapeData>> LandShape::m_dataArray;


LandShapeCommon::LandShapeCommon(LandShapeCommonDef def)
{
	auto graphics = MasaboLib::Graphics::GetInstance();

	// �J����
	m_camera = def.camera;
	// �`��X�e�[�g
	m_commonStates.reset(new CommonStates(graphics->GetDevice()));
	// �G�t�F�N�g�t�@�N�g��
	m_effectFactory.reset(new EffectFactory(graphics->GetDevice()));
	// �v���~�e�B�u�o�b�`
	m_primitiveBatch.reset(new PrimitiveBatch<VertexPositionNormal>(graphics->GetContext(), BatchSize * 3, BatchSize));
	// �G�t�F�N�g
	m_basicEffect.reset(new BasicEffect(graphics->GetDevice()));
	// ���C�e�B���O�L��
	m_basicEffect->SetLightingEnabled(true);
	// �}�e���A���J���[�ݒ�
	m_basicEffect->SetAmbientLightColor(Vector3(0, 0.0f, 0));
	m_basicEffect->SetDiffuseColor(Vector3(1.0f, 1.0f, 1.0f));
	// ���C�g0�i�O���[���j
	m_basicEffect->SetLightEnabled(0, true);
	m_basicEffect->SetLightDiffuseColor(0, Vector3(0.1f, 0.6f, 0.1f));
	m_basicEffect->SetLightDirection(0, Vector3(0, -1.0f, 0));
	// ���C�g1�i�s���N�j
	m_basicEffect->SetLightEnabled(1, true);
	m_basicEffect->SetLightDiffuseColor(1, Vector3(0.5f, 0.2f, 0.3f));
	m_basicEffect->SetLightDirection(1, Vector3(-1, 0, -2));
	// ���C�g2�i���F�j
	m_basicEffect->SetLightEnabled(2, true);
	m_basicEffect->SetLightDiffuseColor(2, Vector3(0.3f, 0.3f, 0.6f));
	m_basicEffect->SetLightDirection(2, Vector3(1, 0, 2));
	// �t�H�O�i�D�F�j �����ߊ����������邽�߂Ɏg��
	m_basicEffect->SetFogEnabled(true);
	m_basicEffect->SetFogColor(Colors::White);
	m_basicEffect->SetFogStart(2.f);
	m_basicEffect->SetFogEnd(10.f);


	void const* shaderByteCode;
	size_t byteCodeLength;

	// �V�F�[�_�[�̎擾
	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// ���̓��C�A�E�g�̍쐬
	graphics->GetDevice()->CreateInputLayout(VertexPositionNormal::InputElements,
		VertexPositionNormal::InputElementCount,
		shaderByteCode, byteCodeLength,
		&m_inputLayout);
}

LandShapeCommon::~LandShapeCommon()
{
	// ���̓��C�A�E�g�̉��
	if (m_inputLayout)
	{
		m_inputLayout->Release();
		m_inputLayout = nullptr;
	}
}

/**
*	@brief �G�t�F�N�g�t�@�N�g���[����
*/
void LandShape::InitializeCommon(LandShapeCommonDef def)
{
	// ���ɏ������ς�
	if (m_common)	return;

	// ���ʃf�[�^����
	m_common.reset(new LandShapeCommon(def));
}

//--------------------------------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------------------------------
LandShape::LandShape()
	: m_data(nullptr)
{

}

//--------------------------------------------------------------------------------------
// ������
//--------------------------------------------------------------------------------------
void LandShape::Initialize(const wstring& filename_bin, const wstring& filename_cmo)
{
	// �t�@�C�������󔒂łȂ����
	if (filename_bin.size() > 0)
	{
		// �t���p�X�ɕ⊮
		wstring fullpath_bin = L"Resources/LandShape/" + filename_bin + L".landshape";

		if (m_dataArray.count(fullpath_bin) == 0)
		{
			// ���f���̓ǂݍ���
			m_dataArray[fullpath_bin] = LandShapeData::CreateFromFile(fullpath_bin.c_str());
		}
		// �n�`�f�[�^���Z�b�g
		m_data = m_dataArray[fullpath_bin].get();
	}

	// �t�@�C�������󔒂łȂ����
	if (filename_cmo.size() > 0)
	{
		// �I�u�W�F�N�g������
		m_obj.LoadModel(filename_cmo);
	}
}

//--------------------------------------------------------------------------------------
// ���[���h�s��̌v�Z
//--------------------------------------------------------------------------------------
void LandShape::Update()
{
	m_obj.Update();
	// �t�s����v�Z
	const Matrix& localworld = m_obj.GetWorld();
	m_worldLocal = localworld.Invert();
}

//--------------------------------------------------------------------------------------
// �n�`�f�[�^�̕`��
//--------------------------------------------------------------------------------------
void LandShape::Draw()
{
	if (CollisionNode::GetDebugVisible() == false)
	{
		// ���f���`��
		m_obj.Render();
	}
	else if (m_data)
	{
		// �f�o�b�O�`��
		const Matrix& view = m_common->m_camera->GetView();
		const Matrix& projection = m_common->m_camera->GetProj();

		// �쐬�����s����G�t�F�N�g�ɃZ�b�g
		m_common->m_basicEffect->SetWorld(m_obj.GetWorld());
		m_common->m_basicEffect->SetView(view);
		m_common->m_basicEffect->SetProjection(projection);

		auto graphics = MasaboLib::Graphics::GetInstance();

		auto context = graphics->GetContext();

		// �G�t�F�N�g�̐ݒ�i�e�s���e�N�X�`���Ȃǂ�ݒ肵�Ă���j
		m_common->m_basicEffect->Apply(context);

		// �[�x�X�e���V�� �X�e�[�g��ݒ肷��
		context->OMSetDepthStencilState(m_common->m_commonStates->DepthDefault(), 0);

		// �u�����f�B���O �X�e�[�g��ݒ肷��
		context->OMSetBlendState(m_common->m_commonStates->NonPremultiplied(), nullptr, 0xFFFFFFFF);

		// ���X�^���C�U �X�e�[�g��ݒ肷�� ���v�����\��
		context->RSSetState(m_common->m_commonStates->CullNone());

		// �T���v���[�X�e�[�g��ݒ肷��
		auto samplerState = m_common->m_commonStates->PointWrap();
		context->PSSetSamplers(0, 1, &samplerState);

		// ���̓��C�A�E�g��ݒ肷��
		context->IASetInputLayout(m_common->m_inputLayout);

		// �`��J�n
		m_common->m_primitiveBatch->Begin();

		const uint16_t* pIndex = &m_data->m_Indices[0];
		int numIndex = m_data->m_Indices.size();

		const VertexPositionNormal* pVertex = (VertexPositionNormal*)&m_data->m_Vertices[0];
		int numVertex = m_data->m_Vertices.size();

		// �O�p�`�v���~�e�B�u�̕`��
		m_common->m_primitiveBatch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, pIndex, numIndex, pVertex, numVertex);

		// �`��I��
		m_common->m_primitiveBatch->End();
	}
}

void LandShape::DisableLighting()
{
	m_obj.DisableLighting();
}

//--------------------------------------------------------------------------------------
// �n�`�Ƌ��̌�������
// sphere : ���苅
// reject : �����o���x�N�g��
//--------------------------------------------------------------------------------------
bool LandShape::IntersectSphere(const Sphere& sphere, Vector3* reject)
{
	if (m_data == nullptr) return false;

	// �q�b�g�t���O��������
	bool hit = false;
	// �傫�������ŏ�����
	float over_length = 1.0e5;
	Vector3 l_inter;
	Vector3 l_normal;
	Vector3 l_down;
	// �X�P�[�����擾
	float scale = GetScale();

	// �����R�s�[
	Sphere localsphere = sphere;

	// �X�P�[��0�̏ꍇ�A���肵�Ȃ�
	if (scale <= 1.0e-10) return false;

	// ���̒��S�_�����[���h���W���烂�f�����W�n�Ɉ�������
	localsphere.m_center = Vector3::Transform(sphere.m_center, m_worldLocal);
	// ���a�����[���h�����[���h���W�n���烂�f�����W�n�ɕϊ�
	localsphere.m_radius = sphere.m_radius / scale;

	// �O�p�`�̐�
	int nTri = m_data->m_Triangles.size();
	// �S�Ă̎O�p�`�ɂ���
	for (int i = 0; i < nTri; i++)
	{
		float temp_over_length;
		Vector3 temp_inter;

		const Triangle& tri = m_data->m_Triangles[i];

		// �O�p�`�Ƌ��̓����蔻��
		if (CheckSphere2Triangle(localsphere, tri, &temp_inter))
		{// �q�b�g����
			hit = true;
			// �Փ˓_���狅�̒��S�ւ̃x�N�g��
			Vector3 sub = localsphere.m_center - temp_inter;
			// ���̒��S���O�p�`�ɂ߂肱��ł��鋗�����v�Z
			temp_over_length = sub.Dot(-tri.Normal);

			// �߂肱�݋�������܂łōŏ��Ȃ�
			if (temp_over_length < over_length)
			{
				// �q�b�g���W�A�@���A�߂肱�݋������L�^
				l_inter = temp_inter;
				l_normal = tri.Normal;
				over_length = temp_over_length;
			}
		}
	}

	if (hit)
	{
		// ���������f�����W�n���烏�[���h���W�n�ł̒����ɕϊ�
		over_length *= scale;

		// ���[���h�s����擾
		const Matrix& localworld = m_obj.GetWorld();

		// �r�˃x�N�g���̌v�Z
		if (reject != nullptr)
		{
			// �n�`�̖@�����������f�����W�n���烏�[���h���W�n�ɕϊ�
			*reject = Vector3::TransformNormal(l_normal, localworld);
			reject->Normalize();
			// �߂荞�ݕ����������o���x�N�g�����v�Z
			const float extra = 0.05f;
			float reject_distance = sphere.m_radius + over_length + extra;
			*reject = (*reject) * reject_distance;
		}
	}

	return hit;
}

//--------------------------------------------------------------------------------------
// �n�`�Ɛ����̌�������
// segment : ����
// �i�o�́jinter : ��_�i�|���S���̕��ʏ�ŁA�_�Ƃ̍Đڋߓ_�̍��W��Ԃ��j
//--------------------------------------------------------------------------------------
bool LandShape::IntersectSegment(const Segment& segment, Vector3* inter)
{
	if (m_data == nullptr) return false;

	// �q�b�g�t���O��������
	bool hit = false;
	// �傫�������ŏ�����
	float distance = 1.0e5;
	// �p�x����p�ɒn�ʂƂ݂Ȃ��p�x�̌��E�l<�x>
	const float limit_angle = XMConvertToRadians(30.0f);
	Vector3 l_inter;

	// �R�s�[
	Segment localSegment = segment;
	// ���������[���h���W���烂�f�����W�n�Ɉ�������
	localSegment.m_start = Vector3::Transform(localSegment.m_start, m_worldLocal);
	localSegment.m_end = Vector3::Transform(localSegment.m_end, m_worldLocal);
	// �����̕����x�N�g�����擾
	Vector3 segmentNormal = localSegment.m_end - localSegment.m_start;
	segmentNormal.Normalize();

	// �O�p�`�̐�
	int nTri = m_data->m_Triangles.size();
	// �S�Ă̎O�p�`�ɂ���
	for (int i = 0; i < nTri; i++)
	{
		float temp_distance;
		Vector3 temp_inter;

		// ������x�N�g���Ɩ@���̓���
		// �������P�̃x�N�g���Q���m�̓��ς́A�R�T�C���i�x�N�g���̓��ς̒�`���j
		float cosine = -segmentNormal.Dot(m_data->m_Triangles[i].Normal);
		//// �R�T�C���l����A������Ƃ̊p�x�����v�Z
		//float angle = acosf(cosine);
		//// ������Ƃ̊p�x�����E�p���傫����΁A�ʂ̌X�����傫���̂ŁA�n�ʂƂ݂Ȃ����X�L�b�v
		//if ( angle > limit_angle ) continue;

		//--������--
		const float limit_cosine = cosf(limit_angle);
		// �R�T�C�����P�̂Ƃ��Ƀx�N�g���Ԃ̊p�x��0�x�ł���A�x�N�g���̊p�x�����傫���قǁA�R�T�C���͏������̂ŁA
		// �R�T�C���l�̂܂ܔ�r����ƁA�p�x�̔�r�̏ꍇ�Ƒ召�֌W���t�ł���
		// �܂�A�R�T�C���l�����l��菬������΁A�ʂ̌X�����傫���̂ŁA�n�ʂƂ݂Ȃ����X�L�b�v
		if (cosine < limit_cosine) continue;
		//--�����ł����܂�--

		// �����ƎO�p�`�i�|���S���j�̌�������
		if (CheckSegment2Triangle(localSegment, m_data->m_Triangles[i], &temp_inter))
		{
			hit = true;
			// �����̎n�_�ƏՓ˓_�̋������v�Z�i�߂肱�݋����j
			temp_distance = Vector3::Distance(localSegment.m_start, temp_inter);
			// �߂肱�݋�������܂łōŏ��Ȃ�
			if (temp_distance < distance)
			{
				// �Փ˓_�̍��W�A�߂肱�݋������L�^
				l_inter = temp_inter;
				distance = temp_distance;
			}
		}
	}

	if (hit && inter != nullptr)
	{
		// �Փ˓_�̍��W�����f�����W�n���烏�[���h���W�n�ɕϊ�
		const Matrix& localworld = m_obj.GetWorld();
		*inter = Vector3::Transform(l_inter, localworld);
	}

	return hit;
}