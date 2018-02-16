//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	FolloCamera.h
//!
//!	@brief	�v���C���[�ɒǏ]����J�����N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/05/15
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef FOLLOW_CAMERA
#define FOLLOW_CAMERA

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "MasaboLib.h"
#include "..\Objects\Character\Player\Player.h"
#include <d3d11.h>
#include <SimpleMath.h>


class FollowCamera :public MasaboLib::Camera
{
public:
	// �v���C���[�Ƃ̋���
	static const float CAMERA_DISTANCE;
private:
	// �Ǐ]�Ώ�
	Player* m_target;
	// �Ǐ]�Ώۂ̍��W
	DirectX::SimpleMath::Vector3 m_targetPos;
	// �Ǐ]�Ώۂ̊p�x
	float m_targetAngle;
public:
	FollowCamera(int width, int height);
	~FollowCamera() {}

	void Initialize();
	void Update() override;

	// �Z�b�^�[ //////////////////////////////////

	// �Ǐ]�Ώۂ�ݒ肷��
	void SetTarget(Player* target)
	{
		m_target = target;
	}

	//////////////////////////////////////////////
};

#endif // !FOLLOW_CAMERA
