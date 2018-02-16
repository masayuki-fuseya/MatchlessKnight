//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Player.cpp
//!
//!	@brief	�v���C���[�N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/07/20
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "MasaboLib.h"
#include "Player.h"
#include "PlayerParts\PlayerBody.h"
#include "PlayerParts\PlayerHead.h"
#include "PlayerParts\PlayerLeftCalf.h"
#include "PlayerParts\PlayerLeftFoot.h"
#include "PlayerParts\PlayerLeftForeArm.h"
#include "PlayerParts\PlayerLeftHand.h"
#include "PlayerParts\PlayerLeftThigh.h"
#include "PlayerParts\PlayerLeftUpperArm.h"
#include "PlayerParts\PlayerRightCalf.h"
#include "PlayerParts\PlayerRightFoot.h"
#include "PlayerParts\PlayerRightForeArm.h"
#include "PlayerParts\PlayerRightHand.h"
#include "PlayerParts\PlayerRightThigh.h"
#include "PlayerParts\PlayerRightUpperArm.h"
#include "..\..\..\ADX2\ADX2Le.h"
#include "..\..\..\ADX2\PlayerSE.h"
#include "..\..\..\State\AttackingState.h"
#include "..\..\..\State\StandingState.h"
#include <d3d11.h>
#include <SimpleMath.h>

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
Player::Player()
{
}



//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Player::Initialize()
{
	// ���C�t������������
	m_life = 100;

	//�p�[�c��ǉ�����
	AddParts();

	// ���[�g�p�[�c������������
	m_rootParts->Initialize();

	m_scale = Vector3(0.7f);
	m_rotation = Vector3(0.0f, XM_PI, 0.0f);
	m_translation = Vector3(0.0f, 0.0f, 40.0f);

	// ��������������
	m_sword = make_unique<Sword>();
	m_sword->Initialize(this);

	// �X�e�[�g�p�^�[��������������
	StandingState::GetInstance()->Initialize(this);
	AttackingState::GetInstance()->Initialize(this);

	// �ŏ��͋N����Ԃɂ���
	ChangeState(StandingState::GetInstance());

	// �����ʒu���X�V����
	Update();

	// �����蔻��m�[�h������������
	m_collisionNodeBody.Initialize();
	// �v���C���[��e�ɐݒ肷��
	m_collisionNodeBody.SetParent(this);
	// ���W��ݒ肷��
	m_collisionNodeBody.SetTranslation(Vector3(0.0f, 3.0f, 0.0f));
	// ���a��ݒ肷��
	m_collisionNodeBody.SetLocalRadius(1.5f);
}



//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Player::Update()
{
	// ���݂̏�Ԃ��X�V����
	m_currentState->Execute();

	// �����蔻��m�[�h���X�V����
	m_collisionNodeBody.Update();

	// ����U��I������N����Ԃɂ���
	if (!m_sword->Update(this))
	{
		ChangeState(StandingState::GetInstance());
	}

	// �s��X�V����
	CalcMatrix();

	// �S�Ẵp�[�c���X�V����
	m_rootParts->Update(m_scale, m_rotation, m_translation);
}



//**********************************************************************
//!	@brief		�`�悷��
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Player::Render()
{
	// ���݂̏�Ԃ�`�悷��
	m_currentState->Render();
}



//**********************************************************************
//!	@brief		�I����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Player::Finalize()
{
	m_rootParts->Finalize();
}



//**********************************************************************
//!	@brief		�N����Ԃ̍X�V������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Player::UpdateStanding()
{
	// �L�[�{�[�h�X�e�[�g���擾����
	Keyboard::State state = MasaboLib::Input::GetInstance()->GetKeyboard()->GetState();

	Vector3 moveV;
	// ����]
	if (state.IsKeyDown(Keyboard::Keys::Left))
	{
		//float angle = m_rotation.y + 0.02f;
		//m_rotation = Vector3(0.0f, angle, 0.0f);
		m_rotation.y += 0.02f;
	}
	// �E��]
	if (state.IsKeyDown(Keyboard::Keys::Right))
	{
		//float angle = m_rotation.y - 0.02f;
		//m_rotation = Vector3(0.0f, angle, 0.0f);
		m_rotation.y -= 0.02f;
	}
	// �O�i
	if (state.IsKeyDown(Keyboard::Keys::Up))
	{
		moveV = Vector3(0.0f, 0.0f, 0.4f);
		// �ړ��x�N�g������]������
		moveV = Vector3::TransformNormal(moveV, GetWorld());
	}
	// ��i
	if (state.IsKeyDown(Keyboard::Keys::Down))
	{
		moveV = Vector3(0.0f, 0.0f, -0.4f);
		// �ړ��x�N�g������]������
		moveV = Vector3::TransformNormal(moveV, GetWorld());
	}
	// �U����ԂɈڍs
	if (MasaboLib::Input::GetInstance()->GetKeyboardTracker()->IsKeyPressed(Keyboard::Keys::Z))
	{
		// ����U��SE�̍Đ�
		ADX2Le::Play(CRI_PLAYER_ATTACK);

		ChangeState(AttackingState::GetInstance());
		m_sword->Wield();
	}

	// ���W�ړ�
	m_translation += moveV;
}



//**********************************************************************
//!	@brief		�U����Ԃ̍X�V������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Player::UpdateAttacking()
{
}



//**********************************************************************
//!	@brief		�N����Ԃ̕`�������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Player::RenderStanding()
{
	// ���[�g�p�[�c��`�悷��
	m_rootParts->Render();
	// ����`�悷��
	m_sword->Render();
}



//**********************************************************************
//!	@brief		�U����Ԃ̕`�������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Player::RenderAttacking()
{
	// ���[�g�p�[�c��`�悷��
	m_rootParts->Render();
	// ����`�悷��
	m_sword->Render();
}



//**********************************************************************
//!	@brief		�U������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		true:�U����
//!	@return		false:�U�����Ă��Ȃ�
//**********************************************************************
bool Player::IsAttack()
{
	// �U������������true��Ԃ�
	if (!m_sword->GetCanWield())
	{
		return true;
	}
	return false;
}



//**********************************************************************
//!	@brief		�p�[�c��ǉ�����
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void Player::AddParts()
{
	// ��
	m_rootParts = make_shared<Node>(new PlayerBody());

	// ��
	shared_ptr<INode> body = make_shared<Node>(new PlayerHead());
	m_rootParts->Add(move(body));

	// �E�r
	shared_ptr<INode> rightUpperArm = make_shared<Node>(new PlayerRightUpperArm());
	body->Add(move(rightUpperArm));
	shared_ptr<INode> rightForeArm = make_shared<Node>(new PlayerRightForeArm());
	rightUpperArm->Add(move(rightForeArm));
	rightForeArm->Add(make_shared<Leaf>(new PlayerRightHand()));

	// ���r
	shared_ptr<INode> leftUpperArm = make_shared<Node>(new PlayerLeftUpperArm());
	body->Add(move(leftUpperArm));
	shared_ptr<INode> leftForeArm = make_shared<Node>(new PlayerLeftForeArm());
	leftUpperArm->Add(move(leftForeArm));
	leftForeArm->Add(make_shared<Leaf>(new PlayerLeftHand()));

	// �E�r
	shared_ptr<INode> rightThigh = make_shared<Node>(new PlayerRightThigh());
	body->Add(move(rightThigh));
	shared_ptr<INode> rightCalf = make_shared<Node>(new PlayerRightCalf());
	rightThigh->Add(move(rightCalf));
	rightCalf->Add(make_shared<Leaf>(new PlayerRightFoot()));

	// ���r
	shared_ptr<INode> leftThigh = make_shared<Node>(new PlayerLeftThigh());
	body->Add(move(leftThigh));
	shared_ptr<INode> leftCalf = make_shared<Node>(new PlayerLeftCalf());
	leftThigh->Add(move(leftCalf));
	leftCalf->Add(make_shared<Leaf>(new PlayerLeftFoot()));
}
