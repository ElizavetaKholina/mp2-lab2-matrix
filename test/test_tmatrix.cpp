#include "Matrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TMatrix<int> m(4));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TMatrix<int> m(-4));
}

TEST(TMatrix, can_create_copied_matrix)
{
	TMatrix<int> m(4);

	ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m(4);
	TMatrix<int> m1(m);
	ASSERT_EQ(m, m1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m(2);
	
	m[0] = 1;
	m[1] = 2;
	m[2] = 3;
	m[3] = 4;
	
	TMatrix<int> m1(m);
	ASSERT_NE(&m[0], &m1[0]);
	ASSERT_NE(&m[1], &m1[1]);
	ASSERT_NE(&m[2], &m1[2]);
	ASSERT_NE(&m[3], &m1[3]);

}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(4);
	ASSERT_NO_THROW(m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(4);
	m[0] = 7;

	EXPECT_EQ(7, m[0]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(3);

	ASSERT_ANY_THROW(TMatrix<int> m[-1]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(3);

	ASSERT_ANY_THROW(TMatrix<int> m[3]);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m(3);
	ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> m(3);
	TMatrix<int> m1(3);
	ASSERT_NO_THROW(m = m1);
}

//TEST(TMatrix, assign_operator_change_matrix_size)
//{
//	ADD_FAILURE();
//}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> m(3);
	TMatrix<int> m1(2);
	ASSERT_NO_THROW(m = m1);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m(3);
	TMatrix<int> m1(m);
	EXPECT_TRUE(m1 == m);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m(3);
	EXPECT_TRUE(m == m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m(3);
	TMatrix<int> m1(4);
	EXPECT_FALSE(m1 == m);
}

TEST(TVector, can_add_scalar_to_matrix)
{
	TMatrix<int> m(3);
	ASSERT_NO_THROW(m + 3);
}

TEST(TVector, can_subtract_scalar_from_matrix)
{
	TMatrix<int> m(3);
	ASSERT_NO_THROW(m - 3);
}

TEST(TVector, can_multiply_scalar_by_matrix)
{
	TMatrix<int> m(3);
	ASSERT_NO_THROW(m * 3);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m(3);
	TMatrix<int> m1(3);
	ASSERT_NO_THROW(m + m1);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m(3);
	TMatrix<int> m1(4);
	ASSERT_ANY_THROW(m + m1);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m(3);
	TMatrix<int> m1(3);
	ASSERT_NO_THROW(m - m1);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m(3);
	TMatrix<int> m1(4);
	ASSERT_ANY_THROW(m - m1);
}

TEST(TMatrix, can_multiply_matrices_with_equal_size)
{
	TMatrix<int> m(3);
	TMatrix<int> m1(3);
	ASSERT_NO_THROW(m * m1);
}

TEST(TMatrix, cant_multiply_matrixes_with_not_equal_size)
{
	TMatrix<int> m(3);
	TMatrix<int> m1(4);
	ASSERT_ANY_THROW(m * m1);
}
