//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	PlayScene.h
//!
//!	@brief	�v���C�V�[���N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/10/23
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef MASABO_PLAY_SCENE
#define MASABO_PLAY_SCENE

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "BaseScene.h"
#include "..\Camera\FollowCamera.h"
#include "..\Objects\Character\Player\Player.h"
#include "..\Objects\Character\Enemy\Enemy.h"
#include "..\Factory\EnemyFactory.h"
#include "..\LandShape\LandShape.h"
#include <Effects.h>
#include <memory>


namespace MasaboLib
{
	class PlayScene :public BaseScene
	{
	public:
		// �G�̍ő吔
		static const int MAX_ENEMY_NUM;
		// �N���A�ڕW�ƂȂ�|������
		static const int CLEAR_BEAT_NUM;
	private:
		// �J����
		std::unique_ptr<FollowCamera> m_camera;

		// ��
		std::unique_ptr<Obj3D> m_floor;
		// ��
		std::unique_ptr<Obj3D> m_sky;
		// ��
		std::unique_ptr<LandShape> m_wall;

		// �v���C���[
		std::unique_ptr<Player> m_player;
		// �G
		std::vector<std::shared_ptr<Enemy>> m_enemies;
		// �G�����p�̃t�@�N�g���[
		std::unique_ptr<EnemyFactory> m_enemyFactory;

		// HP�o�[

		// �t���[����
		float m_frameCount;
		// ��������
		int m_timeLimit;
		// �G��|������
		int m_numBeat;
	public:
		PlayScene();
		~PlayScene() {}

		void Initialize();
		void Update(const DX::StepTimer& timer);
		void Render(const DX::StepTimer& timer, DirectX::SpriteBatch* batch, DirectX::SpriteFont* font);
		void Finalize();
	private:
		// �v���C���[�ƕǂ̓����蔻��
		void CollisionPlayerAndWall();
		// �v���C���[�̌��ƓG�̓����蔻��
		void CollisionPlayerSwordAndEnemy();
	};
}

#endif // !MASABO_PLAY_SCENE
