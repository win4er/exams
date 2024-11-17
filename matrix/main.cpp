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

	int n4 = 4;
	int temp = 16;
	double array[n4][n4] = {{0}};
	for (int row=0; row < n4; ++row) {
		for (int column = 0; column < n4; ++column) {
			array[row][column] = temp--;
		}
	}
	double (*ptr3)[] = array;
	Matrix M(ptr3, 4, 4);
	M.print();
	printf("Det M: %f\n", M.RDet());
	M.T();
	M.print();
	printf("Det M: %f\n", M.RDet());


	return 0; 
}
