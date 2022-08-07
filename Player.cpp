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
	worldTransformUpdate(&worldTransform_);
}

void Player::Move()
{
	//arow�L�[��ADSW�ňړ�
	if (input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_A))
	{
		move.x -= moveSpeed;
	}
	if (input_->PushKey(DIK_RIGHT) || input_->PushKey(DIK_D))
	{
		move.x += moveSpeed;
	}
	if (input_->PushKey(DIK_DOWN) || input_->PushKey(DIK_S))
	{
		move.y -= moveSpeed;
	}
	if (input_->PushKey(DIK_UP) || input_->PushKey(DIK_W))
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

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


