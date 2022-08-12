#include "Skydome.h"
#include "Matrix.h"
#include <cassert>

void Skydome::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	worldTransformUpdate(&worldTransform_);
}

void Skydome::Update()
{
}

void Skydome::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}