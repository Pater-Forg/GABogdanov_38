#pragma once

namespace matOp {
	/*
	 * Sum two matrix
	 * 
	 * @param a pointer to pointer on first matrix
	 * @param b pointer to pointer on second matrix
	 * @param res pointer to pointer of matrix with the result
	 * @param n size of matrix
	 */
	void sum(int** a, int** b, int** res, int n);
	/*
	 * Multiply two matrix
	 *
	 * @param a pointer to pointer on first matrix
	 * @param b pointer to pointer on second matrix
	 * @param res pointer to pointer of matrix with the result
	 * @param n size of matrix
	 */
	void mult(int** a, int** b, int** res, int n);
	/*
	 * Transpose matrix
	 *
	 * @param a pointer to pointer of matrix
	 * @param res pointer to pointer of matrix with the result
	 * @param n size of matrix
	 */
	void transpose(int** a, int** res, int n);
	/*
	 * Calculate determinant of matrix
	 *
	 * @param a pointer to pointer of matrix
	 * @param n size of matrix
	 * @return determinant of matrix
	 */
	int det(int** a, int n);
}