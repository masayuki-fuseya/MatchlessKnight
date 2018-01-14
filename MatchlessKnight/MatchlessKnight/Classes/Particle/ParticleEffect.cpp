//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	ParticleEffect.cpp
//!
//!	@brief	�p�[�e�B�N���G�t�F�N�g�N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/11/10
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "ParticleEffect.h"
#include "ParticleEffectManager.h"
#include <WICTextureLoader.h>


using namespace MasaboLib;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;


//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
ParticleEffect::ParticleEffect()
	: m_frameCount(0)
{
}



//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�p�[�e�B�N���̏�񂪓������\����
//!
//!	@return		�Ȃ�
//**********************************************************************
void ParticleEffect::Initialize(ParticleData& data)
{
	auto graphics = Graphics::GetInstance();

	auto device = graphics->GetDevice();
	auto context = graphics->GetContext();

	// �v���~�e�B�u�o�b�`�쐬
	// �e���_�Ɋ܂܂���񂪁A�ʒu�E�F�E�e�N�X�`��UV
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context, 1, ParticleEffectManager::PARTICLE_NUM_MAX);

	m_data = std::make_unique<ParticleData>(data);

	// ���_�f�[�^�ǉ�
	VertexPositionColorTexture vertexData;
	vertexData.color = m_data->m_startColor;
	vertexData.position = m_data->m_pos;
	vertexData.textureCoordinate = Vector2(m_data->m_startScale, m_data->m_startRadian);
	m_vertice = std::make_unique<VertexPositionColorTexture>(vertexData);

	m_commonStates = std::make_unique<CommonStates>(device);

	// �e�N�X�`���T���v���[�쐬
	D3D11_SAMPLER_DESC sam;
	// �S�Ă̕ϐ���0������(�\���̂ɂ̂ݎg�p)
	ZeroMemory(&sam, sizeof(sam));
	sam.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sam.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sam.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sam.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	if (FAILED(device->CreateSamplerState(&sam, m_sampler.ReleaseAndGetAddressOf())))
	{
		// �G���[
		MessageBox(0, L"CreateSamplerState Failed.", NULL, MB_OK);
		return;
	}

	// ���Z�`��p�̃u�����h�X�e�[�g���쐬
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
		// �G���[
		MessageBox(0, L"CreateBlendState Failed.", NULL, MB_OK);
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
void ParticleEffect::Update(const StepTimer& timer)
{
	m_frameCount++;

	// �����x
	m_data->m_velocity += m_data->m_accel;
	// �ړ�
	m_vertice->position = m_vertice->position + m_data->m_velocity;
	// �F�̃A�j���[�V����
	m_vertice->color = m_data->m_startColor + (m_data->m_endColor - m_data->m_startColor) *
		(m_frameCount / (60.0f * m_data->m_disappearanceTime));
	// �傫���̃A�j���[�V����
	m_vertice->textureCoordinate.x = m_data->m_startScale + (m_data->m_endScale - m_data->m_startScale) *
		(m_frameCount / (60.0f * m_data->m_disappearanceTime));
	// �p�x�̃A�j���[�V����
	m_vertice->textureCoordinate.y = m_data->m_startRadian + (m_data->m_endRadian - m_data->m_startRadian) *
		(m_frameCount / (60.0f * m_data->m_disappearanceTime));
}



//**********************************************************************
//!	@brief		�`�揈��
//!
//!	@param[in]	�J����
//!
//!	@return		�Ȃ�
//**********************************************************************
void ParticleEffect::Render(Camera* camera)
{
	auto graphics = Graphics::GetInstance();

	auto device = graphics->GetDevice();
	auto context = graphics->GetContext();

	context->IASetInputLayout(ParticleEffectManager::GetInstance()->GetInputLayout().Get());

	// �A�ʏ���
	context->RSSetState(m_commonStates->CullNone());
	// �A���t�@�u�����h�ݒ�
	//context->OMSetBlendState(m_commonStates->NonPremultiplied(), nullptr, 0xffffffff);
	// ���Z�`��
	context->OMSetBlendState(m_commonStates->Additive(), nullptr, 0xffffffff);
	// ���Z�`��
	//context->OMSetBlendState(m_BlendStateSubtract.Get(), nullptr, 0xffffff);
	// �[�x�e�X�g�ݒ�
	context->OMSetDepthStencilState(m_commonStates->DepthNone(), 0);

	context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	// ���_�f�[�^�����ׂēn���ĕ`�悷��
	m_primitiveBatch->Begin();
	m_primitiveBatch->Draw(D3D_PRIMITIVE_TOPOLOGY_POINTLIST, m_vertice.get(), 1);
	m_primitiveBatch->End();
}



//**********************************************************************
//!	@brief		�I������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void ParticleEffect::Finalize()
{
}



//**********************************************************************
//!	@brief		���Ŏ��Ԃ��߂�����
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		true:�߂���
//!	@return		false:�߂��Ă��Ȃ�
//**********************************************************************
bool ParticleEffect::IsEnded()
{
	if (m_data->m_disappearanceTime * 60.0f < m_frameCount)
	{
		return true;
	}

	return false;
}
