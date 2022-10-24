#pragma once

#include <string>
#include "Circle.h"
#include "Rectangle.h"
#include "Hexagon.h"

namespace Fig {
	enum Type
	{
		Circle_t, Rectangle_t, Hexagon_t
	};
	/*
	 * Class to store pointer to exact and manipulate figure's movement 
	 */
	class Shape
	{
	public:
		/*
		 * Default constructor
		 */
		Shape() : _p_shape(nullptr) {}

		/*
		 * Shape object constructor
		 * 
		 * @param shape - pointer to exact shape
		 * @param type - type of shape
		 */
		Shape(void* shape, Fig::Type type) :
			_p_shape(shape), _type(type) {}

		/*
		 * Shape getter
		 * 
		 * @return pointer to shape
		 */
		void* getShape() const {
			return _p_shape;
		}
		
		/*
		 * Speed getter
		 *
		 * @return speed by x
		 */
		float getXSpeed() const { return _xspeed; }

		/*
		 * Speed setter
		 * 
		 * @param s - speed by x
		 */
		void setXSpeed(float s) {
			_xspeed = s;
		}

		/*
		 * Speed getter
		 *
		 * @return speed by y
		 */
		float getYSpeed() const { return _yspeed; }

		/*
		 * Speed setter
		 *
		 * @param s - speed by y
		 */
		void setYSpeed(float s) {
			_yspeed = s;
		}

		/*
		 * Speed setter
		 *
		 * @param sx - speed by x
		 * @param sy - speed by y
		 */
		void setSpeed(float sx, float sy) {
			_xspeed = sx;
			_yspeed = sy;
		}

		/*
		 * Inverts speed by x
		 */
		void invertXSpeed() {
			_xspeed *= -1;
		}

		/*
		 * Inverts speed by y
		 */
		void invertYSpeed() {
			_yspeed *= -1;
		}

		/*
		 * Moves shape to given direction
		 */
		void move();

		/*
		 * Moves shape to given direction
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
		 * @return area of shape
		 */
		float getArea();

		/*
		 * Calculate parameters of circumtified circle
		 * 
		 * @return tuple with central point and radius
		 */
		std::tuple<Point, float> getCircumCircle() const;
	private:
		void* _p_shape;
		Type _type;
		float _xspeed = 0;
		float _yspeed = 0;
		float _rad = 0;
	};

}