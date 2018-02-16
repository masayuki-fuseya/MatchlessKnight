//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayScene.cpp
//!
//!	@brief	�v���C�V�[���N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "PlayScene.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace MasaboLib;
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace DX;

// �ÓI�����o�ϐ��̒�` ====================================================
const int PlayScene::MAX_ENEMY_NUM = 100;
const int PlayScene::CLEAR_BEAT_NUM = 30;


//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
PlayScene::PlayScene()
{
}



//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void PlayScene::Initialize()
{
	// �e�N�X�`����o�^����
	TextureManager::GetInstance()->Initialize(L"Assets\\CSV\\TitleTexture.csv");

	// �J�����𐶐�����
	m_camera = make_unique<FollowCamera>(Graphics::GetInstance()->GetWidth(), Graphics::GetInstance()->GetHeight());

	// �I�u�W�F�N�g�̐ÓI�ϐ�������������
	Obj3D::InitializeStatic(m_camera.get());

	// �n�`������������
	LandShapeCommonDef def;
	def.camera = m_camera.get();
	LandShape::InitializeCommon(def);

	// ���𐶐�����
	m_floor = make_unique<Obj3D>();
	m_floor->LoadModel(L"floor");
	m_floor->DisableLighting();

	// ��𐶐�����
	m_sky = make_unique<Obj3D>();
	m_sky->LoadModel(L"skydome");
	m_sky->DisableLighting();

	// �ǂ𐶐�����
	m_wall = make_unique<LandShape>();
	m_wall->Initialize(L"wall", L"wall");
	m_wall->DisableLighting();

	// �v���C���[�𐶐�����
	m_player = make_unique<Player>();
	m_player->Initialize();

	// �v���C���[���J�����̒Ǐ]�Ώۂɂ���
	m_camera->SetTarget(m_player.get());
	m_camera->Initialize();

	// �G�̐�������ő吔��ݒ肷��
	m_enemies.reserve(MAX_ENEMY_NUM);

	// �G�����p�̃t�@�N�g���[������������
	m_enemyFactory = make_unique<EnemyFactory>();
	m_enemyFactory->Initialize();

	m_frameCount = 0.0f;
	m_timeLimit = 1800;
	m_numBeat = 0;
}



//**********************************************************************
//!	@brief		�X�V����
//!
//!	@param[in]	�^�C�}�[
//!
//!	@return		�Ȃ�
//**********************************************************************
void PlayScene::Update(const StepTimer& timer)
{
	// �J�������X�V����
	m_camera->Update();

	// �����X�V����
	m_floor->Update();
	// ����X�V����
	m_sky->Update();
	// �ǂ��X�V����
	m_wall->Update();

	// �v���C���[���X�V����
	m_player->Update();

	m_frameCount += (float)timer.GetElapsedSeconds();
	if (m_frameCount >= 0.2f)
	{
		// �G���܂������ł���Ȃ琶������
		shared_ptr<Enemy> enemy;
		enemy = m_enemyFactory->Reallocate(Enemy::ID::WEAK);
		if (enemy)
		{
			m_enemies.push_back(enemy);
			// �ǔ��Ώۂ��v���C���[�ɐݒ肷��
			(m_enemies.end() - 1)->get()->SetTarget(m_player.get());
		}

		m_frameCount = 0.0f;
	}

	// �G���X�V����
	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr)
	{
		(*itr)->Update();
	}

	// �����蔻�� ////////////////////////////////////

	// �ǂƎ��@�̓����蔻��
	CollisionPlayerAndWall();

	// �v���C���[�̌��ƓG�̓����蔻��
	CollisionPlayerSwordAndEnemy();

	//////////////////////////////////////////////////

	// �G�������Ă��Ȃ���Ώ���
	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); )
	{
		if (!(*itr)->GetIsAlive())
		{
			itr = m_enemies.erase(itr);
		}
		else
		{
			++itr;
		}
	}

	// 0�b��艺���Ȃ��悤�ɂ���
	m_timeLimit > 0 ? m_timeLimit-- : 0;

	// ���Ԑ؂�ŃN���A�ڕW�ȏゾ������
	if (m_timeLimit == 0 && m_numBeat >= CLEAR_BEAT_NUM)
	{
		//m_isClear = true;
	}
}



//**********************************************************************
//!	@brief		�`�悷��
//!
//!	@param[in]	�^�C�}�[,�@�X�v���C�g�o�b�`,�@�X�v���C�g�t�H���g
//!
//!	@return		�Ȃ�
//**********************************************************************
void PlayScene::Render(const StepTimer& timer, SpriteBatch* batch, SpriteFont* font)
{
	// ���`�悷��
	m_sky->Render();
	// ����`�悷��
	m_floor->Render();
	// �ǂ�`�悷��
	m_wall->Draw();

	// �v���C���[��`�悷��
	m_player->Render();
	// �G��`�悷��
	for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr)
	{
		(*itr)->Render();
	}

	// �������Ԃ�`�悷��

	// �|�����G�̐���`�悷��

	// �e�N�X�`����`�悷��
	//TextureManager::GetInstance()->Render(batch);
}



//**********************************************************************
//!	@brief		�I������������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void PlayScene::Finalize()
{
	m_player->Finalize();
}



//**********************************************************************
//!	@brief		�v���C���[�ƕǂ̓����蔻�������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void PlayScene::CollisionPlayerAndWall()
{
	Sphere sphere = m_player->GetCollisionNodeSphere();
	Vector3 trans = m_player->GetTranslation();
	// �����蔻�苅�̒��S����v���C���[�̑����ւ̃x�N�g��
	Vector3 sphere2player = trans - sphere.m_center;

	// �r�˃x�N�g��
	Vector3 reject;
	// �n�`�Ƌ��̓����蔻��
	if (m_wall->IntersectSphere(sphere, &reject))
	{
		// �߂荞�ݕ������o��
		sphere.m_center += reject;
	}

	// �����o���ꂽ���W��ݒ肷��
	m_player->SetTranslation(sphere.m_center += sphere2player);

	// ���[���h�s�񂾂����炷
	m_player->CalcMatrix();
}



//**********************************************************************
//!	@brief		�v���C���[�̌��ƓG�̓����蔻�������
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
void PlayScene::CollisionPlayerSwordAndEnemy()
{
	// �U������������
	if (m_player->IsAttack())
	{
		Sphere swordSphere = m_player->GetSword()->GetCollisionNode();
		for (auto itr = m_enemies.begin(); itr != m_enemies.end(); ++itr)
		{
			Sphere enemySphere = (*itr)->GetCollisionNodeSphere();

			// �����m�̓����蔻��
			if (CheckSphere2Sphere(swordSphere, enemySphere))
			{
				// �G�̗̑͂����炷
				(*itr)->ReduceLife(10);

				// �G������ł�����
				if (!(*itr)->GetIsAlive())
				{
					// �������ԓ��Ŗ��N���A��������G��|�������𑝂₷
					if (m_timeLimit != 0)
					{
						m_numBeat++;
					}
				}
			}
		}
	}
}
