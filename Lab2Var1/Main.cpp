#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MatrixOperations.h"

/*
 * Allocate memory for matrix NxN
 * 
 * @param n size of matrix
 * @return pointer to pointer of matrix
 */
int** alloc_mem(int n);
/*
 * Fill matrix with random numbers in range from 0 to 10
 * 
 * @param mat pointer to pointer of matrix
 * @param n size of matrix
 */
void fill_matrix(int** mat, int n);
/*
 * Print matrix to stdout
 *
 * @param mat pointer to pointer of matrix
 * @param n size of matrix
 */
void print_matrix(int** mat, int n);
/*
 * Print message, clear stdin and ignore INT_MAX characters or till new line
 * 
 * @param msg message to print
 */
void fix_input_error(const char* msg);

int main() {
	std::srand(time(nullptr));
	int n = 0;
	std::cout << "Enter size of matrix (from 1 to 10)\n> ";
	std::cin >> n;
	if (std::cin.fail() || n <= 0 || n > 10) {
		fix_input_error("Invalid size! Press <Enter> to quit");
		return 0;
	}
	std::cout << "Allocating memory..." << std::endl;
	int** a = alloc_mem(n);
	int** b = alloc_mem(n);
	int** c = alloc_mem(n);
	std::cout << "Filling arrays..." << std::endl;
	fill_matrix(a, n);
	fill_matrix(b, n);
	fill_matrix(c, n);
	std::cout << "Generated 3 arrays of size " << n << "x" << n << std::endl;
	std::cout << "A = ";
	print_matrix(a, n);
	std::cout << "B = ";
	print_matrix(b, n);
	std::cout << "C = ";
	print_matrix(c, n);

	const char* msg = "Select operation:\n"
		"[1] C = A + B\n"
		"[2] C = A * B\n"
		"[3] Transpose and write to C...\n"
		"[4] Determinant...\n"
		"[0] Exit";
	std::cout << msg << std::endl;
	int command = 0;
	char mat = '*';
	int res = 0;
	do
	{
		std::cout << "> ";
		std::cin >> command;
		if (std::cin.fail()) {
			fix_input_error("number expected");
			continue;
		}
		switch (command)
		{
		case 1:
			matOp::sum(a, b, c, n);
			std::cout << "A + B = ";
			print_matrix(c, n);
			break;
		case 2:
			matOp::mult(a, b, c, n);
			std::cout << "A * B = ";
			print_matrix(c, n);
			break;
		case 3:
			std::cout << "Which one? [A/B]" << std::endl;
			std::cin >> mat;
			if (mat == 'A')	matOp::transpose(a, c, n);
			else if (mat == 'B') matOp::transpose(b, c, n);
			else {
				fix_input_error("no such matrix");
				continue;
			}
			std::cout << "Transposed " << mat << " = ";
			print_matrix(c, n);
			break;
		case 4:
			std::cout << "Which one? [A/B/C]" << std::endl;
			std::cin >> mat;
			if (mat == 'A')	res = matOp::det(a, n);
			else if (mat == 'B') res = matOp::det(b, n);
			else if (mat == 'C') res = matOp::det(c, n);
			else {
				fix_input_error("no such matrix");
				continue;
			}
			std::cout << "Determinant of " << mat << " = " << res << std::endl;
			break;
		case 0:
			return 0;
		default:
			fix_input_error("unknown command");
			break;
		}
	} while (true);

	return 0;
}

int** alloc_mem(int n) {
	int** m = new int* [n];
	for (int i = 0; i < n; i++) {
		m[i] = new int[n];
	}
	return m;
}

void fill_matrix(int** mat, int n) {
	const int MIN = 0;
	const int MAX = 10;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mat[i][j] = MIN + (std::rand() % (MAX - MIN + 1));;
		}
	}
}

void print_matrix(int** mat, int n) {
	std::cout << "[" << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << ' ';
		for (int j = 0; j < n; j++) {
			std::cout << mat[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << "]" << std::endl;
}

void fix_input_error(const char* msg) {
	std::cout << "[Error] " << msg << std::endl;
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
}