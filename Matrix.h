#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include <d3d12.h>
#include "WorldTransform.h"

//WorldTransformの更新
void worldTransformUpdate(WorldTransform* worldTransform_);
//WorldTransformのとベクトルの掛け算
void worldTransformScale(Vector3* vector_, WorldTransform* worldTransform_);
void worldTransformMove(Vector3* vector_, WorldTransform* worldTransform_);
void worldTransformRoll(Vector3* vector_, WorldTransform* worldTransform_);
void vecWorldTransform(Vector3* vector_, WorldTransform* worldTransform_);

