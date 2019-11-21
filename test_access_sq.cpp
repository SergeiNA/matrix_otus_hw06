#define BOOST_TEST_MODULE test_access

#include "matrix.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_access)

BOOST_AUTO_TEST_CASE(Test_2D)
{
	Matrix<int,0> matrix;

	BOOST_CHECK_EQUAL(matrix[0][0],0);
	BOOST_CHECK_EQUAL(matrix[12][100],0);
	BOOST_CHECK_EQUAL(matrix.getDefaultNum(),0);
	BOOST_CHECK_EQUAL(matrix.size(),0);
	
	matrix[0][0] = 1;
	matrix[1][10] = 10;
	BOOST_CHECK_EQUAL(matrix[0][0],1);
	BOOST_CHECK_EQUAL(matrix[1][10],10);
	BOOST_CHECK_EQUAL(matrix[12][100],0);
	BOOST_CHECK_EQUAL(matrix.size(),2);

	matrix[1][10] = 0;
	BOOST_CHECK_EQUAL(matrix[0][0],1);
	BOOST_CHECK_EQUAL(matrix[1][10],0);
	BOOST_CHECK_EQUAL(matrix[12][100],0);
	BOOST_CHECK_EQUAL(matrix.size(),1);

	matrix[1][10] = 10;
	matrix[10][10] = 10;

	BOOST_CHECK_EQUAL(matrix[0][0],1);
	BOOST_CHECK_EQUAL(matrix[1][10],10);
	BOOST_CHECK_EQUAL(matrix[10][10],10);
	BOOST_CHECK_EQUAL(matrix.size(),3);

	matrix[1][10] = 0;

	BOOST_CHECK_EQUAL(matrix[0][0],1);
	BOOST_CHECK_EQUAL(matrix[0][10],0);
	BOOST_CHECK_EQUAL(matrix[10][10],10);
	BOOST_CHECK_EQUAL(matrix.size(),2);

}

BOOST_AUTO_TEST_CASE(Test_3D)
{
	Matrix<int,0,3> matrix;

	BOOST_CHECK_EQUAL(matrix[0][0][0],0);
	BOOST_CHECK_EQUAL(matrix[12][100][100],0);
	BOOST_CHECK_EQUAL(matrix.getDefaultNum(),0);
	BOOST_CHECK_EQUAL(matrix.size(),0);
	
	matrix[0][0][0] = 1;
	matrix[1][10][1] = 10;
	BOOST_CHECK_EQUAL(matrix[0][0][0],1);
	BOOST_CHECK_EQUAL(matrix[1][10][1],10);
	BOOST_CHECK_EQUAL(matrix[12][100][100],0);
	BOOST_CHECK_EQUAL(matrix.size(),2);

	matrix[1][10][1] = 0;
	BOOST_CHECK_EQUAL(matrix[0][0][0],1);
	BOOST_CHECK_EQUAL(matrix[1][10][1],0);
	BOOST_CHECK_EQUAL(matrix[12][100][100],0);
	BOOST_CHECK_EQUAL(matrix.size(),1);

	matrix[1][10][1] = 10;
	matrix[10][10][1] = 10;

	BOOST_CHECK_EQUAL(matrix[0][0][0],1);
	BOOST_CHECK_EQUAL(matrix[1][10][1],10);
	BOOST_CHECK_EQUAL(matrix[10][10][1],10);
	BOOST_CHECK_EQUAL(matrix.size(),3);

	matrix[1][10][1] = 0;

	BOOST_CHECK_EQUAL(matrix[0][0][0],1);
	BOOST_CHECK_EQUAL(matrix[0][10][1],0);
	BOOST_CHECK_EQUAL(matrix[10][10][1],10);
	BOOST_CHECK_EQUAL(matrix.size(),2);

}

BOOST_AUTO_TEST_CASE(Test_4D)
{
	Matrix<int,0,4> matrix;

	BOOST_CHECK_EQUAL(matrix[0][0][0][0],0);
	BOOST_CHECK_EQUAL(matrix[12][100][100][0],0);
	BOOST_CHECK_EQUAL(matrix.getDefaultNum(),0);
	BOOST_CHECK_EQUAL(matrix.size(),0);
	
	matrix[0][0][0][0] = 1;
	matrix[1][10][1][0] = 10;
	BOOST_CHECK_EQUAL(matrix[0][0][0][0],1);
	BOOST_CHECK_EQUAL(matrix[1][10][1][0],10);
	BOOST_CHECK_EQUAL(matrix[12][100][100][0],0);
	BOOST_CHECK_EQUAL(matrix.size(),2);

	matrix[1][10][1][0] = 0;
	BOOST_CHECK_EQUAL(matrix[0][0][0][0],1);
	BOOST_CHECK_EQUAL(matrix[1][10][1][0],0);
	BOOST_CHECK_EQUAL(matrix[12][100][100][0],0);
	BOOST_CHECK_EQUAL(matrix.size(),1);

	matrix[1][10][1][0] = 10;
	matrix[10][10][1][0] = 10;

	BOOST_CHECK_EQUAL(matrix[0][0][0][0],1);
	BOOST_CHECK_EQUAL(matrix[1][10][1][0],10);
	BOOST_CHECK_EQUAL(matrix[10][10][1][0],10);
	BOOST_CHECK_EQUAL(matrix.size(),3);

	matrix[1][10][1][0] = 0;

	BOOST_CHECK_EQUAL(matrix[0][0][0][0],1);
	BOOST_CHECK_EQUAL(matrix[0][10][1][0],0);
	BOOST_CHECK_EQUAL(matrix[10][10][1][0],10);
	BOOST_CHECK_EQUAL(matrix.size(),2);

}

BOOST_AUTO_TEST_SUITE_END()