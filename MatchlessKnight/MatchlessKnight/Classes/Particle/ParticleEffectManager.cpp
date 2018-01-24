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
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

// �ÓI�����o�ϐ��̒�` ====================================================
// �p�[�e�B�N���̍ő吔
const int ParticleEffectManager::PARTICLE_NUM_MAX = 10000;
// ���̓��C�A�E�g�̒�`
const vector<D3D11_INPUT_ELEMENT_DESC> ParticleEffectManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,									D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(Vector3),						D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(Vector3) + sizeof(Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

unique_ptr<ParticleEffectManager> ParticleEffectManager::m_instance = nullptr;


//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void ParticleEffectManager::Initialize()
{
	auto graphics = Graphics::GetInstance();

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	auto VSData = BinLoader::Load(L"Resources/CSO/ParticleVS.cso");
	auto GSData = BinLoader::Load(L"Resources/CSO/ParticleGS.cso");
	auto PSData = BinLoader::Load(L"Resources/CSO/ParticlePS.cso");


	auto device = graphics->GetDevice();

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
		(*itr)->Render();
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
void ParticleEffectManager::Entry(unique_ptr<ParticleEffect>&& particle)
{
	if (m_particles.size() < PARTICLE_NUM_MAX)
	{
		m_particles.push_back(move(particle));
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
