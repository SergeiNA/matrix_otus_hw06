#pragma once
#include <unordered_map>
#include <iostream>
#include <utility>
#include <boost/functional/hash.hpp>
#include <array>


template<class T,size_t Space, size_t defaultParam = 0>
class Matrix{
public:
    typedef std::array<size_t,Space> elem_pos;
    // typedef std::unordered_map<elem_pos,T,boost::hash<elem_pos>> matrix_core_;
    using matrix_core_ = std::unordered_map<elem_pos,T,boost::hash<elem_pos>>;

private:
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

        // T& operator* (){
        //     return itr_matrix_->second;
        // }

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
		IndexProxy(Matrix& matrix, const elem_pos& pos):proxy_matrix_(matrix), pos_(pos){}
		IndexProxy(const IndexProxy&) = default;
		IndexProxy(IndexProxy&&) = default;
		~IndexProxy() = default;

        IndexProxy &operator=(T elem)
        {
            auto it_elem = proxy_matrix_.matrix_.find(pos_);

            if (it_elem == proxy_matrix_.matrix_.end() 
                && elem != (T)defaultParam)
            {
                proxy_matrix_.matrix_[pos_] = elem;
            }
            else if(elem == (T)defaultParam){
                proxy_matrix_.matrix_.erase(pos_);
                return *this;
            }
            else
                proxy_matrix_.matrix_[pos_] = elem;
            return *this;
        }

        operator T()const {
			return std::as_const(proxy_matrix_)(pos_.first,pos_.second);
		}

	private:
		Matrix& proxy_matrix_;
		elem_pos pos_;
	};

public:
    Matrix()=default;
    ~Matrix()=default;
    Matrix(const Matrix&)=default;
    Matrix(Matrix&&) =default;

    size_t size(){
        return matrix_.size();
    }

/*

template<typename... Args>
    Node (Args&&... val):value(std::forward<Args>(val)...)
*/

    T operator() (size_t n, size_t m)const {
        auto it_elem = matrix_.find(std::make_pair(n,m));
        if(it_elem ==  matrix_.end()){
            return (T)defaultParam;
        }
        return matrix_.at(std::make_pair(n,m));
    }
    IndexProxy operator() (size_t n, size_t m){
        return{*this,std::make_pair(n,m)};
    }

    // T operator() (size_t n, size_t m)const {
    //     auto it_elem = matrix_.find(std::make_pair(n,m));
    //     if(it_elem ==  matrix_.end()){
    //         return (T)defaultParam;
    //     }
    //     return matrix_.at(std::make_pair(n,m));
    // }
    // IndexProxy operator() (size_t n, size_t m){
    //     return{*this,std::make_pair(n,m)};
    // }

    auto begin(){
        return Matrix_iterator<decltype(std::begin(matrix_))>(std::begin(matrix_));
    }
    auto end(){
        return Matrix_iterator<decltype(std::end(matrix_))>(std::end(matrix_));    
    }
    
    auto begin()const{
        return Matrix_iterator<decltype(std::cbegin(matrix_))>(std::begin(matrix_));
    }
    auto end()const{
        return Matrix_iterator<decltype(std::cend(matrix_))>(std::end(matrix_));    
    }
private:
    matrix_core_ matrix_;
};