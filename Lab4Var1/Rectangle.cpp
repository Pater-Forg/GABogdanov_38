#include "Rectangle.h"

Fig::Rectangle::Rectangle(const Point& cen, float a, float b)
{
	_ps[0] = Point(cen.getX() + a / 2, cen.getY() + b / 2);
	_ps[1] = Point(cen.getX() + a / 2, cen.getY() - b / 2);
	_ps[2] = Point(cen.getX() - a / 2, cen.getY() - b / 2);
	_ps[3] = Point(cen.getX() - a / 2, cen.getY() + b / 2);
	_rad = Point::distBetweenPoints(_ps[0], _ps[2]) / 2;
	_pos = cen;
	_ar = a * b;
}

void Fig::Rectangle::move(float dx, float dy)
{
	for (int i = 0; i < 4; i++) {
		_ps[i].move(dx, dy);
	}
	_pos.move(dx, dy);
}

bool Fig::Rectangle::isThere(float x, float y)
{
	return (
		x >= _ps[2].getX() && y >= _ps[2].getY() &&
		x <= _ps[0].getX() && y <= _ps[0].getY()
		);
}
