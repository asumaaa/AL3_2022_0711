#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"

class Skydome
{
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection viewProjection);
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
};

