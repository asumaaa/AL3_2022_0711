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
#include "memory"
#include "list"
#define PI 3.141592653589

class Enemy
{
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Move();
	void Roll();
	void Draw(ViewProjection viewProjection);
	void Attack();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	//�ړ��p�x�N�g��
	Vector3 move = { 0,0,0 };
	Vector3 roll = { 0,0,0 };
	Vector3 scale = { 0,0,0 };
	//���x
	float moveSpeed = 0.5;
	float rollSpeed = 0.02 * PI;
	float scaleSpeed = 0.1;
};

