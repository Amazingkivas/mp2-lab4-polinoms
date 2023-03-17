#include "polynom.h"
#include <gtest.h>

TEST(Polynom, can_create_polynom)
{
	ASSERT_NO_THROW(Polynom poly);
}

TEST(Polynom, can_add_monom)
{
	Polynom poly;
	ASSERT_NO_THROW(poly.add_monom(1, 111));
}

TEST(Polynom, reduction_when_add_monoms_with_equal_degrees)
{
	Polynom poly;
	poly.add_monom(1, 100);
	poly.add_monom(2, 100);
	Polynom res;
	res.add_monom(3, 100);
	EXPECT_EQ(poly, res);
}

TEST(Polynom, erase_when_add_monoms_with_equal_degrees_and_opposite_coefficient)
{
	Polynom poly;
	poly.add_monom(1, 100);
	poly.add_monom(-1, 100);
	Polynom res;
	EXPECT_EQ(poly, res);
}

TEST(Polynom, throws_when_add_monom_with_negative_degree)
{
	Polynom poly;
	ASSERT_ANY_THROW(poly.add_monom(1, -111));
}

TEST(Polynom, throws_when_add_monom_with_too_large_degree)
{
	Polynom poly;
	ASSERT_ANY_THROW(poly.add_monom(1, 1000));
}

TEST(Polynom, can_get_polynom_size)
{
	Polynom poly;
	EXPECT_EQ(0, poly.psize());
	poly.add_monom(1, 100);
	EXPECT_EQ(1, poly.psize());
}

TEST(Polynom, can_add_polynoms)
{
	Polynom poly1;
	Polynom poly2;
	poly1.add_monom(1, 100);
	poly1.add_monom(1, 105);
	poly1.add_monom(1, 300);
	poly2.add_monom(2, 200);
	poly2.add_monom(2, 105);
	poly2.add_monom(-1, 300);
	Polynom res;
	res.add_monom(2, 200);
	res.add_monom(3, 105);
	res.add_monom(1, 100);
	EXPECT_EQ(res, poly1 + poly2);
}

TEST(Polynom, can_subtract_polynoms)
{
	Polynom poly1;
	Polynom poly2;
	poly1.add_monom(1, 100);
	poly1.add_monom(1, 105);
	poly1.add_monom(1, 300);
	poly2.add_monom(2, 200);
	poly2.add_monom(2, 105);
	poly2.add_monom(1, 300);
	Polynom res;
	res.add_monom(-2, 200);
	res.add_monom(-1, 105);
	res.add_monom(1, 100);
	EXPECT_EQ(res, poly1 - poly2);
}

TEST(Polynom, can_multiply_polynoms)
{
	Polynom poly1;
	Polynom poly2;
	poly1.add_monom(1, 106);
	poly1.add_monom(1, 105);
	poly2.add_monom(2, 200);
	poly2.add_monom(-2, 201);
	Polynom res;
	res.add_monom(-2, 307);
	res.add_monom(2, 305);
	EXPECT_EQ(res, poly1 * poly2);
}

TEST(Polynom, throws_when_result_degree_is_invalid_after_multiply_polynoms)
{
	Polynom poly1;
	Polynom poly2;
	poly1.add_monom(1, 106);
	poly2.add_monom(2, 205);
	ASSERT_ANY_THROW(poly1 * poly2);
}

TEST(Polynom, can_multiply_polynoms_by_number)
{
	Polynom poly;
	poly.add_monom(1, 106);
	poly.add_monom(-0.5, 105);
	Polynom res;
	res.add_monom(-3, 106);
	res.add_monom(1.5, 105);
	EXPECT_EQ(res, poly * -3.0);
}

TEST(Polynom, can_compare_polynoms)
{
	Polynom pol1, pol2;
	pol1.add_monom(1.2, 1);
	pol1.add_monom(-0.1, 1);
	pol2.add_monom(1.1, 1);
	EXPECT_EQ(true, pol1 == pol2);
	EXPECT_EQ(false, pol1 != pol2);
}
