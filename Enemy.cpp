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

void Enemy::Update()
{
	Move();
	Rotate();
	PhaseManager();
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

void Enemy::PhaseManager()
{
	switch (phase_)
	{
	case Phase::Approach:
		Approach();
		if (worldTransform_.translation_.z <= -20)
		{
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		Leave();
		if (worldTransform_.translation_.z >= 20)
		{
			phase_ = Phase::Approach;
		}
	}
}

void Enemy::Approach()
{
	worldTransform_.translation_.z -= 0.2f;
}

void Enemy::Leave()
{
	worldTransform_.translation_.z += 0.2f;
}
