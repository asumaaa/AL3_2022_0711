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
	void Attack();	//�U��
	void PhaseManager();	//�t�F�[�Y�̑J�ڂ��Ǘ�
	void Approach();	//�ڋ߃t�F�[�Y
	void ApproachInitialize();
	void Leave();		//���E�t�F�[�Y
	void LeaveInitialize();
	void OnCollision();
	//�Z�b�^�[
	void SetPlayer(Player* player) { player_ = player; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	//�Q�b�^�[
	Vector3 GetTransration() { return worldTransform_.translation_; }
	Vector3 GetRotation() { return worldTransform_.rotation_; }
	Vector3 GetScale() { return worldTransform_.scale_; }
	//const std::list<std::unique_ptr<EnemyBullet>>& GetBullet() { return bullets_; }//�e���X�g���擾
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
	//�s���t�F�[�Y
	enum class Phase
	{
		Approach,	//�ڋ�
		Leave,		//���E
	};
	//�t�F�[�Y
	Phase phase_ = Phase::Approach;	//�����t�F�[�Y

	//�e
	//std::list<std::unique_ptr<EnemyBullet>> bullets_;
	/*float bulletSpeed = 1.0;
	static const int bulletInterval = 60;
	int bulletTimer = bulletInterval;*/

	//���L����
	Player* player_ = nullptr;
	//�Q�[���V�[��
	GameScene* gameScene_ = nullptr;
};


