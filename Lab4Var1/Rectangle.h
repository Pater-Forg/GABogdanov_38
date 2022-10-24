#pragma once

#include "Point.h"
#include <cmath>

namespace Fig {
	/*
	 * Class to store information about rectangle and to manipulate it's parameters
	 */
	class Rectangle
	{
	private:
		Point _ps[4];
		float _rad = 0;
		Point _pos;
		float _ar = 0;
	public:
		/*
		 * Hexagon class constructor
		 *
		 * @param cen - object of class Point that keeps central position
		 * @param a - side of the hexagon
		 * @param b - side of the hexagon
		 */
		Rectangle(const Point& cen, float a, float b);

		/*
		 * Position getter
		 *
		 * @return object of class Point that keeps central position
		 */
		Point getPos() { return _pos; }

		/*
		 * Radius getter
		 *
		 * @return radius of a circle inscribed around a rectangle
		 */
		float getRadius() { return _rad; }

		/*
		 * Moves all points of rectangle
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
		 * @return area of rectangle
		 */
		float getArea() { return _ar; }
	};

}