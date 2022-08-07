#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	move = { 10,10,10 };
}

void Enemy::Update()
{
	//移動
	Move();
	Roll();

	//行列更新
	worldTransformUpdate(&worldTransform_);
}

void Enemy::Move()
{
	move.z -= 0.2f;
	worldTransform_.translation_ = move;
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
