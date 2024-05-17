#include "matrix.cpp"
int main()
{
    WellsMatrixLib::Matrix<double> a(5, 5);
    WellsMatrixLib::Matrix<double> b(5, 5);
    WellsMatrixLib::Matrix<double> e(a);
    a.fill(5);
    b.fill(6);
    std::cout << a(1, 1) << std::endl;
    WellsMatrixLib::Matrix<double> c = 5.0 + a;
    std::cout << c << std::endl;
    c += a;
    WellsMatrixLib::ROI<double> f = e.roi(2, 3, 2, 3);
    f(1, 1) = 111;
    WellsMatrixLib::Matrix<double> h(2, 2);
    h.fill(0, 1, 0, 1, 6);
    WellsMatrixLib::Matrix<double> s = f * h;
    std::cout << a.get_row() << std::endl;
    std::cout << a.get_col() << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << e << std::endl;
    std::cout << (c == a) << std::endl;
    // std::cout << d << std::endl;
    std::cout << e.getData_count() << std::endl;
    std::cout << f(1, 1) << std::endl
              << std::endl;
    std::cout << f.get_row() << std::endl;
    std::cout << f.getData_count() << std::endl;
    std::cout << h << std::endl;
    std::cout << s << std::endl;
}
