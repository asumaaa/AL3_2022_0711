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
	uint32_t textureHandleScope = 0;
	uint32_t textureHandleScope2 = 0;

	//3Dモデル
	Model* model_[36];
	Model* scope;
	Model* scope2;
	//ワールドトランスフォーム
	WorldTransform worldTransform_[36];
	WorldTransform worldTransformScope;
	WorldTransform worldTransformScope2;
	//ビュープロジェクション
	ViewProjection viewProjectionScope;
	ViewProjection viewProjection_;
	Vector3 target= {0,0,0};

	//スコープモード
	bool scopeMode = false;
	bool scopeMode2 = false;

	const float window_width = 1440;
	const float window_height = 810;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
