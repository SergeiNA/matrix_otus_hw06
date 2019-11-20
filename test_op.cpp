#define BOOST_TEST_MODULE arithmetic_op

#include "matrix.h"
#include <sstream>
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_matrix_operations)

BOOST_AUTO_TEST_CASE(Addition)
{
	const size_t N =10;
	Matrix<int,1,3> matrix1;
	for (size_t i = 0; i < N; i++)
	{
		matrix1(i,i,i) = 10;
	}

	Matrix<int,2,3> matrix2;

	for (size_t i = 0; i < N; i++)
	{
		matrix2(i,i,i) = -10;
		
	}

	matrix1(1,2,3) = 5;
	matrix2(3,2,1) = 5;

	auto matrix3 = matrix1 + matrix2;

	for (size_t i = 0; i < N; i++)
	{
		BOOST_CHECK_EQUAL(matrix3(i,i,i),0);
	}

	BOOST_CHECK_EQUAL(matrix3.getDefaultNum(),3);

	BOOST_CHECK_EQUAL(matrix3(1,2,3),7);
	BOOST_CHECK_EQUAL(matrix3(3,2,1),6);

}

BOOST_AUTO_TEST_CASE(Substraction)
{
	const size_t N =10;
	Matrix<int,1,3> matrix1;
	for (size_t i = 0; i < N; i++)
	{
		matrix1(i,i,i) = 10;
	}

	Matrix<int,2,3> matrix2;

	for (size_t i = 0; i < N; i++)
	{
		matrix2(i,i,i) = -10;
		
	}

	matrix1(1,2,3) = 5;
	matrix2(3,2,1) = 5;

	auto matrix3 = matrix1 - matrix2;

	for (size_t i = 0; i < N; i++)
	{
		BOOST_CHECK_EQUAL(matrix3(i,i,i),20);
	}

	BOOST_CHECK_EQUAL(matrix3.getDefaultNum(),-1);

	BOOST_CHECK_EQUAL(matrix3(1,2,3),3);
	BOOST_CHECK_EQUAL(matrix3(3,2,1),-4);

}

BOOST_AUTO_TEST_SUITE_END()