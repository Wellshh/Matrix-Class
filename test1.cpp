#include "matrix.cpp"
int main(){
    WellsMatrixLib::Matrix<double> a(5, 5);
    a.fill(5);
    WellsMatrixLib::Matrix<double> b = a;
    WellsMatrixLib::Matrix<double> e(a);
    a.fill(5);
    std::cout << a.getData_count() << std::endl;
    std::cout << a << std::endl;

}