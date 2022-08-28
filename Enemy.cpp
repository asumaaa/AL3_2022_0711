#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model)
{
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("purple.png");

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.translation_ = Vector3(10, 10, 20);
}

void Enemy::Update()
{
	Move();
	Rotate();
	worldTransformUpdate(&worldTransform_);
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Move()
{
	worldTransform_.translation_.z -= 0.2f;
}

void Enemy::Rotate()
{
}
