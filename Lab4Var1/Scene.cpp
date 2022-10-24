#include "Scene.h"
#include <iostream>
#include <tuple>
#include <cstdlib>
#include <Windows.h>

void Scene::_draw() {
	for (int i = 0; i < SceneData::width; i++) {
		for (int j = 0; j < SceneData::height; j++) {
			char px = ' ';
			for (auto& s : _s) {
				float x = (float)i / SceneData::width * 2.0f - 1.0f;
				float y = (float)j / SceneData::height * 2.0f - 1.0f;
				x *= SceneData::aspect * SceneData::px_aspect;
				if (s.isThere(x, y)) {
					px = '@';
				}
			}
			_p_screen[i + j * SceneData::width] = px;
		}
	}
	std::cout << _p_screen;
}

bool Scene::_checkVerWallCol(const Fig::Shape& s) {
	Point cen;
	float rad;
	std::tie(cen, rad) = s.getCircumCircle();
	return (fabsf(cen.getX()) + rad >= 1.6f);
}

bool Scene::_checkHorWallCol(const Fig::Shape& s) {
	Point cen;
	float rad;
	std::tie(cen, rad) = s.getCircumCircle();
	return (fabsf(cen.getY()) + rad >= 1.0f);
}
bool Scene::_checkFigCol(const Fig::Shape& s1, const Fig::Shape& s2) {
	Point cen1, cen2;
	float r1, r2;
	std::tie(cen1, r1) = s1.getCircumCircle();
	std::tie(cen2, r2) = s2.getCircumCircle();
	return (Point::distBetweenPoints(cen1, cen2) <= r1 + r2);
}

void Scene::_handleCol() {
	for (int i = 0; i < _s.size(); i++) {
		if (_checkVerWallCol(_s.at(i))) _s.at(i).invertXSpeed();
		if (_checkHorWallCol(_s.at(i))) _s.at(i).invertYSpeed();
		for (int j = i + 1; j < _s.size(); j++) {
			if (_checkFigCol(_s.at(i), _s.at(j))) {
				_changeDir(_s.at(i), _s.at(j));
			}
		}
	}
}

void Scene::_changeDir(Fig::Shape& s1, Fig::Shape& s2)
{
	Point cen1, cen2;
	float r1, r2;
	std::tie(cen1, r1) = s1.getCircumCircle();
	std::tie(cen2, r2) = s2.getCircumCircle();

	float dx = cen1.getX() - cen2.getX();
	float dy = cen1.getY() - cen2.getY();
	float d = std::sqrtf(dx * dx + dy * dy);
	if (d == 0) d = 0.01;
	float s = dx / d;
	float e = dy / d;

	float vn1 = s2.getXSpeed() * s + s2.getYSpeed() * e;
	float vn2 = s1.getXSpeed() * s + s1.getYSpeed() * e;
	// prevents shapes from sticking together
	float dt = (r2 + r1 - d) / (vn1 - vn2);
	if (dt > 0.6f) dt = 0.6f;
	if (dt < -0.6f) dt = -0.6f;
	s1.move(-s1.getXSpeed() * dt, -s1.getYSpeed() * dt);
	s2.move(-s2.getXSpeed() * dt, -s2.getYSpeed() * dt);
	dx = cen1.getX() - cen2.getX();
	dy = cen1.getY() - cen2.getY();
	d = std::sqrtf(dx * dx + dy * dy);
	if (d == 0) d = 0.01;
	s = dx / d;
	e = dy / d;

	float vt1 = -s2.getXSpeed() * e + s2.getYSpeed() * s;
	float vt2 = -s1.getXSpeed() * e + s1.getYSpeed() * s;

	std::swap(vn1, vn2);

	s1.setXSpeed(vn2 * s - vt2 * e);
	s1.setYSpeed(vn2 * e + vt2 * s);
	s2.setXSpeed(vn1 * s - vt1 * e);
	s2.setYSpeed(vn1 * e + vt1 * s);
}

float Scene::getSumArea()
{
	float res = 0.0f;
	for (auto& s : _s) {
		res += s.getArea();
	}
	return res;
}

float randFloat(float min, float max) {
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

void Scene::fillWithRandomFig(int n)
{
	int lim = 100;
	int k = 0;
	int i = 0;
	while (i < n && k < lim) {
		void* sh = nullptr;
		Point cen(randFloat(MIN_X, MAX_X), randFloat(MIN_Y, MAX_Y));
		float xs = randFloat(MIN_S, MAX_S);
		float ys = randFloat(MIN_S, MAX_S);
		int t = rand() % 3;
		float r = 0.0f;
		float a = 0.0f;
		float b = 0.0f;
		switch (t)
		{
		case Fig::Circle_t:
			r = randFloat(MIN_R, MAX_R);
			sh = (void*)(new Fig::Circle(cen, r));
			break;
		case Fig::Rectangle_t:
			a = randFloat(MIN_A, MAX_A);
			b = randFloat(MIN_A, MAX_A);
			sh = (void*)(new Fig::Rectangle(cen, a, b));
			break;
		case Fig::Hexagon_t:
			a = randFloat(MIN_A, MAX_A);
			sh = (void*)(new Fig::Hexagon(cen, a));
		}
		Fig::Shape shape(sh, (Fig::Type)t);
		shape.setSpeed(xs, ys);
		bool isCol = _checkVerWallCol(shape) || _checkHorWallCol(shape);
		if (!isCol) {
			for (const auto& s : _s) {
				if (_checkFigCol(s, shape)) {
					isCol = true;
					break;
				}
			}
		}
		if (isCol) {
			k++;
		}
		else {
			k = 0;
			i++;
			_s.push_back(shape);
		}
	}
	if (k >= lim) std::cout << "[Warning] only " << i << " figures were added" << std::endl;
}

void Scene::runAnimation() {
	system("cls");
	for (int t = 0; t < 10000; t++) {
		for (int i = 0; i < _s.size(); i++)
		{
			_s.at(i).move();
		}
		_handleCol();
		_draw();
		Sleep(10);
	}
}
