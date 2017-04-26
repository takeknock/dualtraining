#include "eval_tests.h"
#include "..\auto_differentiation\evals.h"
#include "..\auto_differentiation\operators.h"

TEST_F(eval_tests, test_add) {
    ad::Variable a = ad::Variable(1);
    ad::Constant b = ad::Constant(2);

    auto actual = a + b;
    int expected = 3;

    EXPECT_EQ(expected, eval(actual));
}

TEST_F(eval_tests, test_sub) {
    ad::Variable a = ad::Variable(1);
    ad::Constant b = ad::Constant(2);

    auto actual = b - a;
    int expected = 1;

    EXPECT_EQ(expected, eval(actual));
}

TEST_F(eval_tests, test_mul) {
    ad::Variable a = ad::Variable(1);
    ad::Constant b = ad::Constant(2);

    auto actual = a * b;
    int expected = 2;

    EXPECT_EQ(expected, eval(actual));
}

TEST_F(eval_tests, test_div) {
    ad::Variable a = ad::Variable(1);
    ad::Constant b = ad::Constant(2);

    auto actual = b / a;
    int expected = 2;

    EXPECT_EQ(expected, eval(actual));
}