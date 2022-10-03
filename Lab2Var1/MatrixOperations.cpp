#include <cmath>
#include <iostream>
#include "MatrixOperations.h"

void matOp::sum(int** a, int** b, int** res, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
}

void matOp::mult(int** a, int** b, int** res, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = 0;
            for (int k = 0; k < n; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void matOp::transpose(int** a, int** res, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = a[j][i];
        }
    }
}

/*
 * Cross out given line and column, forming minor of matrix
 * 
 * @param m given matrix
 * @param n size of matrix
 * @param line number of line to cross out
 * @param col number of colubn to cross out
 * 
 * @return pointer to new matrix
 */
int** trimLineAndColumn(int** m, int n, int line, int col)
{
    int k = n - 1;  // size of trimmed matrix
    int** newMat = new int* [k];
    for (int i = 0; i < k; i++) {
        newMat[i] = new int[k];
    }

    int di = 0;
    for (int i = 0; i < k; i++) {
        if (di == line) di++;
        int dj = 0;
        for (int j = 0; j < k; j++) {
            if (dj == col) dj++;
            newMat[i][j] = m[di][dj];
            dj++;
        }
        di++;
    }

    return newMat;
}

int matOp::det(int** a, int n)
{
    if (n == 1) return a[0][0];
    if (n == 2) return (a[0][0] * a[1][1]) - (a[0][1] * a[1][0]);

    double res = 0;
    int k = 1;
    for (int i = 0; i < n; i++) {
        int** t = trimLineAndColumn(a, n, 0, i);
        res += k * a[0][i] * det(t, n-1);
        k = -k;
    }

    return res;
}
