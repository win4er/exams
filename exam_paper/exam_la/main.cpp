#include "exam_la.hpp"

int main() {
    double arr[2][2] = {
        {1.0, 2.0},
        {-2.0, 1.0},
    };
    double (*ptr)[] = arr;
    Matrix M(ptr, 2, 2);
    M.print();
    printf("%f", M.RDet());
    return 0;
}