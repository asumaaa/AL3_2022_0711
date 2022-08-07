#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3 position)
{
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("black.png");

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransformUpdate(&worldTransform_);
}

void PlayerBullet::Update()
{
	worldTransformUpdate(&worldTransform_);
	worldTransform_.TransferMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
