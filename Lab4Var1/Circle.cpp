#include "Circle.h"

bool Fig::Circle::isThere(float x, float y)
{
	//x *= SceneData::aspect * SceneData::px_aspect;
	return powf((x - _pos.getX()), 2) + powf((y - _pos.getY()), 2) <= _rad;
}
