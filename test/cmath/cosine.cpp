#include <funcy/cmath/cosine.h>

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

TEST( CosineTest, D0 )
{
    auto fun = funcy::Cos( x0() );
    EXPECT_DOUBLE_EQ( fun.d0(), cos( x0() ) );
}

TEST( CosineTest, D1 )
{
    auto fun = funcy::Cos( x0() );
    double dx = 2.;
    EXPECT_DOUBLE_EQ( fun.d1(), -sin( x0() ) );
    EXPECT_DOUBLE_EQ( fun.d1( dx ), -sin( x0() ) * dx );
}

TEST( CosineTest, D1DifferentialQuotient )
{
    auto fun = funcy::Cos( x0() );
    auto dx = 1e-8;
    auto f0 = fun();
    fun.update( x0() + dx );
    EXPECT_NEAR( fun.d1(), ( fun() - f0 ) / dx, dx * condition() );
}

TEST( CosineTest, D2 )
{
    auto fun = funcy::Cos( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    EXPECT_DOUBLE_EQ( fun.d2(), -cos( x0() ) );
    EXPECT_DOUBLE_EQ( fun.d2( dx, dy ), -cos( x0() ) * dx * dy );
}

TEST( CosineTest, D3 )
{
    auto fun = funcy::Cos( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    const auto dz = 4.0;
    EXPECT_DOUBLE_EQ( fun.d3(), sin( x0() ) );
    EXPECT_DOUBLE_EQ( fun.d3( dx, dy, dz ), sin( x0() ) * dx * dy * dz );
}
