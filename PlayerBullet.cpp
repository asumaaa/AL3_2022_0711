#include "PlayerBullet.h"
#include <cassert>


void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("black.png");

	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransformUpdate(&worldTransform_);
}

void PlayerBullet::Update()
{
	//��莞�Ԍo�߂Œe���폜
	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}

	//���W���ړ�
	worldTransform_.translation_ += velocity_;
	//�s����X�V
	worldTransformUpdate(&worldTransform_);
	worldTransform_.TransferMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
