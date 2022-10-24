#pragma once
#include "Point.h"
#include <cmath>

namespace Fig {
	/*
	 * Class to store information about hexagon and to manipulate it's parameters
	 */
	class Hexagon
	{
	private:
		Point _ps[6];
		float _rad = 0;
		Point _pos;
		float _ar = 0;
		float _eq(const Point& p1, const Point& p2, float x);
	public:
		/*
		 * Hexagon class constructor
		 *
		 * @param cen - object of class Point that keeps central position
		 * @param a - side of the hexagon
		 */
		Hexagon(const Point& cen, float a);

		/*
		 * Position getter
		 *
		 * @return object of class Point that keeps central position
		 */
		Point getPos() { return _pos; }

		/*
		 * Radius getter
		 *
		 * @return radius of a circle inscribed around a hexagon
		 */
		float getRadius() { return _rad; }

		/*
		 * Moves all points of hexagon
		 *
		 * @param dx - shift by x
		 * @param dy - shift by y
		 */
		void move(float dx, float dy);

		/*
		 * Checks if a character should be drawn at this location
		 *
		 * @param x - x coordinate
		 * @param y - y coordinate
		 * @return true if a character should be drawn at this location and false otherwise
		 */
		bool isThere(float x, float y);

		/*
		 * Calculate area of figure
		 *
		 * @return area of hexagon
		 */
		float getArea() { return _ar; }
	};
}
