//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayerPartsFactory.cpp
//!
//!	@brief	�v���C���[�p�[�c�����H��N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/08/02
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "PlayerPartsFactory.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerBody.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerHead.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftCalf.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftFoot.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftForeArm.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftHand.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftThigh.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerLeftUpperArm.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightCalf.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightFoot.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightForeArm.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightHand.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightThigh.h"
#include "..\Objects\Character\Player\PlayerParts\PlayerRightUpperArm.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace std;


//**********************************************************************
//!	@brief		�v���C���[�p�[�c�𐶐�����
//!
//!	@param[in]	�v���C���[�p�[�c�̎��
//!
//!	@return		�������ꂽ�v���C���[�p�[�c
//**********************************************************************
unique_ptr<Player>&& PlayerPartsFactory::Create(Player::PARTS parts)
{
	unique_ptr<Player> playerParts;

	switch (parts)
	{
	// ��
	case Player::HEAD:
		playerParts = make_unique<PlayerHead>();
		break;
	// ��
	case Player::BODY:
		playerParts = make_unique<PlayerBody>();
		break;
	// �E��r
	case Player::RIGHT_UPPER_ARM:
		playerParts = make_unique<PlayerRightUpperArm>();
		break;
	// �E�O�r��
	case Player::RIGHT_FORE_ARM:
		playerParts = make_unique<PlayerRightForeArm>();
		break;
	// �E��
	case Player::RIGHT_HAND:
		playerParts = make_unique<PlayerRightHand>();
		break;
	// ����r
	case Player::LEFT_UPPER_ARM:
		playerParts = make_unique<PlayerLeftUpperArm>();
		break;
	// ���O�r��
	case Player::LEFT_FORE_ARM:
		playerParts = make_unique<PlayerLeftForeArm>();
		break;
	// ����
	case Player::LEFT_HAND:
		playerParts = make_unique<PlayerLeftHand>();
		break;
	// �E���
	case Player::RIGHT_THIGH:
		playerParts = make_unique<PlayerRightThigh>();
		break;
	// �E�ӂ���͂�
	case Player::RIGHT_CALF:
		playerParts = make_unique<PlayerRightCalf>();
		break;
	// �E��
	case Player::RIGHT_FOOT:
		playerParts = make_unique<PlayerRightFoot>();
		break;
	// �����
	case Player::LEFT_THIGH:
		playerParts = make_unique<PlayerLeftThigh>();
		break;
	// ���ӂ���͂�
	case Player::LEFT_CALF:
		playerParts = make_unique<PlayerLeftCalf>();
		break;
	// ����
	case Player::LEFT_FOOT:
		playerParts = make_unique<PlayerLeftFoot>();
		break;
	}

	// �v���C���[�p�[�c������������
	playerParts->Initialize();

	// ���L����n���ĕԂ�
	return move(playerParts);
}
