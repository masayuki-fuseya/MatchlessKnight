//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	ParticleFactory.cpp
//!
//!	@brief	�p�[�e�B�N���t�@�N�g���[�N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/11/13
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "ParticleFactory.h"
#include "ParticleEffectManager.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace MasaboLib;
using namespace std;


//**********************************************************************
//!	@brief		�p�[�e�B�N���𐶐�����
//!
//!	@param[in]	�e�N�X�`���ԍ�, �p�[�e�B�N���̏�񂪓������\����, �t�@�C���̃p�X
//!
//!	@return		�������ꂽ�p�[�e�B�N��
//**********************************************************************
unique_ptr<ParticleEffect>&& ParticleFactory::Create(int textureNumber, ParticleEffect::ParticleData& data, const wchar_t* filepath)
{
	std::unique_ptr<ParticleEffect> particle = make_unique<ParticleEffect>();
	particle->Initialize(data);
	auto texture = ParticleEffectManager::GetInstance()->CreateTexture(textureNumber, filepath);
	particle->SetTexture(texture);

	return move(particle);
}
