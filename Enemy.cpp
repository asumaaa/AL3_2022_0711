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
}

void Enemy::Attack()
{
}

void Enemy::PhaseManager()
{
	//�t�F�[�Y�̕ύX
	switch (phase_)
	{
		//�ڋ߃t�F�[�Y
	case Phase::Approach:
		if (worldTransform_.translation_.z < 0.0f)
		{
			phase_ = Phase::Leave;
		}
		break;
		//���E�t�F�[�Y
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
