#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
}

void Player::Update()
{
	//移動関連
	Move();
	Roll();
	
	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet)
		{return bullet->IsDead(); }
	);
	//攻撃
	Attack();
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	worldTransformUpdate(&worldTransform_);
}

void Player::Move()
{
	//arowキーで移動
	if (input_->PushKey(DIK_LEFT))
	{
		move.x -= moveSpeed;
	}
	if (input_->PushKey(DIK_RIGHT))
	{
		move.x += moveSpeed;
	}
	if (input_->PushKey(DIK_DOWN))
	{
		move.y -= moveSpeed;
	}
	if (input_->PushKey(DIK_UP))
	{
		move.y += moveSpeed;
	}
	//画面外に出ないように設定
	move.x = min(move.x, 36);
	move.x = max(move.x, -36);
	move.y = min(move.y, 20);
	move.y = max(move.y, -20);

	worldTransform_.translation_ = move;
}

void Player::Roll()
{
	//ADキーで回転
	if (input_->PushKey(DIK_A))
	{
		roll.y -= rollSpeed;
	}
	if (input_->PushKey(DIK_D))
	{
		roll.y += rollSpeed;
	}

	//キーを離したときに元の角度に
	if (input_->PushKey(DIK_A) != true && input_->PushKey(DIK_D) != true && roll.y >= 0)
	{
		roll.y -= rollSpeed;
	}
	if (input_->PushKey(DIK_A) != true && input_->PushKey(DIK_D) != true && roll.y <= 0)
	{
		roll.y += rollSpeed;
	}

	//画面外に出ないように設定
	roll.y = min(roll.y, PI/2);
	roll.y = max(roll.y, -PI/2);

	worldTransform_.rotation_ = roll;
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection);
	}
}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE))
	{
		Vector3 velocity(0, 0, bulletSpeed);
		//速度ベクトルを時期の向きに合わせて回転する
		worldTransformRoll(&velocity, &worldTransform_);

		//弾を生成し初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_,velocity);

		//弾を登録する
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::OnCollision()
{
}


