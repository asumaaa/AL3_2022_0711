#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Matrix.h"
#include "memory"
#include "list"
#include "EnemyBullet.h"
#define PI 3.141592653589

class Player;

class Enemy
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection viewProjection);
	void Move();
	void Rotate();
	//�t�F�[�Y
	void Approach();
	void ApproachInitialize();
	void Leave();
	void LeaveInitialize();
	//�U��
	void Fire();
	//�Z�b�^�[
	void SetPlayer(Player*player) { player_=player; }
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	//�s���t�F�[�Y
	enum class Phase
	{
		Approach,
		Leave,
	};
	size_t phase_ = static_cast<size_t>(Phase::Approach);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (Enemy::*Phase_[])();
	//�e
	std::list<std::unique_ptr<EnemyBullet>>bullets_;
	const float kBulletSpead = 1.0f;	//�e�̑��x

	//���ˊԊu
	static const int kFireInterval = 60.0f;
	int32_t bulletTimer = 0;

	//���L����
	Player * player_;
};

