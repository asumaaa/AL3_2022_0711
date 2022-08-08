#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Matrix.h"
#include "PlayerBullet.h"
#include "memory"
#include "list"
#define PI 3.141592653589

class Player
{
public:
	void Initialize(Model* model,uint32_t textureHandle);
	void Update();
	void Move();
	void Roll();
	void Draw(ViewProjection viewProjection);
	void Attack();
	//�Q�b�^�[
	Vector3 GetTransration() { return worldTransform_.translation_; }
	Vector3 GetRotation() { return worldTransform_.rotation_; }
	Vector3 GetScale() { return worldTransform_.scale_; }
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	//�ړ��p�x�N�g��
	Vector3 move = { 0,0,0 };
	Vector3 roll = { 0,0,0 };
	Vector3 scale = { 0,0,0 };
	//���x
	float moveSpeed = 0.5;
	float rollSpeed = 0.02 * PI;
	float scaleSpeed = 0.1;

	//�e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	float bulletSpeed = 1.0;
};

