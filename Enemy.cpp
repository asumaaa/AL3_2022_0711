#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model)
{
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("purple.png");

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();

	//�t�F�[�Y������
	ApproachInitialize();

	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(10, 10, 20);
}

void (Enemy::* Enemy::Phase_[])() =
{
	&Enemy::Approach,
	&Enemy::Leave
};

void Enemy::Update()
{
	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{
			return bullet->IsDead();
		});
	Move();
	Rotate();

	//�ڋ߃t�F�[�Y������
	(this->*Phase_[phase_])();

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	worldTransformUpdate(&worldTransform_);
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Move()
{
}

void Enemy::Rotate()
{
}

void Enemy::Approach()
{
	bulletTimer -= 1.0f;
	if (bulletTimer == 0)
	{
		Fire();
		bulletTimer = kFireInterval;
	}
	worldTransform_.translation_.z -= 0.2f;
	//���̍��W�ŗ��E�t�F�[�Y�ֈڍs
	if (worldTransform_.translation_.z <= -20)
	{
		phase_ = static_cast<size_t>(Phase::Leave);
	}
}

void Enemy::ApproachInitialize()
{
	bulletTimer = kFireInterval;
}

void Enemy::Leave()
{
	worldTransform_.translation_.z += 0.2f;
	//���̍��W�Őڋ߃t�F�[�Y�ֈڍs
	if (worldTransform_.translation_.z >= 20)
	{
		phase_ = static_cast<size_t>(Phase::Approach);
	}
}

void Enemy::Fire()
{
	
	//�G�ƃv���C���[�̍����x�N�g�����擾
	Vector3 velocity;
	velocity.x = player_->GetTransration().x - GetTransration().x;
	velocity.y = player_->GetTransration().y - GetTransration().y;
	velocity.z = player_->GetTransration().z - GetTransration().z;
	//�x�N�g���̒����𑬂��ɍ��킹��
	Vector3 velocity2(vector3Normalize(velocity).x * bulletSpeed, vector3Normalize(velocity).y * bulletSpeed, vector3Normalize(velocity).z * bulletSpeed);

	//�e�𐶐���������
	std::unique_ptr<EnemyBullet>newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//�e��o�^����
	bullets_.push_back(std::move(newBullet));
	
	
}
