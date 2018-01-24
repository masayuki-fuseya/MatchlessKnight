//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	ParticleEffect.h
//!
//!	@brief	�p�[�e�B�N���G�t�F�N�g�N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/11/10
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef MASABO_PARTICLE_EFFECT
#define MASABO_PARTICLE_EFFECT

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "MasaboLib.h"
#include <CommonStates.h>
#include <d3d11.h>
#include <memory>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <SimpleMath.h>
#include <wrl.h>


namespace MasaboLib
{
	class ParticleEffect
	{
	public:
		// �p�[�e�B�N���f�[�^
		struct ParticleData
		{
			// ���W
			DirectX::SimpleMath::Vector3 m_pos;
			// ���x
			DirectX::SimpleMath::Vector3 m_velocity;
			// �����x
			DirectX::SimpleMath::Vector3 m_accel;
			// �F
			DirectX::SimpleMath::Vector4 m_startColor;
			DirectX::SimpleMath::Vector4 m_endColor;
			// �傫��
			float m_startScale;
			float m_endScale;
			// �p�x
			float m_startRadian;
			float m_endRadian;
			// ���Ŏ���
			float m_disappearanceTime;

			ParticleData()
				: m_startColor(1, 1, 1, 1)
				, m_endColor(1, 1, 1, 1)
				, m_startScale(1.0f)
				, m_endScale(1.0f)
				, m_startRadian(0.0f)
				, m_endRadian(0.0f)
				, m_disappearanceTime(1.0f) {}

			void Initialize()
			{
				m_pos = DirectX::SimpleMath::Vector3::Zero;
				m_velocity = DirectX::SimpleMath::Vector3::Zero;
				m_accel = DirectX::SimpleMath::Vector3::Zero;
				m_startColor = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
				m_endColor = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
				m_startScale = 1.0f;
				m_endScale = 1.0f;
				m_startRadian = 0.0f;
				m_endRadian = 0.0f;
				m_disappearanceTime = 1.0f;
			}
		};
	private:
		// �v���~�e�B�u�o�b�`
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
		// ���_�f�[�^
		std::unique_ptr<DirectX::VertexPositionColorTexture> m_vertice;
		// �ėp�`��ݒ�
		std::unique_ptr<DirectX::CommonStates> m_commonStates;
		// �e�N�X�`��
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		// �e�N�X�`���T���v���[
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

		// ���Z�`��X�e�[�g
		Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendStateSubtract;

		// �p�[�e�B�N���f�[�^
		std::unique_ptr<ParticleData> m_data;
		// �t���[����
		int m_frameCount;
	public:
		ParticleEffect();
		~ParticleEffect() {}

		void Initialize(ParticleData& data);
		void Update(const MasaboLib::DX::StepTimer& timer);
		void Render();
		void Finalize();

		bool IsEnded();

		void SetTexture(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& texture)
		{
			m_texture = texture;
		}
	};
}

#endif // !MASABO_PARTICLE_EFFECT
