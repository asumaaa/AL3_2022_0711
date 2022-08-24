#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	move = { 10,10,10 };
	worldTransform_.translation_ = move;

	//�ڋ߃t�F�[�Y������
	ApproachInitialize();
}

void Enemy::Update()
{
	//�ړ�
	Move();
	Roll();

	//�t�F�[�Y�J��
	PhaseManager();

	//�t�F�[�Y�ɂ���čs����ύX
	switch (phase_)
	{
	case Phase::Approach:
		Approach();
		break;
	case Phase::Leave:
		Leave();
	}

	////�f�X�t���O�̗������e���폜
	//bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
	//	{return bullet->IsDead(); }
	//);
	////�e�X�V
	//for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	//{
	//	bullet->Update();
	//}

	//�s��X�V
	worldTransformUpdate(&worldTransform_);
}

void Enemy::Move()
{
}

void Enemy::Roll()
{
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	/*for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection);
	}*/
}

void Enemy::Attack()
{
	assert(player_);
	
	//�G�ƃv���C���[�̍����x�N�g�����擾
	Vector3 velocity;
	velocity.x = player_->GetTransration().x - GetTransration().x;
	velocity.y = player_->GetTransration().y - GetTransration().y;
	velocity.z = player_->GetTransration().z - GetTransration().z;
	//�x�N�g���̒����𑬂��ɍ��킹��
	Vector3 velocity2(vector3Normalize(velocity).x * bulletSpeed, vector3Normalize(velocity).y * bulletSpeed, vector3Normalize(velocity).z * bulletSpeed);

	//�e�𐶐���������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity2);

	////�e��o�^����
	//bullets_.push_back(std::move(newBullet));
}

void Enemy::PhaseManager()
{
	//�t�F�[�Y�̕ύX
	switch (phase_)
	{
		//�ڋ߃t�F�[�Y
	case Phase::Approach:
		if (worldTransform_.translation_.z < -20.0f)
		{
			phase_ = Phase::Leave;
		}
		break;
		//���E�t�F�[�Y
	case Phase::Leave:
		if (worldTransform_.translation_.z > 30.0f)
		{
			phase_ = Phase::Approach;
		}
		break;
	}
}

void Enemy::Approach()
{
	worldTransform_.translation_.z -= 0.2f;
	//��莞�Ԃ��ƂɍU��
	--bulletTimer;
	if (bulletTimer <= 0)
	{
		Attack();
		//�^�C�}�[������
		bulletTimer = bulletInterval;
	}
}
void Enemy::ApproachInitialize()
{
	//�^�C�}�[������
	bulletTimer = bulletInterval;
}

void Enemy::Leave()
{
	worldTransform_.translation_.z += 0.2f;
}
void Enemy::LeaveInitialize()
{
}

void Enemy::OnCollision()
{
}

