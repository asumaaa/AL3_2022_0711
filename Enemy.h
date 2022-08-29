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
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection viewProjection);
	void Move();
	void Rotate();
	void Approach();
	void Leave();
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	//�s���t�F�[�Y
	enum class Phase
	{
		Approach,
		Leave,
	};
	size_t phase_ = static_cast<size_t>(Phase::Approach);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (Enemy::*Phase_[])();
};

