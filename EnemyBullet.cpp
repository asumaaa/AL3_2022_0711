#include "EnemyBullet.h"
#include "cassert"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& move)
{
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("orange.png");

	move_ = move;

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransformUpdate(&worldTransform_);
}

void EnemyBullet::Update()
{
	worldTransform_.translation_ += move_;
	worldTransformUpdate(&worldTransform_);
	worldTransform_.TransferMatrix();

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
