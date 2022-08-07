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

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//3Dモデル
	Model* model_[13];
	//ワールドトランスフォーム
	WorldTransform worldTransform_[13];
	//ビュープロジェクション
	ViewProjection viewProjection_;

	enum PartId
	{
		kRoot,
		kSpine,
		kChest,
		kHead,
		kArmL,
		kArmL2,
		kArmR,
		kArmR2,
		kHip,
		kLegL,
		kLegL2,
		kLegR,
		kLegR2,
		
		kNumPartId
	};

	float r = 0;
	float r2 = 1;

	//ジャンプ
	bool jumpMode = false;
	float jumpSpead = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
