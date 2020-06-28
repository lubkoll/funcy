#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <funcy/mathop/max.h>
#include <funcy/cmath/pow.h>
#include <funcy/variable.h>

using testing::DoubleEq;

TEST(MaxTest, LhsIsFunction_UpdateAndD0)
{
    const auto x = funcy::Pow<1>(1.0);
    auto fun = funcy::max(x, 2.0);
    EXPECT_THAT(fun(), DoubleEq(2.0));
    fun.update(3.0);
    EXPECT_THAT(fun(), DoubleEq(3.0));
}

TEST(MaxTest, LhsIsFunction_D1)
{
    const auto x = funcy::Pow<1>(1.0);
    auto fun = funcy::max(x, 2.0);
    EXPECT_THAT(fun.d1<0>(1.0), DoubleEq(0.0));
    EXPECT_THAT(fun.d1<0>(2.0), DoubleEq(0.0));
    fun.update(3.0);
    EXPECT_THAT(fun.d1<0>(1.0), DoubleEq(1.0));
    EXPECT_THAT(fun.d1<0>(2.0), DoubleEq(2.0));
}

TEST(MaxTest, LhsIsFunction_D2)
{
    const auto x = funcy::Pow<2>(1.0);
    auto fun = funcy::max(x, 2.0);
    const auto f1 = fun.d2<0,0>(1.0, 1.0);
    EXPECT_THAT(f1, DoubleEq(0.0));
    const auto f2 = fun.d2<0,0>(2.0, 1.0);
    EXPECT_THAT(f2, DoubleEq(0.0));
    fun.update(3.0);
    const auto f3 = fun.d2<0,0>(1.0, 1.0);
    EXPECT_THAT(f3, DoubleEq(2.0));
    const auto f4 = fun.d2<0,0>(2.0, 1.0);
    EXPECT_THAT(f4, DoubleEq(4.0));
}

TEST(MaxTest, LhsIsFunction_D3)
{
    const auto x = funcy::Pow<3>(1.0);
    auto fun = funcy::max(x, 2.0);
    const auto f1 = fun.d3<0,0,0>(1.0, 1.0, 1.0);
    EXPECT_THAT(f1, DoubleEq(0.0));
    const auto f2 = fun.d3<0,0,0>(1.0, 2.0, 1.0);
    EXPECT_THAT(f2, DoubleEq(0.0));
    fun.update(3.0);
    const auto f3 = fun.d3<0,0,0>(1.0, 1.0, 1.0);
    EXPECT_THAT(f3, DoubleEq(6.0));
    const auto f4 = fun.d3<0,0,0>(1.0, 1.0, 2.0);
    EXPECT_THAT(f4, DoubleEq(12.0));
}

TEST(MaxTest, RhsIsFunction_UpdateAndD0)
{
    const auto x = funcy::Pow<1>(1.0);
    auto fun = funcy::max(2.0, x);
    EXPECT_THAT(fun(), DoubleEq(2.0));
    fun.update(3.0);
    EXPECT_THAT(fun(), DoubleEq(3.0));
}

TEST(MaxTest, RhsIsFunction_D1)
{
    const auto x = funcy::Pow<1>(1.0);
    auto fun = funcy::max(2.0, x);
    EXPECT_THAT(fun.d1<0>(1.0), DoubleEq(0.0));
    EXPECT_THAT(fun.d1<0>(2.0), DoubleEq(0.0));
    fun.update(2.0);
    EXPECT_THAT(fun.d1<0>(1.0), DoubleEq(1.0));
    EXPECT_THAT(fun.d1<0>(2.0), DoubleEq(2.0));
}

TEST(MaxTest, LhsAndRhsAreFunction_UpdateAndD0)
{
    const auto x = funcy::Pow<1>(2.0);
    const auto y = funcy::Pow<2>(1.0);
    auto fun = funcy::max(x, y);
    EXPECT_THAT(fun(), DoubleEq(2.0));
    fun.update(2.0);
    EXPECT_THAT(fun(), DoubleEq(4.0));
}

TEST(MaxTest, LhsAndRhsAreFunction_D1)
{
    const auto x = funcy::Pow<1>(2.0);
    const auto y = funcy::Pow<2>(1.0);
    auto fun = funcy::max(x, y);
    EXPECT_THAT(fun.d1<0>(1.0), DoubleEq(1.0));
    EXPECT_THAT(fun.d1<0>(2.0), DoubleEq(2.0));
    fun.update(1.1);
    EXPECT_THAT(fun.d1<0>(1.0), DoubleEq(2.2));
    EXPECT_THAT(fun.d1<0>(2.0), DoubleEq(4.4));
}

TEST(MaxTest, LhsIsVariable_UpdateAndD0)
{
    const auto x = funcy::variable<0>(2.0);
    const auto y = funcy::Pow<2>(1.0);
    auto fun = funcy::max(x, y);
    EXPECT_THAT(fun(), DoubleEq(2.0));
    fun.update(3.0);
    EXPECT_THAT(fun(), DoubleEq(9.0));
    fun.update<0>(10.0);
    EXPECT_THAT(fun(), DoubleEq(10.0));
}

TEST(MaxTest, LhsIsVariable_D1)
{
    const auto x = funcy::variable<0>(2.0);
    const auto y = funcy::Pow<2>(2.0);
    auto fun = funcy::max(x, y);
    EXPECT_THAT(fun.d1<0>(1.0), DoubleEq(4.0));
    EXPECT_THAT(fun.d1<0>(2.0), DoubleEq(8.0));
    fun.update(0.3);
    EXPECT_THAT(fun.d1<0>(1.0), DoubleEq(1.0));
    EXPECT_THAT(fun.d1<0>(2.0), DoubleEq(2.0));
    fun.update<0>(0.01);
    EXPECT_THAT(fun.d1<0>(1.0), DoubleEq(0.6));
    EXPECT_THAT(fun.d1<0>(2.0), DoubleEq(1.2));
}
