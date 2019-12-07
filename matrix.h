#pragma once
#include <unordered_map>
#include <iostream>
#include <utility>
#include <boost/functional/hash.hpp>
#include <array>
#include <exception>

template <class T>
constexpr std::add_const_t<T>& as_const(T& t) noexcept
{
    return t;
}


template<class T, int defaultParam = 0,size_t dimentions = 2>
class Matrix{
    class IndexProxy;
public:
    using nsp_indx = std::array<size_t,dimentions> ;
    using matrix_core_ = std::unordered_map<nsp_indx,T,boost::hash<nsp_indx>>;
public:
    Matrix()=default;
    ~Matrix()=default;
    Matrix(const Matrix&)=default;
    Matrix(Matrix&&) =default;

    size_t size() const{
        return matrix_.size();
    }

    template <typename... Args>
    T operator()(Args&&... val) const
    {
        nsp_indx t_indx = indx_creat(std::forward<Args>(val)...);
        auto it_elem = matrix_.find(t_indx);
        if(it_elem ==  matrix_.end()){
            return (T)defaultParam;
        }
        return matrix_.at(t_indx);
    }

    template <typename... Args>
    IndexProxy operator() (Args&&... val){
        return{*this, indx_creat(std::forward<Args>(val)...)};
    }

    T operator() (const nsp_indx& indx)const {
        auto it_elem = matrix_.find(indx);
        if(it_elem ==  matrix_.end()){
            return (T)defaultParam;
        }
        return matrix_.at(indx);
    }

    IndexProxy operator() (const nsp_indx& indx){
        return{*this,indx};
    }

    IndexProxy operator[](size_t i){
        return {*this,i};
    }

    // IndexProxy(const Matrix<T,defaultParamRhs,dimentions>::IndexProxy& rhs) {
    //         return *this;
    // };

    size_t getDimention()const noexcept{
        return dimentions;
    }

    int getDefaultNum()const noexcept {
        return defaultParam;
    }

    void reset(){
        matrix_.clear();
    }
    
    // need IterProxy
    // auto begin(){
    //     return Matrix_iterator<decltype(std::begin(matrix_))>(std::begin(matrix_));
    // }

    // auto end(){
    //     return Matrix_iterator<decltype(std::end(matrix_))>(std::end(matrix_));    
    // }
    
    auto begin()const{
        return Matrix_iterator<decltype(std::cbegin(matrix_))>(std::begin(matrix_));
    }

    auto end()const{
        return Matrix_iterator<decltype(std::cend(matrix_))>(std::end(matrix_));    
    }

    template<class U, int defaultParamRhs>
    auto operator+ (const Matrix<U,defaultParamRhs,dimentions>& rhs)const{
        Matrix<U,defaultParamRhs+defaultParam,dimentions> result;

        for(const auto& elem:matrix_)
            result(elem.first) = elem.second + rhs(elem.first);

        for(const auto& r_elem:rhs)
            result(r_elem.first) = (*this)(r_elem.first) + r_elem.second;

        return result;
    }

    template<class U, int defaultParamRhs>
    auto operator- (const Matrix<U,defaultParamRhs,dimentions>& rhs)const{
        Matrix<U,defaultParam - defaultParamRhs,dimentions> result;

        for(const auto& elem:matrix_)
            result(elem.first) = elem.second -  rhs(elem.first);

        for(const auto& r_elem:rhs)
            result(r_elem.first) = (*this)(r_elem.first) - r_elem.second;

        return result;
    }

private:
    /* class IterProxy to handle something like 
	for(auto& elem:matrix)
		elem.second = 0;
    */
    template <typename Iter>
    class Matrix_iterator{
    public:
        Matrix_iterator(Iter matrix):itr_matrix_(matrix) {}

        bool operator!=(const Matrix_iterator& rhs){
            return itr_matrix_!=rhs.itr_matrix_;
        }

        Matrix_iterator operator++(){
            itr_matrix_=std::next(itr_matrix_);
            return *this;
        }

        auto& operator* (){
            return *itr_matrix_;
        }

    private:
        Iter itr_matrix_;
    };
    
private:
    class IndexProxy
	{
	public:
        IndexProxy(Matrix& matrix, const nsp_indx& indx):
            proxy_matrix_(matrix), indx_(indx),pos_in_indx{dimentions} {}

        IndexProxy(Matrix& matrix, size_t first_):
            proxy_matrix_(matrix), pos_in_indx{0} {indx_.at(pos_in_indx++) = first_;}

		IndexProxy(const IndexProxy&) = default;
		IndexProxy(IndexProxy&&) = default;
		~IndexProxy() = default;



        IndexProxy& operator[] (size_t n) {
            if(pos_in_indx >= dimentions)
                throw std::out_of_range("Out of range");

            while(pos_in_indx != dimentions){
                indx_.at(pos_in_indx++) = n;
                return *this;
            }
            return *this;
        }

        T operator=(T elem)
        {
            if(pos_in_indx < dimentions)
                throw std::range_error("Partial index was given");

            auto it_elem = proxy_matrix_.matrix_.find(indx_);

            if (it_elem == proxy_matrix_.matrix_.end() 
                && elem != (T)defaultParam)
            {
                proxy_matrix_.matrix_[indx_] = elem;
            }
            else if(elem == (T)defaultParam){
                proxy_matrix_.matrix_.erase(indx_);
            }
            else
                proxy_matrix_.matrix_[indx_] = elem;
            return elem;
        }

        operator T() const {
            if(pos_in_indx < dimentions)
                throw std::range_error("Partial index was given");

			return as_const(proxy_matrix_)(indx_);
		}

	private:
		Matrix& proxy_matrix_;
		nsp_indx indx_;
        size_t pos_in_indx;
	};

private:
    template <typename... Args>
    nsp_indx indx_creat(Args&&... val) const{
        if(sizeof...(val)>dimentions)
            throw std::out_of_range("out of matrix dimention");
        size_t i =0;
        nsp_indx indx;
        ((indx[i++]=val),...);
        return indx;
    }
private:
    matrix_core_ matrix_;
};