//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	ParticleEffectManager.h
//!
//!	@brief	�p�[�e�B�N���G�t�F�N�g�Ǘ��N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/11/06
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef MASABO_PARTICLE_EFFECT_MANAGER
#define MASABO_PARTICLE_EFFECT_MANAGER

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "MasaboLib.h"
#include "ParticleEffect.h"
#include <d3d11.h>
#include <map>
#include <memory>
#include <SimpleMath.h>
#include <vector>
#include <wrl.h>


namespace MasaboLib
{
	class ParticleEffectManager :public Singleton<ParticleEffectManager>
	{
	public:
		// �p�[�e�B�N���̍ő吔
		static const int PARTICLE_NUM_MAX;
		// ���̓��C�A�E�g�̒�`
		static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
		
		// �萔�o�b�t�@
		struct Constants
		{
			//World View Projection �����s��
			DirectX::SimpleMath::Matrix WVP;
			// �r���{�[�h�s��
			DirectX::SimpleMath::Matrix Billboard;
		};
	private:
		friend class Singleton<ParticleEffectManager>;

		// �C���X�^���X
		static std::unique_ptr<ParticleEffectManager> m_instance;

		// ���_�V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		// �W�I���g���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;
		// �s�N�Z���V�F�[�_
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;

		// ���̓��C�A�E�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		// �萔�o�b�t�@�I�u�W�F�N�g
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

		// �e�N�X�`��
		std::map<int, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textures;

		// �J����
		MasaboLib::Camera* m_camera;

		// �p�[�e�B�N���̏W����
		std::vector<std::unique_ptr<ParticleEffect>> m_particles;
	public:
		// �C���X�^���X���擾����
		static ParticleEffectManager* GetInstance()
		{
			// ��������ĂȂ���ΐ�������
			if (!m_instance.get())
			{
				m_instance.reset(new ParticleEffectManager());
			}
			return m_instance.get();
		}

		void Initialize();
		void Update(const MasaboLib::DX::StepTimer& timer);
		void Render();

		// �p�[�e�B�N���o�^
		void Entry(std::unique_ptr<ParticleEffect>&& particle);

		// �e�N�X�`���𐶐�����
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> CreateTexture(int textureNumber, const wchar_t* filepath);

		// �Q�b�^�[ ////////////////////////////////////////////

		// ���̓��C�A�E�g���擾����
		Microsoft::WRL::ComPtr<ID3D11InputLayout> GetInputLayout()
		{
			return m_inputLayout;
		}

		////////////////////////////////////////////////////////

		// �Z�b�^�[ ////////////////////////////////////////////

		// �J������ݒ肷��
		void SetCamera(MasaboLib::Camera* camera)
		{
			m_camera = camera;
		}

		////////////////////////////////////////////////////////
	private:
		ParticleEffectManager();
	};
}

#endif // !MASABO_PARTICLE_EFFECT_MANAGER
