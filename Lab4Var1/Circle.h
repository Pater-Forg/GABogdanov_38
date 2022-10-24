#pragma once
#include <stdexcept>
#include <cmath>
#include "SceneData.h"
#include "Point.h"

namespace Fig {
	/*
	 * Class to store information about circle and to manipulate it's parameters
	 */
	class Circle
	{
	private:
		Point _pos;
		float _rad = 1;
	public:
		/*
		 * Circle class constructor
		 * 
		 * @param center - object of class Point that keeps central position
		 * @param radius - radius of circle
		 */
		Circle(Point center, float radius) {
			setPos(center);
			setRadius(radius);
		}

		/*
		 * Position getter
		 * 
		 * @return object of class Point that keeps central position
		 */
		Point getPos() { return _pos; }

		/*
		 * Position setter
		 * 
		 * @param object of class Point that keeps central position
		 */
		void setPos(Point center) {
			_pos = center;
		}

		/*
		 * Radius getter
		 *
		 * @return radius of circle
		 */
		float getRadius() { return _rad + 0.2; }

		/*
		 * Radius setter
		 *
		 * @param radius of circle (from 0 to 1)
		 */
		float setRadius(float radius) {
			if (radius <= 0 || radius > 1)
				throw std::invalid_argument("Radius must be >0 and <=1");
			else _rad = radius;
		}

		/*
		 * Moves center of circle
		 * 
		 * @param dx - shift by x
		 * @param dy - shift by y
		 */
		void move(float dx, float dy) {
			_pos.move(dx, dy);
		}

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
		 * @return area of circle
		 */
		float getArea() { return 3.14 * _rad * _rad; }
	};

}