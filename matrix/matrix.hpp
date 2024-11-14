#ifndef MATRIX_HPP
#define MATRIX_HPP

#include<stdlib.h>
#include<assert.h>
#include<math.h>

class Matrix {
	private:
		int row_n;
		int col_n;
		double** matrix;
	
	public:
		Matrix();
		Matrix(double (*arr)[], int row_n, int col_n);
		Matrix(const Matrix& M, int wipe_row, int wipe_col);
		Matrix(const Matrix& M);
		~Matrix();
		bool print();
		double Minor(const Matrix& m2);
		double RDet();
		double Det();
		double DetG();
		int getRowIndex();
		Matrix& T();
		Matrix& operator+(const Matrix& m2);
		Matrix& operator-(const Matrix& m2);
		Matrix& operator=(const Matrix& m2);
		Matrix& operator*(const Matrix& m2);
};

#endif
