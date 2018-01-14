//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	ParticleEffectManager.cpp
//!
//!	@brief	�p�[�e�B�N���G�t�F�N�g�Ǘ��N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/11/06
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "ParticleEffectManager.h"
#include <WICTextureLoader.h>

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace MasaboLib;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

// �ÓI�����o�ϐ��̒�` ====================================================
// �p�[�e�B�N���̍ő吔
const int ParticleEffectManager::PARTICLE_NUM_MAX = 10000;
// ���̓��C�A�E�g�̒�`
const std::vector<D3D11_INPUT_ELEMENT_DESC> ParticleEffectManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,									D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(Vector3),						D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(Vector3) + sizeof(Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

std::unique_ptr<ParticleEffectManager> ParticleEffectManager::m_instance = nullptr;


//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void ParticleEffectManager::Initialize()
{
	auto graphics = MasaboLib::Graphics::GetInstance();

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	auto VSData = BinLoader::Load(L"Resources/Shaders/ParticleVS.cso");
	auto GSData = BinLoader::Load(L"Resources/Shaders/ParticleGS.cso");
	auto PSData = BinLoader::Load(L"Resources/Shaders/ParticlePS.cso");


	auto device = graphics->GetDevice();
	//ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();

	// ���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.data(), VSData.size(), NULL, m_VertexShader.ReleaseAndGetAddressOf())))
	{
		// �G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.data(), GSData.size(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{
		// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}

	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.data(), PSData.size(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{
		// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	// ���_�t�H�[�}�b�g���w�肵�ē��̓��C�A�E�g�쐬
	device->CreateInputLayout(&INPUT_LAYOUT[0], INPUT_LAYOUT.size(), VSData.data(), VSData.size(), m_inputLayout.GetAddressOf());

	// �p�[�e�B�N���̍ő吔�����߂�
	m_particles.reserve(PARTICLE_NUM_MAX);

	// �V�F�[�_�ɋ��ʃf�[�^��n�����߂̒萔�o�b�t�@���쐬
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Constants);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;
	if (FAILED(device->CreateBuffer(&cb, nullptr, m_constantBuffer.ReleaseAndGetAddressOf())))
	{
		// �G���[
		MessageBox(0, L"CreateBuffer Failed.", NULL, MB_OK);
		return;
	}

	// ����Ă݂悤�@ /////////////////////////////////////////////////////

	// ��
	//for (int i = 0; i < 1000; i++)
	//{
	//	// 1���̒��_�f�[�^
	//	VertexPositionColorTexture vertexData;
	//	vertexData.position = Vector3(-0.5f + i / 1000.0f, 0, 0);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate = Vector2(0, 0);
	//	m_Vertices.push_back(vertexData);
	//}

	// �\��
	//for (int i = 0; i < 4000; i++)
	//{
	//	// 1���̒��_�f�[�^
	//	VertexPositionColorTexture vertexData;
	//	// ����
	//	if (i < 2000)
	//	{
	//		vertexData.position = Vector3(-1.0f + i / 1000.0f, 0, 0);
	//	}
	//	// �c��
	//	else
	//	{
	//		vertexData.position = Vector3(0, -1.0f + (i - 2000) / 1000.0f, 0);
	//	}
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate = Vector2(0, 0);
	//	m_Vertices.push_back(vertexData);
	//}

	// �~��
	//for (int i = 0; i < 4000; i++)
	//{
	//	// 1���̒��_�f�[�^
	//	VertexPositionColorTexture vertexData;
	//	// ��������E��
	//	if (i < 2000)
	//	{
	//		vertexData.position = Vector3(-1.0f + i / 1000.0f, -1.0f + i / 1000.0f, 0);
	//	}
	//	// ���ォ��E��
	//	else
	//	{
	//		vertexData.position = Vector3(-1.0f + (i - 2000) / 1000.0f, 1.0f - (i - 2000) / 1000.0f, 0);
	//	}
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate = Vector2(0, 0);
	//	m_Vertices.push_back(vertexData);
	//}

	// �ȉ~
	//for (int i = 0; i < 4000; i++)
	//{
	//	float radian = XM_PIDIV2 * i / 1000.0f;
	//
	//	// 1���̒��_�f�[�^
	//	VertexPositionColorTexture vertexData;
	//	vertexData.position = Vector3(sin(radian) * 0.5f, cos(radian) * 0.5f, 0);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate = Vector2(0, 0);
	//	m_Vertices.push_back(vertexData);
	//}

	// �^�~
	//for (int i = 0; i < 4000; i++)
	//{
	//	RECT rect = DeviceResources::GetInstance()->GetOutputSize();
	//	float width = rect.right - rect.left;
	//	float height = rect.top - rect.bottom;
	//	float aspect = height / width;
	//	float radian = XM_PIDIV2 * i / 1000.0f;

	//	// 1���̒��_�f�[�^
	//	VertexPositionColorTexture vertexData;
	//	vertexData.position = Vector3(sin(radian) * 0.5f * aspect, cos(radian) * 0.5f, 0);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate = Vector2(0, 0);
	//	m_Vertices.push_back(vertexData);
	//}

	///////////////////////////////////////////////////////////////////////

	//VertexPositionColorTexture vertexData;
	// ����Ă݂悤�E ////////////////////////////////

	// ����5�\��
	//for (int i = 0; i < 5; i++)
	//{
	//	vertexData.position = Vector3(-3.0f + i * 1.5f, 0, 1);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate.x = 1;
	//	vertexData.textureCoordinate.y = 1;
	//	m_Vertices.push_back(vertexData);
	//}

	// �~�`�ɕ\��
	//for (int i = 0; i < 20; i++)
	//{
	//	vertexData.position = Vector3(cos(XM_2PI * i / 20.0f), sin(XM_2PI * i / 20.0f), 1);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate.x = 1;
	//	vertexData.textureCoordinate.y = 0;
	//	m_Vertices.push_back(vertexData);
	//}

	// 8�̎��ɕ\��
	//for (int i = 0; i < 20; i++)
	//{
	//	vertexData.position = Vector3(cos(XM_2PI * i / 20.0f), sin(XM_2PI * i / 20.0f * 2) / 2.0f, 1);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	vertexData.textureCoordinate.x = 1;
	//	vertexData.textureCoordinate.y = 0;
	//	m_Vertices.push_back(vertexData);
	//}

	//////////////////////////////////////////////////

	// ����Ă݂悤�F ////////////////////////////////
	// �~�`�ɕ\��
	//for (int i = 0; i < 100; i++)
	//{
	//	vertexData.position = Vector3(cos(XM_2PI * i / 100.0f), sin(XM_2PI * i / 100.0f), 1);
	//	vertexData.color = Vector4(1, 1, 1, 1);
	//	// ���Ԃ���
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

	//// 1�_�� ����
	//VertexPositionColorTexture vertexData;
	//vertexData.position = Vector3(0, -1.0f, 1);
	//vertexData.color = Vector4(1, 1, 1, 1);
	//// ����Ă݂悤�A ///////////////////
	////vertexData.color = Vector4(1, 0, 0, 1);
	///////////////////////////////////////
	//vertexData.textureCoordinate = Vector2(0, 1);
	//// ����Ă݂悤�C ///////////////////

	//// ���ゾ���\��
	////vertexData.textureCoordinate = Vector2(0, 0.5f);

	//// 2�~3�ŕ\��
	////vertexData.textureCoordinate = Vector2(0, 2.0f);

	///////////////////////////////////////
	//m_Vertices.push_back(vertexData);

	//// 2�_�� �E��
	//vertexData.position = Vector3(1.0f, -1.0f, 1);
	//vertexData.color = Vector4(1, 1, 1, 1);
	//// ����Ă݂悤�A ///////////////////
	////vertexData.color = Vector4(1, 0, 0, 1);
	///////////////////////////////////////
	//vertexData.textureCoordinate = Vector2(1, 1);
	//// ����Ă݂悤�C ///////////////////

	//// ���ゾ���\��
	////vertexData.textureCoordinate = Vector2(0.5f, 0.5f);

	//// 2�~3�ŕ\��
	////vertexData.textureCoordinate = Vector2(3.0f, 2.0f);

	///////////////////////////////////////
	//m_Vertices.push_back(vertexData);

	//// 3�_�� ����
	//vertexData.position = Vector3(0, 0, 1);
	//vertexData.color = Vector4(1, 1, 1, 1);
	//// ����Ă݂悤�A ///////////////////
	////vertexData.color = Vector4(1, 0, 0, 1);
	///////////////////////////////////////
	//vertexData.textureCoordinate = Vector2(0, 0);
	//// ����Ă݂悤�C ///////////////////

	//// ���ゾ���\��
	////vertexData.textureCoordinate = Vector2(0, 0);

	//// 2�~3�ŕ\��
	////vertexData.textureCoordinate = Vector2(0, 0);

	///////////////////////////////////////
	//m_Vertices.push_back(vertexData);

	//// 4�_�� �E��
	//vertexData.position = Vector3(1.0f, 0, 1);
	//vertexData.color = Vector4(1, 1, 1, 1);
	//vertexData.textureCoordinate = Vector2(1, 0);
	//// ����Ă݂悤�C ///////////////////

	//// ���ゾ���\��
	////vertexData.textureCoordinate = Vector2(0.5f, 0);

	//// 2�~3�ŕ\��
	////vertexData.textureCoordinate = Vector2(3.0f, 0);

	///////////////////////////////////////
	//m_Vertices.push_back(vertexData);
}



//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�X�e�b�v�^�C�}�[
//!
//!	@return		�Ȃ�
//**********************************************************************
void ParticleEffectManager::Update(const StepTimer& timer)
{
	// ����Ă݂悤�A ///////////////////////////////////////////

	// �E�Ɉړ�
	//for (auto itr = m_Vertices.begin(); itr != m_Vertices.end(); itr++)
	//{
	//	itr->position = itr->position + Vector3(0.01f, 0.0f, 0.0f);
	//}

	// �Ԃ����
	//for (auto itr = m_Vertices.begin(); itr != m_Vertices.end(); itr++)
	//{
	//	itr->color.x -= 0.01f;
	//	itr->color.z += 0.01f;
	//}

	/////////////////////////////////////////////////////////////

	// ����Ă݂悤�C ///////////////////////////////////////////

	// �E���獶�ɗ����A�j���[�V����
	//for (auto itr = m_Vertices.begin(); itr != m_Vertices.end(); itr++)
	//{
	//	itr->textureCoordinate.x += 0.05f;
	//}

	// �摜�̐^�񒆂𒆐S�ɉ�]
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

	// ����Ă݂悤�E ///////////////////////////////////////////

	// ������E�ɃE�F�[�u
	//static float param = 0.0f;
	//param += XMConvertToRadians(6.0f);
	//int i = 0;
	//for (VertexPositionColorTexture& vertex : m_Vertices)
	//{
	//	vertex.textureCoordinate.x = (sin(param - i * XMConvertToRadians(72.0f)) + 1) / 2.0f;
	//	i++;
	//}

	// �~�`�ɃE�F�[�u
	//static float param = 0.0f;
	//param += XMConvertToRadians(6.0f);
	//int i = 0;
	//for (VertexPositionColorTexture& vertex : m_Vertices)
	//{
	//	vertex.textureCoordinate.x = (sin(param - i * XMConvertToRadians(18.0f)) + 1) / 10;
	//	i++;
	//}

	// 8�̎��ɃE�F�[�u
	//static float param = 0.0f;
	//param += XMConvertToRadians(6.0f);
	//int i = 0;
	//for (VertexPositionColorTexture& vertex : m_Vertices)
	//{
	//	vertex.textureCoordinate.x = (sin(param - i * XMConvertToRadians(18.0f)) + 1) / 10;
	//	i++;
	//}

	/////////////////////////////////////////////////////////////

	// ����Ă݂悤�F ///////////////////////////////////////////

	// ���̌`
	//static float param = 0.0f;
	//param += XMConvertToRadians(6.0f);
	//int i = 0;
	//for (VertexPositionColorTexture& vertex : m_Vertices)
	//{
	//	// �X�P�[��
	//	vertex.textureCoordinate.x = (sin(param - i * XMConvertToRadians(3.6f)) + 1) / 4.0f;
	//	// ��]
	//	//vertex.textureCoordinate.y += XMConvertToRadians(2.0f);

	//	// �O���f�[�V���� //////////////////////////////
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
//!	@brief		�`�揈��
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void ParticleEffectManager::Render()
{
	auto graphics = Graphics::GetInstance();

	auto context = graphics->GetContext();

	Matrix world = Matrix::Identity;
	Matrix view = m_camera->GetView();
	Matrix proj = m_camera->GetProj();

	Matrix wvp = world * view * proj;
	// �V�F�[�_�̒萔�o�b�t�@�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		Constants constants;

		constants.WVP = wvp;
		constants.Billboard = m_camera->GetBillboard();

		memcpy_s(pData.pData, pData.RowPitch, &constants, sizeof(Constants));

		context->Unmap(m_constantBuffer.Get(), 0);
	}

	// �萔�o�b�t�@���ǂ̃V�F�[�_�Ŏg����
	context->VSSetConstantBuffers(0, 0, nullptr);
	context->GSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
	context->PSSetConstantBuffers(0, 0, nullptr);

	// �f�o�C�X�R���e�L�X�g�ɁA�`��Ɏg�p����V�F�[�_���w��
	context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_PixelShader.Get(), nullptr, 0);

	for (auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
	{
		(*itr)->Render(m_camera);
	}

	// �V�F�[�_���N���A
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}



//**********************************************************************
//!	@brief		�p�[�e�B�N����ǉ�����
//!
//!	@param[in]	�ǉ�����p�[�e�B�N��
//!
//!	@return		�Ȃ�
//**********************************************************************
void ParticleEffectManager::Entry(std::unique_ptr<ParticleEffect>&& particle)
{
	if (m_particles.size() < PARTICLE_NUM_MAX)
	{
		m_particles.push_back(std::move(particle));
	}
}



//**********************************************************************
//!	@brief		�e�N�X�`������
//!
//!	@param[in]	�e�N�X�`���ԍ�, �t�@�C���̃p�X
//!
//!	@return		�������ꂽ�e�N�X�`��
//**********************************************************************
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ParticleEffectManager::CreateTexture(int textureNumber, const wchar_t* filepath)
{
	auto device = Graphics::GetInstance()->GetDevice();

	if (m_textures.count(textureNumber) == 0)
	{
		// �e�N�X�`���ǂݍ���
		if (FAILED(CreateWICTextureFromFile(device, filepath, nullptr, m_textures[textureNumber].ReleaseAndGetAddressOf())))
		{
			// �G���[
			MessageBox(0, L"CreateWICTextureFromFile Failed.", NULL, MB_OK);
			return nullptr;
		}
	}

	return m_textures[textureNumber];
}



//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
ParticleEffectManager::ParticleEffectManager()
	: m_camera(nullptr)
{
}
