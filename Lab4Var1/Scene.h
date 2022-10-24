#pragma once
#include <vector>
#include "Shape.h"
#include "SceneData.h"
#include "Circle.h"

const float MIN_X = -0.5f;
const float MAX_X = 0.5f;
const float MIN_Y = -0.5f;
const float MAX_Y = 0.5f;
const float MIN_R = 0.1;
const float MAX_R = 0.15;
const float MIN_A = 0.2;
const float MAX_A = 0.3;
const float MIN_S = -0.05;
const float MAX_S = 0.05;

/*
 * Class to store objects of shapes and manipulating their movements
 */
class Scene
{
private:
	char* _p_screen;
	std::vector<Fig::Shape> _s;
	/*
	 * Check if figure hit the vertical wall
	 * 
	 * @param s - const reference to shape object
	 * @return true if shape crosses vertical wall, false othewise
	 */
	bool _checkVerWallCol(const Fig::Shape& s);

	/*
	 * Check if figure hit the horizontal wall
	 *
	 * @param s - const reference to shape object
	 * @return true if shape crosses horizontal wall, false othewise
	 */
	bool _checkHorWallCol(const Fig::Shape& s);

	/*
	 * Check if figures hit each other
	 *
	 * @param s1 - const reference to first shape object
	 * @param s2 - const reference to second shape object
	 * @return true if shapes crosses each other, false othewise
	 */
	bool _checkFigCol(const Fig::Shape& s1, const Fig::Shape& s2);

	/*
	 * Checks all intersections and call function to change directions
	 */
	void _handleCol();

	/*
	 * Changes direction of movement
	 * 
	 * @param s1 - const reference to first shape object
	 * @param s2 - const reference to second shape object
	 */
	void _changeDir(Fig::Shape& s1, Fig::Shape& s2);

	/*
	 * Draws shapes in loop
	 */
	void _draw();
public:
	/*
	 * Default constructor
	 */
	Scene() {
		_p_screen = new char[SceneData::width * SceneData::height + 1];
		_p_screen[SceneData::width * SceneData::height] = '\0';
	}
	
	/*
	 * Fills scene with random figures. If the given number of figures does not fit,
	   then a warning is displayed
	 * 
	 * @param n - number of figures
	 */
	void fillWithRandomFig(int n);

	/*
	 * Calculates the summary area of all shapes
	 */
	float getSumArea();

	/*
	 * Launchs the animation of movement
	 */
	void runAnimation();
};

