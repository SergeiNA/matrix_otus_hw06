#include "matrix.h"

#include <iostream>
#include <iomanip>

template <class T,size_t N>
std::ostream& operator<< (std::ostream& os, const std::array<T,N>& array){
    bool isBegin = true;
    for(const auto& elem: array){
        if(!isBegin){
            os<<',';
        }
        isBegin = false;
        os<<elem;
    }
    return os;
}

template<class matrix_type>
void pretty_print_flat_2D(const matrix_type& matrix, size_t m, size_t n,size_t m_0=0, size_t n_0=0)
{
    assert(matrix.getDimention()==2);
    for (size_t i = m_0; i < m; ++i)
        for (size_t j = n_0; j < n; ++j)
            std::cout << "Element(" << i << "," << j << "): " << matrix(i, j) << std::endl;
}


template<class matrix_type>
void pretty_print_rect_2D(const matrix_type& matrix, size_t m, size_t n,size_t m_0=0, size_t n_0=0)
{
    assert(matrix.getDimention()==2);
    std::cout<<std::endl;
    for (size_t i = m_0; i < m; ++i){
        std::cout<<"[";
        for (size_t j = n_0; j < n; ++j)
            std::cout<<std::setw(4)<< matrix(i, j);
        std::cout<<"]"<<std::endl;
    }
}

int main([[maybe_unused]]int argc, [[maybe_unused]]const char** argv) {
    {
        // 2D
        std::cout<<"Task example for 2D matrix\n";
        Matrix<int, -1> matrix;
        assert(matrix.size() == 0);
        auto a = matrix(0, 0);
        assert(a == -1);
        assert(matrix.size() == 0);
        matrix(100, 100) = 314;
        assert(matrix(100, 100) == 314);
        assert(matrix.size() == 1);
        std::cout<<"OK"<<std::endl;
    }
    {
        // 3D
        std::cout<<"Task example for 3D matrix\n";
        Matrix<int, -1, 3> matrix;
        assert(matrix.size() == 0);
        auto a = matrix(0, 0, 0);
        assert(a == -1);
        assert(matrix.size() == 0);
        matrix(100, 100, 100) = 314;
        assert(matrix(100, 100, 100) == 314);
        assert(matrix.size() == 1);
        std::cout<<"OK"<<std::endl;
    }
    {
        // 4D
        std::cout<<"Task example for 4D matrix\n";
        Matrix<int, -1, 4> matrix;
        assert(matrix.size() == 0);
        auto a = matrix(0, 0, 0, 0);
        assert(a == -1);
        assert(matrix.size() == 0);
        matrix(100, 100, 100, 100) = 314;
        assert(matrix(100, 100, 100, 100) == 314);
        assert(matrix.size() == 1);
        std::cout<<"OK"<<std::endl;
    }
    {
        // test for-loop and range-base loop 2D
        std::cout<<"Example of for-loop and range-base loop for 2D matrix\n";
        const int Defaultnum =3;
        Matrix<int, 3> matrix;
        assert(matrix.size() == 0);
        matrix(0, 0) = -1;
        matrix(1, 1) = -1;
        matrix(2, 2) = -1;
        matrix(3, 3) = Defaultnum;
        assert(matrix.size() == 3);
        pretty_print_flat_2D(matrix, 5, 5);
        pretty_print_rect_2D(matrix, 5, 5);
        for (const auto &i : matrix)
        {
            std::cout << '[' << i.first << ']';
            std::cout << ' ' << i.second << std::endl;
        }
        matrix(2, 5) = 2;
        assert(matrix.size() == 4);
        matrix(0, 0) = Defaultnum;
        assert(matrix.size() == 3);
        std::cout<<"OK"<<std::endl;

    }
    {
        // test range-base loop 4D
        std::cout<<"Example of range-base loop for 4D matrix\n";
        const int Defaultnum =3;
        Matrix<int, 3, 4> matrix;
        assert(matrix.size() == 0);
        matrix(0, 0, 1, 1) = -1;
        matrix(1, 1, 0, 0) = -1;
        matrix(2, 2, 30, 15) = -1;
        matrix(3, 3, 7, 1) = Defaultnum;
        assert(matrix.size() == 3);
        for (const auto &i : matrix)
        {
            std::cout << '[' << i.first << ']';
            std::cout << ' ' << i.second << std::endl;
        }
        matrix(2, 2, 2, 2) = 2;
        assert(matrix.size() == 4);
        matrix(0, 0, 1, 1) = Defaultnum;
        assert(matrix.size() == 3);
        std::cout<<"OK"<<std::endl;
    }
    {
        // diagonal + chess
        std::cout<<"Main task\n";
        Matrix<int, 0> matrix;
        const size_t N = 10;
        for (size_t i = 0; i < N; i++)
        {
            matrix(i, i) = i;
            matrix(N - 1 - i, i) = i;
        }
        std::cout<<"Fill diagonales of matrix\n";
        pretty_print_rect_2D(matrix, N, N);
        std::cout << "size: " << matrix.size() << std::endl;
        size_t n_counter = 0;
        for (size_t i = 0; i < N/2; ++i)
        {
            size_t k = (N/2)%2;
            for (size_t j = 0 + i % 2; j < N; j += 2)
            {
                matrix(i, j) = 0;
                matrix(i + N/2,k*(N-j-1)+(1-k)*j) = 0;
                ++n_counter;
            }
        }
        {
            // ADDED
            size_t N=10;
            Matrix<int, 0> matrix_ts;
            size_t k = (N/2)%2;
            for (size_t i = 0; i < N / 2; ++i)
            {
                for (size_t j = 0 + i % 2; j < N; j += 2)
                {
                    matrix_ts(i, j) = 1;
                    matrix_ts(i + N/2,k*(N-j-1)+(1-k)*j) = 2;
                }
            }
            std::cout<<"Fill matrix chess-like test\n";
            pretty_print_rect_2D(matrix_ts, N, N);
        }
        {
            // ADDED
            size_t N = 8;
            Matrix<int, 0> matrix_ts;
            for (size_t i = 0; i < N; i++){
                //matrix_ts[i][i] = matrix_ts[N - 1 - i][i] = i;
                matrix_ts(i,i) = matrix_ts(N - 1 - i, i) = i;
            }
            std::cout << "Fill matrix diag assign test, use (n,n,...,n)\n";
            pretty_print_rect_2D(matrix_ts, N, N);
            std::cout<<std::endl;
        }
        {
            // ADDED
            size_t N = 8;
            Matrix<int, 0> matrix_ts;
            for (size_t i = 0; i < N; i++){
                matrix_ts[i][i] = matrix_ts[N - 1 - i][i] = i;
            }
            std::cout << "Fill matrix diag assign test, use [][],...,[]\n";
            pretty_print_rect_2D(matrix_ts, N, N);
            std::cout<<std::endl;
        }

        std::cout<<"Fill matrix chess-like\n";
        std::cout<<"Counter: "<<n_counter<<std::endl;
        pretty_print_rect_2D(matrix, N, N);
        std::cout << "size: " << matrix.size() << std::endl;
        // [1,1] [8,8]
        std::cout<<"Fill matrix chess-like [1,1] [8,8]\n";
        pretty_print_rect_2D(matrix, 9, 9,1,1);
        return 0;
        std::cout<<"Unique elements:\n";
        for (const auto &i : matrix)
        {
            std::cout << '[' << i.first << ']';
            std::cout << ' ' << i.second << std::endl;
        }
    }

    {
        std::cout<<"Addition"<<std::endl;
        Matrix<int,1> matrix_1;
        matrix_1(1,1) = 10;
        matrix_1(1,2) = 10;
        Matrix<int,2> matrix_2;
        matrix_2(1,1) = 5;
        matrix_2(2,1) = 5;
        auto matrix_3 = matrix_1 + matrix_2;

        assert(matrix_3(1,1)== 15);
        assert(matrix_3(2,1)== 6);
        assert(matrix_3(1,2)== 12);
        assert(matrix_3.getDefaultNum() == 3);
        assert(matrix_3.size() == 3);

        std::cout << "matrix_1 defNum= " << matrix_1.getDefaultNum()<<std::endl;
        std::cout << "matrix_2 defNum= " << matrix_2.getDefaultNum()<<std::endl;
        std::cout << "New matrix (matrix_1 + matrix_2) defNum= " << matrix_3.getDefaultNum()<<std::endl;
        std::cout<<
            "matrix_1(1,1): "<< matrix_1(1,1) 
            <<" + "<< 
            "matrix_2(1,1): "<<matrix_2(1,1) 
            << " = " << 
            matrix_3(1,1)<<std::endl;
        std::cout<<
            "matrix_1(1,2): "<< matrix_1(1,2) 
            <<" + "<< 
            "matrix_2(1,2): "<<matrix_2(1,2) 
            << " = " << 
            matrix_3(1,2)<<std::endl;
        std::cout<<
            "matrix_1(2,1): "<< matrix_1(2,1) 
            <<" + "<< 
            "matrix_2(2,1): "<<matrix_2(2,1) 
            << " = " << 
            matrix_3(2,1)<<std::endl;
    }

    {
        std::cout<<"Substraction"<<std::endl;
        Matrix<int,1> matrix_1;
        matrix_1(1,1) = 10;
        matrix_1(1,2) = 10;
        Matrix<int,2> matrix_2;
        matrix_2(1,1) = 5;
        matrix_2(2,1) = 5;
        auto matrix_3 = matrix_1 - matrix_2;

        assert(matrix_3(1,1)== 5);
        assert(matrix_3(2,1)== -4);
        assert(matrix_3(1,2)== 8);
        assert(matrix_3.getDefaultNum() == -1);
        assert(matrix_3.size() == 3);

        std::cout << "matrix_1 defNum= " << matrix_1.getDefaultNum()<<std::endl;
        std::cout << "matrix_2 defNum= " << matrix_2.getDefaultNum()<<std::endl;
        std::cout << "New matrix (matrix_1 - matrix_2) defNum= " << matrix_3.getDefaultNum()<<std::endl;
        std::cout<<
            "matrix_1(1,1): "<< matrix_1(1,1) 
            <<" - "<< 
            "matrix_2(1,1): "<<matrix_2(1,1) 
            << " = " << 
            matrix_3(1,1)<<std::endl;
        std::cout<<
            "matrix_1(1,2): "<< matrix_1(1,2) 
            <<" - "<< 
            "matrix_2(1,2): "<<matrix_2(1,2) 
            << " = " << 
            matrix_3(1,2)<<std::endl;
        std::cout<<
            "matrix_1(2,1): "<< matrix_1(2,1) 
            <<" - "<< 
            "matrix_2(2,1): "<<matrix_2(2,1) 
            << " = " << 
            matrix_3(2,1)<<std::endl;
    }

    {
        std::cout<<"Reset"<<std::endl;
        Matrix<int,1> matrix_1;
        matrix_1(1,1) = 10;
        matrix_1(1,2) = 10;
        matrix_1.reset();
        assert(matrix_1.size() == 0);
    }

    {
        std::cout<<"multiple []"<<std::endl;
        Matrix<int,0,3> matrix;
        assert(matrix[0][1][0] == 0) ;
        matrix[0][1][0] = 10;
        assert(matrix[0][1][0] == 10);
        assert(matrix.size() == 1);
        matrix[0][1][1] = 10;
        matrix[0][1][2] = 10;
        assert(matrix.size() == 3);
        matrix[0][1][2] = 0;
        assert(matrix.size() == 2);
    }
    return 0;
}

