#include "Hexagon.h"

float Fig::Hexagon::_eq(const Point& p1, const Point& p2, float x)
{
	return ((x - p2.getX()) * (p2.getY() - p1.getY()) / (p2.getX() - p1.getX()) + p2.getY());
}

Fig::Hexagon::Hexagon(const Point& cen, float a)
{
	_ps[0] = Point(cen.getX(), cen.getY() + a);
	_ps[1] = Point(cen.getX() + a * 0.5 * std::sqrtf(3), cen.getY() + a * 0.5);
	_ps[2] = Point(cen.getX() + a * 0.5 * std::sqrtf(3), cen.getY() - a * 0.5);
	_ps[3] = Point(cen.getX(), cen.getY() - a);
	_ps[4] = Point(cen.getX() - a * 0.5 * std::sqrtf(3), cen.getY() - a * 0.5);
	_ps[5] = Point(cen.getX() - a * 0.5 * std::sqrtf(3), cen.getY() + a * 0.5);
	_pos = cen;
	_rad = a;
	_ar = 1.5f * sqrtf(3.0f) * a * a;
}

void Fig::Hexagon::move(float dx, float dy)
{
	for (int i = 0; i < 6; i++) {
		_ps[i].move(dx, dy);
	}
	_pos.move(dx, dy);
}

bool Fig::Hexagon::isThere(float x, float y)
{
	return (
		y <= _eq(_ps[0], _ps[1], x) &&
		y >= _eq(_ps[2], _ps[3], x) &&
		y <= _eq(_ps[0], _ps[5], x) &&
		y >= _eq(_ps[3], _ps[4], x) &&
		x >= _ps[5].getX() &&
		x <= _ps[1].getX()
		);
}
