#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "math.h"

#define PI 3.141592653589

GameScene::GameScene() {}

GameScene::~GameScene() 
{
	for (int i = 0; i < 13; i++)
	{
		delete model_[i];
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//3Dモデルの生成
	for (int i = 0; i < 13; i++)
	{
		model_[i] = Model::Create();
		//ワールドトランスフォームの初期化
		worldTransform_[i].Initialize();
	}
	worldTransform_[PartId::kSpine].parent_ = &worldTransform_[PartId::kRoot];
	worldTransform_[PartId::kSpine].translation_ = { 0.0f,5.0f,0.0f };

	//上半身
	//胸
	worldTransform_[PartId::kChest].parent_ = &worldTransform_[PartId::kSpine];
	worldTransform_[PartId::kChest].translation_ = { 0.0f,0.0f,0.0f };
	//頭
	worldTransform_[PartId::kHead].parent_ = &worldTransform_[PartId::kChest];
	worldTransform_[PartId::kHead].translation_ = { 0.0f,3.0f,0.0f };
	//左腕
	worldTransform_[PartId::kArmL].parent_ = &worldTransform_[PartId::kChest];
	worldTransform_[PartId::kArmL].translation_ = { 3.0f,0.0f,0.0f };
	//左腕2
	worldTransform_[PartId::kArmL2].parent_ = &worldTransform_[PartId::kArmL];
	worldTransform_[PartId::kArmL2].translation_ = { 0.0f,-2.0f,0.0f };
	//右腕
	worldTransform_[PartId::kArmR].parent_ = &worldTransform_[PartId::kChest];
	worldTransform_[PartId::kArmR].translation_ = {-3.0f,0.0f,0.0f };
	//右腕2
	worldTransform_[PartId::kArmR2].parent_ = &worldTransform_[PartId::kArmR];
	worldTransform_[PartId::kArmR2].translation_ = {  0.0f,-2.0f,0.0f };

	////下半身
	//腰
	worldTransform_[PartId::kHip].parent_ = &worldTransform_[PartId::kSpine];
	worldTransform_[PartId::kHip].translation_ = { 0.0f,-3.0f,0.0f };
	//左足
	worldTransform_[PartId::kLegL].parent_ = &worldTransform_[PartId::kHip];
	worldTransform_[PartId::kLegL].translation_ = { 2.0f, -3.0f,0.0f };
	//左足2
	worldTransform_[PartId::kLegL2].parent_ = &worldTransform_[PartId::kLegL];
	worldTransform_[PartId::kLegL2].translation_ = { 0.0f, -2.0f,0.0f };
	//右足
	worldTransform_[PartId::kLegR].parent_ = &worldTransform_[PartId::kHip];
	worldTransform_[PartId::kLegR].translation_ = {-2.0f,-3.0f,0.0f };
	//右足2
	worldTransform_[PartId::kLegR2].parent_ = &worldTransform_[PartId::kLegR];
	worldTransform_[PartId::kLegR2].translation_ = {  0.0f,-2.0f,0.0f };

	//座標を変える
	for (int i = 0; i < 13; i++)
	{
		worldTransformUpdate(&worldTransform_[i]);
	}

	//ビュープロジェクションの初期化
	viewProjection_.eye = { 0,0,-30 };
	viewProjection_.Initialize();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("texture.jpg");
}

void GameScene::Update()
{
	if (input_->PushKey(DIK_LEFT))
	{
		worldTransform_[PartId::kRoot].translation_.x -= 0.2;
	}
	if (input_->PushKey(DIK_RIGHT))
	{
		worldTransform_[PartId::kRoot].translation_.x += 0.2;
	}
	if (input_->PushKey(DIK_A))
	{
		worldTransform_[PartId::kRoot].rotation_.y += 0.05;
	}
	if (input_->PushKey(DIK_D))
	{
		worldTransform_[PartId::kRoot].rotation_.y -= 0.05;
	}

	//腕足回転
	r += 0.02;
	r2 += 0.02;

	worldTransform_[PartId::kArmL].rotation_.x = sin(r * PI);
	worldTransform_[PartId::kArmR].rotation_.x = sin(r2 * PI);
	worldTransform_[PartId::kLegL].rotation_.x = sin(r2 * PI);
	worldTransform_[PartId::kLegR].rotation_.x = sin(r * PI);

	worldTransformUpdate(&worldTransform_[PartId::kRoot]);
	worldTransform_[PartId::kRoot].TransferMatrix();

	for (int i = 1; i < 13; i++)
	{
		worldTransformUpdate(&worldTransform_[i]);
		worldTransform_[i].matWorld_ *= worldTransform_[i].parent_->matWorld_;
		worldTransform_[i].TransferMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	for (int i = 2; i < 13; i++)
	{
		model_[i]->Draw(worldTransform_[i], viewProjection_, textureHandle_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
