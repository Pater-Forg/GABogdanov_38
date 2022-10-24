#include "Scene.h"
#include "Shape.h"
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
	srand(time(0));
	Scene scene;

	int n = 0;
	std::cout << "Enter number of figures\n> ";
	std::cin >> n;
	scene.fillWithRandomFig(n);
	std::cout << "Total area of figures: " << scene.getSumArea() << std::endl;
	std::cout << "Press any key to start animation" << std::endl;
	system("pause");
	std::cout << "Launching animation..." << std::endl;
	Sleep(1000);
	scene.runAnimation();
	

	return 0;
}

