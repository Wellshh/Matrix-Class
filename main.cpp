#include "matrix.cpp"
int main(){
    WellsMatrixLib::Matrix<double> a(5,5);
    WellsMatrixLib::Matrix<double> b(5,5);
    WellsMatrixLib::Matrix<double> c(5,5);
    a.fill(5);
    b.fill(6);
    
    std::cout << a(1,1) << std::endl;
    WellsMatrixLib::Matrix<double> c = a + b;
    WellsMatrixLib::Matrix<double> d = a + 5;
    std::cout<< a.get_row() << std::endl;
    std::cout << a.get_col() << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
}
