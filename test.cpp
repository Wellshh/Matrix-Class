#include "matrix.cpp"
#include <iostream>

int main() {
    using namespace WellsMatrixLib;

    // Create two 3x3 matrices and fill them with some values
    Matrix<double> mat1(3, 3);
    Matrix<double> mat2(3, 3);

    mat1.fill(1.0); // Fill mat1 with 1.0
    mat2.fill(2.0); // Fill mat2 with 2.0

    std::cout << "Matrix 1:" << std::endl;
    std::cout << mat1;

    std::cout << "Matrix 2:" << std::endl;
    std::cout << mat2;

    // Accessing elements using the operator()
    std::cout << "Element at (0, 0) in mat1: " << mat1(0, 0) << std::endl;
    std::cout << "Element at (1, 1) in mat2: " << mat2(1, 1) << std::endl;

    // Matrix addition
    Matrix<double> mat3 = mat1 + mat2;
    std::cout << "Matrix 3 (mat1 + mat2):" << std::endl;
    std::cout << mat3;

    // Matrix subtraction
    Matrix<double> mat4 = mat2 - mat1;
    std::cout << "Matrix 4 (mat2 - mat1):" << std::endl;
    std::cout << mat4;

    // Matrix scalar multiplication
    Matrix<double> mat5 = mat1 * 3.0;
    std::cout << "Matrix 5 (mat1 * 3.0):" << std::endl;
    std::cout << mat5;

    // Matrix scalar addition
    Matrix<double> mat6 = mat1 + 5.0;
    std::cout << "Matrix 6 (mat1 + 5.0):" << std::endl;
    std::cout << mat6;

    // Test the ROI class
    ROI<double> roi = mat1.roi(0, 0, 2, 2);
    std::cout << "Matrix 1 after filling ROI (0, 0, 2, 2) with 4.0:" << std::endl;
    std::cout << mat1;

    return 0;
}
