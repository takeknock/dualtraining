#include "dual_tests.h"

#include "../auto_differentiation/dual_number.h"

TEST_F(dual_tests, add_test)
{
    // f(x) = 2.0 + x_j + 5
    // f'(x) = 1.0
    const double expected = 1.0;
    ad::dual_number<double, double> x_j = ad::dual_number<double, double>(3.0, 1.0);
    ad::dual_number<double, double> c_1 = ad::dual_number<double, double>(2.0, 0.0);
    ad::dual_number<int, double> c_2 = ad::dual_number<int, double>(5, 0.0);
    const ad::dual_number<double, double> actual = c_1 + x_j + c_2;
    EXPECT_DOUBLE_EQ(expected, actual.d());
}

TEST_F(dual_tests, sub_test)
{
    // f(x) = 5.0 - x_j - 1
    // f'(x) = - 1.0

    ad::dual_number<double, double> x_j = ad::dual_number<double, double>(2.0, 1.0);
    ad::dual_number<double, double> c_1 = ad::dual_number<double, double>(5.0, 0.0);
    ad::dual_number<int, double> c_2 = ad::dual_number<int, double>(1, 0.0);

    const double expected = - 1.0;
    const ad::dual_number<double, double> actual = c_1 - x_j - c_2;
    EXPECT_DOUBLE_EQ(expected, actual.d());
}

TEST_F(dual_tests, mul_test)
{
    // f(x) = 5 * x_j + 2.0 * x_j * x_j
    // f'(x) = 4.0 * x_j + 5.0
    ad::dual_number<double, double> x_j = ad::dual_number<double, double>(2.0, 1.0);
    ad::dual_number<int, double> c_1 = ad::dual_number<int, double>(5, 0.0);
    ad::dual_number<double, double> c_2 = ad::dual_number<double, double>(2.0, 0.0);


    const double expected = 13.0;
    const ad::dual_number<double, double> actual = c_1 * x_j + x_j * x_j * c_2;
    EXPECT_DOUBLE_EQ(expected, actual.d());
}

TEST_F(dual_tests, div_test)
{
    // f(x) = 5.0 / x_j + x_j / 2.0
    // f'(x) = - 4.0 / (x_j * x_j) + 2.0
    ad::dual_number<double, double> x_j = ad::dual_number<double, double>(2.0, 1.0);
    ad::dual_number<double, double> c_1 = ad::dual_number<double, double>(5.0, 0.0);
    ad::dual_number<int, double> c_2 = ad::dual_number<int, double>(2, 0.0);


    const double expected = 1.0;
    const ad::dual_number<double, double> actual = c_1 / x_j + x_j / c_2;
    EXPECT_DOUBLE_EQ(expected, actual.d());
}