#include <funcy/cmath/exp.h>

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

TEST( ExpTest, D0 )
{
    auto fun = funcy::Exp( x0() );
    EXPECT_DOUBLE_EQ( fun.d0(), exp( x0() ) );
}

TEST( ExpTest, D1 )
{
    auto fun = funcy::Exp( x0() );
    auto dx = 2.;
    EXPECT_DOUBLE_EQ( fun.d1(), exp( x0() ) );
    EXPECT_DOUBLE_EQ( fun.d1( dx ), exp( x0() ) * dx );
}

TEST( ExpTest, D1DifferentialQuotient )
{
    auto fun = funcy::Exp( x0() );
    auto dx = 1e-8;
    auto f0 = fun();
    fun.update( x0() + dx );
    EXPECT_NEAR( fun.d1(), ( fun() - f0 ) / dx, dx * condition() );
}

TEST( ExpTest, D2 )
{
    auto fun = funcy::Exp( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    EXPECT_DOUBLE_EQ( fun.d2(), exp( x0() ) );
    EXPECT_DOUBLE_EQ( fun.d2( dx, dy ), exp( x0() ) * dx * dy );
}

TEST( ExpTest, D3 )
{
    auto fun = funcy::Exp( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    const auto dz = 4.0;
    EXPECT_DOUBLE_EQ( fun.d3(), exp( x0() ) );
    EXPECT_DOUBLE_EQ( fun.d3( dx, dy, dz ), exp( x0() ) * dx * dy * dz );
}

TEST( Exp2Test, D0 )
{
    auto fun = funcy::Exp2( x0() );
    EXPECT_DOUBLE_EQ( fun.d0(), exp2( x0() ) );
}

TEST( Exp2Test, D1 )
{
    auto fun = funcy::Exp2( x0() );
    auto dx = 2.;
    auto ln2 = log( 2 );
    EXPECT_DOUBLE_EQ( fun.d1(), exp2( x0() ) * ln2 );
    EXPECT_DOUBLE_EQ( fun.d1( dx ), exp2( x0() ) * ln2 * dx );
}

TEST( Exp2Test, D1DifferentialQuotient )
{
    auto fun = funcy::Exp2( x0() );
    auto dx = 1e-8;
    auto f0 = fun();
    fun.update( x0() + dx );
    EXPECT_NEAR( fun.d1(), ( fun() - f0 ) / dx, dx * condition() );
}

TEST( Exp2Test, D2 )
{
    auto fun = funcy::Exp2( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    auto ln2 = log( 2 );
    EXPECT_DOUBLE_EQ( fun.d2(), exp2( x0() ) * ln2 * ln2 );
    EXPECT_DOUBLE_EQ( fun.d2( dx, dy ), exp2( x0() ) * ln2 * ln2 * dx * dy );
}

TEST( Exp2Test, D3 )
{
    auto fun = funcy::Exp2( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    const auto dz = 4.0;
    auto ln2 = log( 2 );
    EXPECT_DOUBLE_EQ( fun.d3(), exp2( x0() ) * ln2 * ln2 * ln2 );
    EXPECT_DOUBLE_EQ( fun.d3( dx, dy, dz ), exp2( x0() ) * ln2 * ln2 * ln2 * dx * dy * dz );
}
