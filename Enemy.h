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
#include "EnemyBullet.h"
#define PI 3.141592653589

class Player;

class Enemy
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection viewProjection);
	void Move();
	void Rotate();
	//フェーズ
	void Approach();
	void ApproachInitialize();
	void Leave();
	void LeaveInitialize();
	//攻撃
	void Fire();
	//セッター
	void SetPlayer(Player*player) { player_=player; }
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	//行動フェーズ
	enum class Phase
	{
		Approach,
		Leave,
	};
	size_t phase_ = static_cast<size_t>(Phase::Approach);
	//メンバ関数のポインタテーブル
	static void (Enemy::*Phase_[])();
	//弾
	std::list<std::unique_ptr<EnemyBullet>>bullets_;
	const float kBulletSpead = 1.0f;	//弾の速度

	//発射間隔
	static const int kFireInterval = 60.0f;
	int32_t bulletTimer = 0;

	//自キャラ
	Player * player_;
};

