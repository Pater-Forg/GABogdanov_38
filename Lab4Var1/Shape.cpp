#include "Shape.h"
#include <tuple>

void Fig::Shape::move()
{
	switch (_type)
	{
	case Fig::Circle_t:
		((Circle*)(_p_shape))->move(_xspeed, _yspeed);
		break;
	case Fig::Rectangle_t:
		((Rectangle*)(_p_shape))->move(_xspeed, _yspeed);
		break;
	case Fig::Hexagon_t:
		((Hexagon*)(_p_shape))->move(_xspeed, _yspeed);
	}
}

void Fig::Shape::move(float dx, float dy)
{
	switch (_type)
	{
	case Fig::Circle_t:
		((Circle*)(_p_shape))->move(dx, dy);
		break;
	case Fig::Rectangle_t:
		((Rectangle*)(_p_shape))->move(dx, dy);
		break;
	case Fig::Hexagon_t:
		((Hexagon*)(_p_shape))->move(dx, dy);
	}
}

bool Fig::Shape::isThere(float x, float y)
{
	switch (_type)
	{
	case Fig::Circle_t:
		return ((Circle*)(_p_shape))->isThere(x, y);
	case Fig::Rectangle_t:
		return ((Rectangle*)(_p_shape))->isThere(x, y);
	case Fig::Hexagon_t:
		return ((Hexagon*)(_p_shape))->isThere(x, y);
	}
}

float Fig::Shape::getArea()
{
	switch(_type)
	{
	case Fig::Circle_t:
		return ((Circle*)(_p_shape))->getArea();
	case Fig::Rectangle_t:
		return ((Rectangle*)(_p_shape))->getArea();
	case Fig::Hexagon_t:
		return ((Hexagon*)(_p_shape))->getArea();
	}
}

std::tuple<Point, float> Fig::Shape::getCircumCircle() const
{
	switch (_type)
	{
	case Fig::Circle_t:
		return std::make_tuple(
			Point(
				((Circle*)(_p_shape))->getPos().getX(),
				((Circle*)(_p_shape))->getPos().getY()
			),
			((Circle*)(_p_shape))->getRadius()
		);
	case Fig::Rectangle_t:
		return std::make_tuple(
			Point(
				((Rectangle*)(_p_shape))->getPos().getX(),
				((Rectangle*)(_p_shape))->getPos().getY()
			),
			((Rectangle*)(_p_shape))->getRadius()
		);
	case Fig::Hexagon_t:
		return std::make_tuple(
			Point(
				((Hexagon*)(_p_shape))->getPos().getX(),
				((Hexagon*)(_p_shape))->getPos().getY()
			),
			((Hexagon*)(_p_shape))->getRadius()
		);
	}
}
