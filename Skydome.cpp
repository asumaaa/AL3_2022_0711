#include "Skydome.h"
#include "Matrix.h"
#include <cassert>

void Skydome::Initialize(Model* model)
{
	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,0,0 };
	worldTransform_.scale_  = { 50,50,50 };
}

void Skydome::Update()
{
	worldTransformUpdate(&worldTransform_);
}

void Skydome::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}