#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model)
{
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("purple.png");

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

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
	Move();
	Rotate();
	(this->*Phase_[phase_])();
	worldTransformUpdate(&worldTransform_);
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Move()
{
}

void Enemy::Rotate()
{
}

void Enemy::Approach()
{
	worldTransform_.translation_.z -= 0.2f;
	//一定の座標で離脱フェーズへ移行
	if (worldTransform_.translation_.z <= -20)
	{
		phase_ = static_cast<size_t>(Phase::Leave);
	}
}

void Enemy::Leave()
{
	worldTransform_.translation_.z += 0.2f;
	//一定の座標で接近フェーズへ移行
	if (worldTransform_.translation_.z >= 20)
	{
		phase_ = static_cast<size_t>(Phase::Approach);
	}
}
