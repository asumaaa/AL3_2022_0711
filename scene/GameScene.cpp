#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() 
{
	for (int i = 0; i < 36; i++)
	{
		delete model_[i];
	}
	delete scope;
	delete scope2;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();


	worldTransformScope.Initialize();
	worldTransformScope.scale_ = { 1,1,1 };
	worldTransformScope.translation_ = { 0,0,-10 };
	worldTransformUpdate(&worldTransformScope);
	worldTransformScope2.Initialize();
	worldTransformScope2.scale_ = { 5.0f * 1.4f,3.0f * 1.4f,1};
	worldTransformScope2.translation_ = { 0,0,-10};
	worldTransformUpdate(&worldTransformScope2);
		
	scope = Model::Create();
	scope2 = Model::Create();

	//3Dモデルの生成
	for (int i = 0; i < 36; i++)
	{
		model_[i] = Model::Create();
		//ワールドトランスフォームの初期化
		worldTransform_[i].Initialize();

		//座標を変える
		worldTransform_[i].translation_ += Vector3(4 * (i % 6) - 10, 4  * (i / 6) - 10, 0.0f);
		worldTransformUpdate(&worldTransform_[i]);
	}
	//ビュープロジェクションの初期化
	viewProjectionScope.eye = { 0,0,-20 };
	viewProjectionScope.Initialize();
	viewProjection_.eye = { 0,0,50 };
	viewProjection_.Initialize();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("texture.jpg");
	textureHandleScope = TextureManager::Load("reticle.png");
	textureHandleScope2 = TextureManager::Load("scope.png");
}

void GameScene::Update() 
{
	if (input_->PushKey(DIK_UP))
	{
		target.y += 0.1;
	}
	if (input_->PushKey(DIK_DOWN))
	{
		target.y -= 0.1;
	}
	if (input_->PushKey(DIK_RIGHT))
	{
		target.x -= 0.1;
	}
	if (input_->PushKey(DIK_LEFT))
	{
		target.x += 0.1;
	}

	if (input_->TriggerKey(DIK_SPACE) && scopeMode == false)
	{
		viewProjection_.eye = { 0,0,25 };
		scopeMode = true;
	}
	else if(input_->TriggerKey(DIK_SPACE))
	{
		scopeMode = false;
	}

	if (scopeMode == true)
	{

		if (input_->PushKey(DIK_W))
		{
			scopeMode2 = true;
		}
		else if (input_->PushKey(DIK_S))
		{
			scopeMode2 = false;
		}

		if (scopeMode2 == false && viewProjection_.eye.z < 25)
		{
			viewProjection_.eye.z += 0.5f;
		}
		if (scopeMode2 == true && viewProjection_.eye.z > 15)
		{
			viewProjection_.eye.z -= 0.5f;
		}
	}
	if(scopeMode == false)
	{
		viewProjection_.eye = { 0,0,50 };
	}

	viewProjection_.target = target;
	viewProjection_.Initialize();
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
	for (int i = 0; i < 36; i++)
	{
		model_[i]->Draw(worldTransform_[i], viewProjection_, textureHandle_);
	}
	if (scopeMode == true)
	{
		scope->Draw(worldTransformScope, viewProjectionScope, textureHandleScope);
		scope2->Draw(worldTransformScope2, viewProjectionScope, textureHandleScope2);
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
