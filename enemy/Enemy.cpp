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

	//接近フェーズ初期化
	ApproachInitialize();
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

	////デスフラグの立った弾を削除
	//bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
	//	{return bullet->IsDead(); }
	//);
	////弾更新
	//for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	//{
	//	bullet->Update();
	//}

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
	/*for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection);
	}*/
}

void Enemy::Attack()
{
	assert(player_);
	
	//敵とプレイヤーの差分ベクトルを取得
	Vector3 velocity;
	velocity.x = player_->GetTransration().x - GetTransration().x;
	velocity.y = player_->GetTransration().y - GetTransration().y;
	velocity.z = player_->GetTransration().z - GetTransration().z;
	//ベクトルの長さを速さに合わせる
	Vector3 velocity2(vector3Normalize(velocity).x * bulletSpeed, vector3Normalize(velocity).y * bulletSpeed, vector3Normalize(velocity).z * bulletSpeed);

	//弾を生成し初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity2);

	////弾を登録する
	//bullets_.push_back(std::move(newBullet));
}

void Enemy::PhaseManager()
{
	//フェーズの変更
	switch (phase_)
	{
		//接近フェーズ
	case Phase::Approach:
		if (worldTransform_.translation_.z < -20.0f)
		{
			phase_ = Phase::Leave;
		}
		break;
		//離脱フェーズ
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
	//一定時間ごとに攻撃
	--bulletTimer;
	if (bulletTimer <= 0)
	{
		Attack();
		//タイマー初期化
		bulletTimer = bulletInterval;
	}
}
void Enemy::ApproachInitialize()
{
	//タイマー初期化
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

