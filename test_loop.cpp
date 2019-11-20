#define BOOST_TEST_MODULE range_base_loop

#include "matrix.h"
#include <sstream>
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_range_base_loop)


BOOST_AUTO_TEST_CASE(Test_2D)
{
	Matrix<int,0> matrix;

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			matrix(i,j) = i+j+1;
		}
	}

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			BOOST_CHECK_EQUAL(matrix(i,j),i+j+1);
		}
	}

	BOOST_CHECK_EQUAL(matrix.size(),100);

	// for(auto& elem:matrix)
	// 	elem.second = 0;
	// instead:
	matrix.reset();

	BOOST_CHECK_EQUAL(matrix.size(),0);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			BOOST_CHECK_EQUAL(matrix(i, j), 0);
		}
	}


}

BOOST_AUTO_TEST_CASE(Test_3D)
{
	Matrix<int,0,3> matrix;

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			for (size_t k = 0; k < 10; k++)
			{
				matrix(i, j, k) = i + j + k + 1;
			}
		}
	}

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			for (size_t k = 0; k < 10; k++)
			{
				BOOST_CHECK_EQUAL(matrix(i,j,k),i+j+k+1);
			}
		}
	}

	BOOST_CHECK_EQUAL(matrix.size(),1000);

	// for(auto& elem:matrix)
	// 	elem.second = 0;
	// instead:
	matrix.reset();

	BOOST_CHECK_EQUAL(matrix.size(),0);

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			for (size_t k = 0; k < 10; k++)
			{
				BOOST_CHECK_EQUAL(matrix(i,j,k),0);
			}
		}
	}

}

BOOST_AUTO_TEST_CASE(Test_4D)
{
	const size_t N = 5;
	Matrix<int,0,4> matrix;

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			for (size_t k = 0; k < N; k++)
			{
				for (size_t t = 0; t < N; t++)
				{
					matrix(i, j, k, t) = i + j + k + t + 1;
				}
			}
		}
	}

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			for (size_t k = 0; k < N; k++)
			{
				for (size_t t = 0; t < N; t++)
				{
					BOOST_CHECK_EQUAL(matrix(i, j, k, t), i + j + k + t + 1);
				}
			}
		}
	}

	BOOST_CHECK_EQUAL(matrix.size(),N*N*N*N);

	// for(auto& elem:matrix)
	// 	elem.second = 0;
	// instead:
	matrix.reset();

	BOOST_CHECK_EQUAL(matrix.size(),0);

	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			for (size_t k = 0; k < N; k++)
			{
				for (size_t t = 0; t < N; t++)
				{
					BOOST_CHECK_EQUAL(matrix(i, j, k, t), 0);
				}
			}
		}
	}


}

BOOST_AUTO_TEST_SUITE_END()