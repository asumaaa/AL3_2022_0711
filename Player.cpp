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
	//�ړ��֘A
	Move();
	Roll();
	//�U��
	Attack();
	if (bullet_)
	{
		bullet_->Update();
	}

	worldTransformUpdate(&worldTransform_);
}

void Player::Move()
{
	//arow�L�[�ňړ�
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
	//��ʊO�ɏo�Ȃ��悤�ɐݒ�
	move.x = min(move.x, 36);
	move.x = max(move.x, -36);
	move.y = min(move.y, 20);
	move.y = max(move.y, -20);

	worldTransform_.translation_ = move;
}

void Player::Roll()
{
	//AD�L�[�ŉ�]
	if (input_->PushKey(DIK_A))
	{
		roll.y += rollSpeed;
	}
	if (input_->PushKey(DIK_D))
	{
		roll.y -= rollSpeed;
	}

	//�L�[�𗣂����Ƃ��Ɍ��̊p�x��
	if (input_->PushKey(DIK_A) != true && input_->PushKey(DIK_D) != true && roll.y >= 0)
	{
		roll.y -= rollSpeed;
	}
	if (input_->PushKey(DIK_A) != true && input_->PushKey(DIK_D) != true && roll.y <= 0)
	{
		roll.y += rollSpeed;
	}

	//��ʊO�ɏo�Ȃ��悤�ɐݒ�
	roll.y = min(roll.y, PI/2);
	roll.y = max(roll.y, -PI/2);

	worldTransform_.rotation_ = roll;
}

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	if (bullet_)
	{
		bullet_->Draw(viewProjection);
	}
}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE))
	{
		//�e�𐶐���������
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		//�e��o�^����
		bullet_ = newBullet;
	}
}


