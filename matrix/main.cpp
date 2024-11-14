#include "matrix.hpp"
#include <iostream>


int main() {
	std::cout << 2 << std::endl;
	int n3 = 3;
	double array1[n3][n3] = {
		{1.0, 2.0, 3.0},
		{4.0, 5.0, 6.0},
		{7.0, 8.0, 9.0},
	};
	
	double array2[3][3] = {
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0},
	};
	double (*ptr1)[] = array1;
	double (*ptr2)[] = array2;

/*	int n4 = 4;
	int temp = 16;
	double array[n4][n4] = {{0}};
	for (int row=0; row < n4; ++row) {
		for (int column = 0; column < n4; ++column) {
			array[row][column] = temp--;
		}
	}
	Matrix M(n4, array);
	M.printM();

//	std::cout << M.RDet() << std::endl;
	std::cout << M.DetG() << std::endl;
*/	
	Matrix M1(ptr1, 3, 3);
	M1.T();
	M1.print();
	std::cout << '\n';
	Matrix M2(ptr2, 3, 3);
	M2.print();
	std::cout << '\n';

	Matrix Multiplicated = M1 * M2;
	Multiplicated.print();
	printf("Determinant:%f\n", Multiplicated.DetG());
	return 0; 
}
