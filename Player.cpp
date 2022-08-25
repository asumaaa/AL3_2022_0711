#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���g���C���X�^���X���擾����
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
	//arow�L�[��ADSW�ňړ�
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
	//��ʊO�ɏo�Ȃ��悤�ɐݒ�
	move.x = min(move.x, 36);
	move.x = max(move.x, -36);
	move.y = min(move.y, 20);
	move.y = max(move.y, -20);

	worldTransform_.translation_ = move;
}

void Player::Rotate()
{
	//ASDW�L�[�ŉ�]
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
		//�e�𐶐���������
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		//�e��o�^����
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


