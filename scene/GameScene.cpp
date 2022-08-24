#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "math.h"

#define PI 3.141592653589

GameScene::GameScene() {}

GameScene::~GameScene() 
{
	delete model_;
	delete modelSkydome_;
	delete debugCamera_;
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//モデル生成
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("Skydome",true);
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("texture.jpg");
	enemyTexture_ = TextureManager::Load("purple.png");
	
	//ビュープロジェクションの初期化
	viewProjection_.eye = { 0,0,-50 };
	viewProjection_.Initialize();

	//自キャラ
	Player* newPlayer = new Player();
	newPlayer->Initialize(model_,textureHandle_);
	player_.reset(newPlayer);

	//敵
	Enemy *newEnemy = new Enemy();
	newEnemy->Initialize(model_, enemyTexture_);
	enemy_.reset(newEnemy);
	//敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_.get());

	//天球
	Skydome* newSkydome = new Skydome();
	newSkydome->Initialize(modelSkydome_,100);
	skydome_.reset(newSkydome);

	//レールカメラ
	RailCamera* newRailCamera = new RailCamera();
	newRailCamera->Initialize(player_->GetWorldTransform());
	railCamera_.reset(newRailCamera);
}

void GameScene::Update()
{
	player_->Update();
	enemy_->Update();
	skydome_->Update();
	railCamera_->Update(player_->GetWorldTransform());
	debugCamera_->Update();
	CheckAllCollisions();
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
	
	player_->Draw(railCamera_->GetViewProjection());
	enemy_->Draw(railCamera_->GetViewProjection());
	skydome_->Draw(railCamera_->GetViewProjection());

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

void GameScene::CheckAllCollisions()
{
	//判定対象ABの座標と差分の座標
	Vector3 posA, posB,V;
	//座標ABの距離
	float length;
	//弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullet();
	const std::list<std::unique_ptr<EnemyBullet >>& enemyBullets  = enemy_ ->GetBullet();

#pragma region 自キャラと敵弾の当たり判定
	//自キャラの座標
	posA = player_->GetTransration();

	//自キャラと敵弾すべての当たり判定
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets)
	{
		//敵の弾の座標取得
		posB = bullet->GetTransration();
		//AとBの距離を求める
		V = { posA.x - posB.x,posA.y - posB.y, posA.z - posB.z };
		length = vector3Length(V);
		//衝突判定
		if ((V.x * V.x) + (V.y * V.y) + (V.z * V.z) <= playerR + enemyBulletR)
		{
			//自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			//敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	//敵キャラの座標
	posA = enemy_->GetTransration();

	//自弾と敵キャラすべての当たり判定
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		//敵の弾の座標取得
		posB = bullet->GetTransration();
		//AとBの距離を求める
		V = { posA.x - posB.x,posA.y - posB.y, posA.z - posB.z };
		length = vector3Length(V);
		//衝突判定
		if ((V.x * V.x) + (V.y * V.y) + (V.z * V.z) <= playerBulletR + enemyR)
		{
			//敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			//自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定

	//自弾と敵キャラすべての当たり判定
	for (const std::unique_ptr<PlayerBullet>& playerbullet : playerBullets)
	{
		for (const std::unique_ptr<EnemyBullet>& enemybullet : enemyBullets)
		{
			//弾の座標取得
			posA = playerbullet->GetTransration();
			posB = enemybullet ->GetTransration();
			//AとBの距離を求める
			V = { posA.x - posB.x,posA.y - posB.y, posA.z - posB.z };
			length = vector3Length(V);
			//衝突判定
			if ((V.x * V.x) + (V.y * V.y) + (V.z * V.z) <= playerBulletR + enemyR)
			{
				//自弾の衝突時コールバックを呼び出す
				playerbullet->OnCollision();
				//敵弾の衝突時コールバックを呼び出す
				enemybullet->OnCollision();
			}
		}
	}
#pragma endregion
}

void GameScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet)
{
	enemyBullets_.push_back(std::move(enemyBullet));
}

void GameScene::EnemyBulletUpdate()
{
	//デスフラグの立った弾を削除
	enemyBullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{return bullet->IsDead(); }
	);
	//弾更新
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_)
	{
		bullet->Update();
	}
}

void GameScene::EnemyBulletDraw()
{
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_)
	{
		bullet->Draw(viewProjection_);
	}
}
