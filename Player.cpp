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
	Move();
	Rotate();
	Attack();

	if (bullets_)
	{
		bullets_->Update();
	}
	worldTransformUpdate(&worldTransform_);
}

void Player::Move()
{
	//arowキーかADSWで移動
	if (input_->PushKey(DIK_LEFT) )
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

void Player::Rotate()
{
	//ASDWキーで回転
	if (input_->PushKey(DIK_A))
	{
		roll.y -= rollSpeed;
	}
	if (input_->PushKey(DIK_D))
	{
		roll.y += rollSpeed;
	}
	if (input_->PushKey(DIK_W))
	{
		roll.x -= rollSpeed;
	}
	if (input_->PushKey(DIK_S))
	{
		roll.x += rollSpeed;
	}

	worldTransform_.rotation_ = roll;
}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE))
	{
		//弾を生成し初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		//弾を登録する
		bullets_ = newBullet;
	}
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	if (bullets_)
	{
		bullets_->Draw(viewProjection);
	}
}


