#include "matrix.h"
#include <iomanip>

template<class matrix_type>
void pretty_print_flat(const matrix_type& matrix, size_t m, size_t n,size_t m_0=0, size_t n_0=0)
{
    for (size_t i = m_0; i < m; ++i)
        for (size_t j = n_0; j < n; ++j)
            std::cout << "Element(" << i << "," << j << "): " << matrix(i, j) << std::endl;
}

template<class matrix_type>
void pretty_print_rect(const matrix_type& matrix, size_t m, size_t n,size_t m_0=0, size_t n_0=0)
{
    std::cout<<std::endl;
    for (size_t i = m_0; i < m; ++i){
        std::cout<<"[";
        for (size_t j = n_0; j < n; ++j)
            std::cout<<std::setw(4)<< matrix(i, j);
        std::cout<<"]"<<std::endl;
    }
}

int main([[maybe_unused]]int argc, [[maybe_unused]]const char** argv) {
    
    Matrix<int,3> matrix;
    std::cout<<"size: "<<matrix.size()<<std::endl;
    matrix(0,0) =-1;
    matrix(1,1) =-1;
    matrix(2,2) =-1;
    matrix(3,3) =3;
    
    std::cout<<"size: "<<matrix.size()<<std::endl;
    pretty_print_flat(matrix,5,5);
    pretty_print_rect(matrix,5,5);
    for(const auto& i: matrix){
        std::cout<<'['<<i.first.first<<'.'<<i.first.second<<']';
        std::cout<<' '<<i.second<<std::endl;
    }
    matrix(2,2) = 3;
    std::cout<<"size: "<<matrix.size()<<std::endl;

    Matrix<int,0> matrix_0;
    const size_t N =10;
    for (size_t i = 0; i < N; i++)
    {
        matrix_0(i,i) = i ;
        matrix_0(N - 1 - i,i) = i;
    }
    pretty_print_rect(matrix_0,N,N);
    
    std::cout<<"size: "<<matrix_0.size()<<std::endl;

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = i%2; j < N; j+=2)
        {
            matrix_0(i,j) = 0;
        }
    }
    std::cout<<"size: "<<matrix_0.size()<<std::endl;

    pretty_print_rect(matrix_0,N,N);


    N_mtx<int,3> d3_mtx;
    d3_mtx[std::array<int,3>{0,0,0}] = 1;
    return 0;
}

