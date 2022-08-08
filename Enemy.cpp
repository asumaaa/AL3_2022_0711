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
}

void Enemy::Update()
{
	//移動
	Move();
	Roll();

	//フェーズ遷移
	PhaseManager();

	//フェーズによって行動を変更
	switch (phase_)
	{
	case Phase::Approach:
		Approach();
		break;
	case Phase::Leave:
		Leave();
	}

	//行列更新
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
}

void Enemy::Attack()
{
}

void Enemy::PhaseManager()
{
	//フェーズの変更
	switch (phase_)
	{
		//接近フェーズ
	case Phase::Approach:
		if (worldTransform_.translation_.z < 0.0f)
		{
			phase_ = Phase::Leave;
		}
		break;
		//離脱フェーズ
	case Phase::Leave:
		if (worldTransform_.translation_.z > 20.0f)
		{
			phase_ = Phase::Approach;
		}
		break;
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
