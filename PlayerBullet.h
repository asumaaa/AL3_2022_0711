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
#define PI 3.141592653589

class PlayerBullet
{
public:
	void Initialize(Model* model, const Vector3& position,const Vector3& move);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	void OnCollision();
	bool IsDead()const { return isDead_; }
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	//移動用ベクトル
	Vector3 move_ = { 0,0,0 };
	Vector3 roll_ = { 0,0,0 };
	Vector3 scale_ = { 0,0,0 };
	//速度
	float moveSpeed = 0.5;
	float rollSpeed = 0.02 * PI;
	float scaleSpeed = 0.1;
	//寿命
	static const int32_t lifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = lifeTime;
	//デスフラグ
	bool isDead_ = false;
};

