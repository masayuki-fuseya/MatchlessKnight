//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	ParticleFactory.h
//!
//!	@brief	�p�[�e�B�N���t�@�N�g���[�N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/11/13
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef MASABO_PARTICLE_FACTORY
#define MASABO_PARTICLE_FACTORY

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "ParticleEffect.h"
#include <memory>


namespace MasaboLib
{
	class ParticleFactory
	{
	public:
		// �p�[�e�B�N���𐶐�����
		static std::unique_ptr<ParticleEffect>&& Create(int textureNumber, ParticleEffect::ParticleData& data, const wchar_t* filepath);
	};
}

#endif // !MASABO_PARTICLE_FACTORY
