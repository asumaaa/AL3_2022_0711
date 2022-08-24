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
#include "Player.h"
#define PI 3.141592653589

class GameScene;

class Enemy
{
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Move();
	void Roll();
	void Draw(ViewProjection viewProjection);
	void Attack();	//攻撃
	void PhaseManager();	//フェーズの遷移を管理
	void Approach();	//接近フェーズ
	void ApproachInitialize();
	void Leave();		//離脱フェーズ
	void LeaveInitialize();
	void OnCollision();
	//セッター
	void SetPlayer(Player* player) { player_ = player; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	//ゲッター
	Vector3 GetTransration() { return worldTransform_.translation_; }
	Vector3 GetRotation() { return worldTransform_.rotation_; }
	Vector3 GetScale() { return worldTransform_.scale_; }
	//const std::list<std::unique_ptr<EnemyBullet>>& GetBullet() { return bullets_; }//弾リストを取得
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	//移動用ベクトル
	Vector3 move = { 0,0,0 };
	Vector3 roll = { 0,0,0 };
	Vector3 scale = { 0,0,0 };
	//速度
	float moveSpeed = 0.5;
	float rollSpeed = 0.02 * PI;
	float scaleSpeed = 0.1;
	//行動フェーズ
	enum class Phase
	{
		Approach,	//接近
		Leave,		//離脱
	};
	//フェーズ
	Phase phase_ = Phase::Approach;	//初期フェーズ

	//弾
	//std::list<std::unique_ptr<EnemyBullet>> bullets_;
	/*float bulletSpeed = 1.0;
	static const int bulletInterval = 60;
	int bulletTimer = bulletInterval;*/

	//自キャラ
	Player* player_ = nullptr;
	//ゲームシーン
	GameScene* gameScene_ = nullptr;
};


