#pragma once

#include <cmath>

/*
 * Structure to store info about point (x, y)
 */
struct Point
{
private:
	float _x = 0;
	float _y = 0;
public:
	/*
	 * Default constructor
	 */
	Point() {}

	/*
	 * Point structure constructor
	 * 
	 * @param x - position by x
	 * @param y - position by y
	 */
	Point(float x, float y) :
		_x(x), _y(y) {}

	/*
	 * X position getter
	 * 
	 * @return x position
	 */
	float getX() const { return _x; }

	/*
	 * X position setter
	 *
	 * @param x position
	 */
	void setX(float x) {
		_x = x;
	}

	/*
	 * Y position getter
	 *
	 * @return y position
	 */
	float getY() const { return _y; }

	/*
	 * Y position setter
	 *
	 * @param y position
	 */
	void setY(float y) {
		_y = y;
	}

	/*
	 * Move point by x and by y
	 * 
	 * @param dx - change by x
	 * @param dy - change by y
	 */
	void move(float dx, float dy) {
		_x += dx;
		_y += dy;
	}

	/*
	 * Calculate distance between two points
	 * 
	 * @param p1 - const reference to first point
	 * @param p2 - const reference to second point
	 * @return distance between points
	 */
	static float distBetweenPoints(const Point& p1, const Point& p2) {
		return sqrtf(powf(p2.getX() - p1.getX(), 2) + powf(p2.getY() - p1.getY(), 2));
	}
};

