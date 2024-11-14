#include "matrix.hpp"


Matrix::Matrix() {}
Matrix::Matrix(double (*arr)[], int row_inp, int col_inp) {
	row_n = row_inp;
	col_n = col_inp;;
	matrix = new double*[row_inp];
	int array_iter = -1;
	for (int iter_r = 0; iter_r < row_n; ++iter_r) {
		double* row = new double[col_n];
		for (int iter_c=0; iter_c < col_n; ++iter_c) {
			row[iter_c] = (*arr)[++array_iter];
		}
		matrix[iter_r] = row;
	}
}


Matrix::Matrix(const Matrix& M, int wipe_row, int wipe_col) {
	assert((wipe_row < M.row_n) && (wipe_col < M.col_n));
	row_n = M.row_n-1;
	col_n = M.col_n-1;
	matrix = new double*[row_n];
	bool condition = 0;

	int iter_r = -1;
	for (int M_iter_r=0; M_iter_r < M.row_n; ++M_iter_r) {
		if (M_iter_r == wipe_row) {
			continue;
		}
		iter_r++;
		double* row = new double[col_n];
		int iter_c = -1;
		for (int M_iter_c=0; M_iter_c < M.col_n; ++M_iter_c) {
			if (M_iter_c == wipe_col) {
				continue;
			}
			++iter_c;
			row[iter_c] = M.matrix[M_iter_r][M_iter_c];
		}
		matrix[iter_r] = row;
	}
}


Matrix::Matrix(const Matrix& M) {
	row_n = M.row_n;
	col_n = M.col_n;
	matrix = new double*[row_n];
	for (int iter_r = 0; iter_r < row_n; ++iter_r) {
		double* row = new double[col_n];
		for (int iter_c=0; iter_c < col_n; ++iter_c) {
			row[iter_c] = M.matrix[iter_r][iter_c];
		}
	matrix[iter_r] = row;
	}
}


Matrix::~Matrix() {
	for (int iter = 0; iter < row_n; ++iter) {
		delete [] matrix[iter];
	}
	delete [] matrix;
}


bool Matrix::print() {
	for (int iter_r=0; iter_r < row_n; ++iter_r) {
		printf("[");
		for (int iter_c=0; iter_c < col_n; ++iter_c) {
			printf("%f", matrix[iter_r][iter_c]);
			if (iter_c < col_n-1) {
				printf(", \t");
			}
		}
		printf("]\n");
	}
	return true;
}


double Matrix::RDet() {
	assert(row_n == col_n);
	int n = row_n;
	int wipe_row = getRowIndex();
	double result = 0.0;
	for (int wipe_col = 0; wipe_col < n; ++wipe_col) {
		Matrix smallM(*this, wipe_row, wipe_col);
		result += pow(-1, wipe_row + wipe_col) * matrix[wipe_row][wipe_col] * Minor(smallM);
	}
	return result;
}


double Matrix::Det() {
	assert(row_n == col_n);
	return 0;		
}


double Matrix::DetG() {
	assert(row_n == col_n);
	int n = row_n;
	double result = 0.0;
	double temp = 0.0;
	Matrix M = *this;
	for (int it1 = 0; it1 < n - 1; ++it1) {
		for (int it2 = it1 + 1; it2 < n; ++it2) {
			temp = -M.matrix[it2][it1] / M.matrix[it1][it1];
			for (int it3 = 0; it3 < n; ++it3) {
				M.matrix[it2][it3] += M.matrix[it1][it3] * temp;
			}
		}
	}
	result = 1.0;
	for (int iter = 0; iter < n; ++iter) {
		result *= M.matrix[iter][iter];
	}
	return result;
}


double Matrix::Minor(const Matrix& M) {
	assert(row_n == col_n);
	int n = row_n;
	int N = M.row_n;
	double result = 0.0;
	if (N==1) {
		result = M.matrix[0][0];
		return result;
	}
	if (N==2) {
		result = M.matrix[0][0] * M.matrix[1][1] - M.matrix[1][0] * M.matrix[0][1];
		return result;
	}
	int iter_r = getRowIndex();
	for (int iter_c=0; iter_c<n; ++iter_c) {
		Matrix m(M, iter_r, iter_c);
		result += pow(-1, iter_r + iter_c) * M.matrix[iter_r][iter_c] * Minor(m);
	}
	return result;
}


int Matrix::getRowIndex() {
	return 0;
}


Matrix& Matrix::T() {
	double arr[row_n][col_n] = {{0}};
	for (int row = 0; row < row_n; ++row) {
		for (int col = 0; col < col_n; ++col) {
			arr[row][col] = matrix[col][row];
		}
	}

	for (int row = 0; row < row_n; ++row) {
		for (int col = 0; col < col_n; ++col) {
			matrix[row][col] = arr[row][col];
		}
	}
	return *this;
}


Matrix& Matrix::operator+(const Matrix& m) {
	assert((row_n == m.row_n) && (col_n == m.col_n));
	for (int iter_r=0; iter_r < row_n; ++iter_r) {
		for (int iter_c=0; iter_c < col_n; ++iter_c) {
			matrix[iter_c][iter_r] += m.matrix[iter_c][iter_r];
		}
	}
	return *this;
}


Matrix& Matrix::operator-(const Matrix& m) {
	assert((row_n == m.row_n) && (col_n == m.col_n));
	for (int iter_r=0; iter_r < row_n; ++iter_r) {
		for (int iter_c=0; iter_c < col_n; ++iter_c) {
			matrix[iter_c][iter_r] -= m.matrix[iter_c][iter_r];
		}
	}
	return *this;
}


Matrix& Matrix::operator=(const Matrix& m) {
	//Guard self assignment
	if (this != &m) {
		return *this;
	}

	for (int iter_r=0; iter_r < row_n; ++iter_r) {
		delete [] matrix[iter_r];
	}
	delete []  matrix;

	row_n = m.row_n;
	col_n = m.col_n;
	matrix = new double*[row_n];
	for (int iter_r=0; iter_r < row_n; ++iter_r) {
		matrix[iter_r] = new double[col_n];
		for (int iter_c=0; iter_c < col_n; ++iter_c) {
			matrix[iter_r][iter_c] = m.matrix[iter_r][iter_c];
		}
	}
	return *this;
}


Matrix& Matrix::operator*(const Matrix& m) {
	assert(col_n == m.row_n);
	double cur_res_element = 0.0;
	int cur_row = -1;
	for (int column = 0; column < col_n; ++column) {
		cur_res_element = 0.0;
		for (int row = 0; row < row_n; ++row) {
			cur_res_element += matrix[row][column] * m.matrix[column][row];
		}
	}
	return *this;
}
