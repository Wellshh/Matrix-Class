#include "matrix.cpp"
#include <iostream>
#include <string>

void testDoubleMatrix()
{
    using namespace WellsMatrixLib;

    // Create two 3x3 matrices and fill them with some values
    Matrix<double> mat1(3, 3);
    Matrix<double> mat2(3, 3);

    mat1.fill(1.0); // Fill mat1 with 1.0
    mat2.fill(2.0); // Fill mat2 with 2.0

    std::cout << "Double Matrix 1:" << std::endl;
    std::cout << mat1;

    std::cout << "Double Matrix 2:" << std::endl;
    std::cout << mat2;

    // Accessing elements using the operator()
    std::cout << "Element at (0, 0) in mat1: " << mat1(0, 0) << std::endl;
    std::cout << "Element at (1, 1) in mat2: " << mat2(1, 1) << std::endl;

    // Matrix addition
    Matrix<double> mat3 = mat1 + mat2;
    std::cout << "Double Matrix 3 (mat1 + mat2):" << std::endl;
    std::cout << mat3;

    // Matrix subtraction
    Matrix<double> mat4 = mat2 - mat1;
    std::cout << "Double Matrix 4 (mat2 - mat1):" << std::endl;
    std::cout << mat4;

    // Matrix scalar multiplication
    Matrix<double> mat5 = mat1 * 3.0;
    std::cout << "Double Matrix 5 (mat1 * 3.0):" << std::endl;
    std::cout << mat5;

    // Matrix scalar addition
    Matrix<double> mat6 = mat1 + 5.0;
    std::cout << "Double Matrix 6 (mat1 + 5.0):" << std::endl;
    std::cout << mat6;

    // Test the ROI class
    ROI<double> roi = mat1.roi(0, 0, 2, 2);
    std::cout << "Double Matrix 1 after filling ROI (0, 0, 2, 2) with 4.0:" << std::endl;
    std::cout << mat1;
}

void testIntMatrix()
{
    using namespace WellsMatrixLib;

    // Create two 3x3 matrices and fill them with some values
    Matrix<int> mat1(3, 3);
    Matrix<int> mat2(3, 3);

    mat1.fill(1); // Fill mat1 with 1
    mat2.fill(2); // Fill mat2 with 2

    std::cout << "Int Matrix 1:" << std::endl;
    std::cout << mat1;

    std::cout << "Int Matrix 2:" << std::endl;
    std::cout << mat2;

    // Accessing elements using the operator()
    std::cout << "Element at (0, 0) in mat1: " << mat1(0, 0) << std::endl;
    std::cout << "Element at (1, 1) in mat2: " << mat2(1, 1) << std::endl;

    // Matrix addition
    Matrix<int> mat3 = mat1 + mat2;
    std::cout << "Int Matrix 3 (mat1 + mat2):" << std::endl;
    std::cout << mat3;

    // Matrix subtraction
    Matrix<int> mat4 = mat2 - mat1;
    std::cout << "Int Matrix 4 (mat2 - mat1):" << std::endl;
    std::cout << mat4;

    // Matrix scalar multiplication
    Matrix<int> mat5 = mat1 * 3;
    std::cout << "Int Matrix 5 (mat1 * 3):" << std::endl;
    std::cout << mat5;

    // Matrix scalar addition
    Matrix<int> mat6 = mat1 + 5;
    std::cout << "Int Matrix 6 (mat1 + 5):" << std::endl;
    std::cout << mat6;

    // Test the ROI class
    ROI<int> roi = mat1.roi(0, 0, 2, 2);
    std::cout << "Int Matrix 1 after filling ROI (0, 0, 2, 2) with 4:" << std::endl;
    std::cout << mat1;
}

void testStringMatrix()
{
    using namespace WellsMatrixLib;

    // Create a 2x2 matrix and fill it with some values
    Matrix<std::string> mat1(2, 2);
    mat1(0, 0) = "Hello";
    mat1(0, 1) = "World";
    mat1(1, 0) = "Foo";
    mat1(1, 1) = "Bar";

    std::cout << "String Matrix 1:" << std::endl;
    std::cout << mat1;

    // Accessing elements using the operator()
    std::cout << "Element at (0, 0) in mat1: " << mat1(0, 0) << std::endl;
    std::cout << "Element at (1, 1) in mat1: " << mat1(1, 1) << std::endl;

    // Test the ROI class
    ROI<std::string> roi = mat1.roi(0, 0, 1, 1);
    std::cout << "String Matrix 1 after filling ROI (0, 0, 1, 1) with 'NewVal':" << std::endl;
    std::cout << mat1;
}

int main()
{
    testDoubleMatrix();
    std::cout << "-----------------------------" << std::endl;
    testIntMatrix();
    std::cout << "-----------------------------" << std::endl;
    testStringMatrix();
    std::cout << "-----------------------------" << std::endl;

    return 0;
}
