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
#include "DebugCamera.h"
#include "Matrix.h"
#include "Player.h"
#include "Enemy.h"
#include "memory"
#include "list"
#include "Skydome.h"
#include "RailCamera.h"
#include "EnemyBullet.h"
#include "PlayerBullet.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:
	//当たり判定
	void CheckAllCollisions();
	//散弾を追加する
	void AddEnemyBullet(std::unique_ptr<EnemyBullet>enemyBullet);
	//敵の弾の更新
	void EnemyBulletUpdate();
	//敵の弾の描画
	void EnemyBulletDraw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t enemyTexture_ = 0;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	//3Dモデル
	Model* model_;
	Model* modelSkydome_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//プレイヤー
	std::unique_ptr<Player> player_;

	//敵
	std::unique_ptr<Enemy>enemy_;
	//敵の弾
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullet() { return enemyBullets_; }//弾リストを取得
	float bulletSpeed = 1.0;
	static const int bulletInterval = 60;
	int bulletTimer = bulletInterval;

	//天球
	std::unique_ptr<Skydome>skydome_;

	//レールカメラ
	std::unique_ptr<RailCamera>railCamera_;

	//半径
	float playerR = 5;
	float enemyR = 5;
	float playerBulletR = 5;
	float enemyBulletR = 5;

		/// <summary>
		/// ゲームシーン用
		/// </summary>
};
