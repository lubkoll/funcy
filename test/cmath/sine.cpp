#include <funcy/cmath/sine.h>

#include <gtest/gtest.h>

namespace
{
    auto x0()
    {
        return 1.0;
    }

    auto condition()
    {
        return 1e1;
    }
} // namespace

TEST( SineTest, D0 )
{
    auto fun = funcy::Sin( x0() );
    EXPECT_DOUBLE_EQ( fun.d0(), sin( x0() ) );
}

TEST( SineTest, D1 )
{
    auto fun = funcy::Sin( x0() );
    double dx = 2.;
    EXPECT_DOUBLE_EQ( fun.d1(), cos( x0() ) );
    EXPECT_DOUBLE_EQ( fun.d1( dx ), cos( x0() ) * dx );
}

TEST( SineTest, D1DifferentialQuotient )
{
    auto fun = funcy::Sin( x0() );
    auto dx = 1e-8;
    auto f0 = fun();
    fun.update( x0() + dx );
    EXPECT_NEAR( fun.d1(), ( fun() - f0 ) / dx, dx * condition() );
}

TEST( SineTest, D2 )
{
    auto fun = funcy::Sin( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    EXPECT_DOUBLE_EQ( fun.d2(), -sin( x0() ) );
    EXPECT_DOUBLE_EQ( fun.d2( dx, dy ), -sin( x0() ) * dx * dy );
}

TEST( SineTest, D3 )
{
    auto fun = funcy::Sin( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    const auto dz = 4.0;
    EXPECT_DOUBLE_EQ( fun.d3(), -cos( x0() ) );
    EXPECT_DOUBLE_EQ( fun.d3( dx, dy, dz ), -cos( x0() ) * dx * dy * dz );
}
