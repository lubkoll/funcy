#include <funcy/cmath/erf.h>

#include <gtest/gtest.h>

using funcy::Erf;

namespace
{
    auto x0()
    {
        return 1.0;
    }
} // namespace

const auto scale = 2 / std::sqrt( M_PI );

TEST( ErfTest, D0 )
{
    auto fun = funcy::Erf( x0() );
    EXPECT_DOUBLE_EQ( fun.d0(), std::erf( x0() ) );
}

TEST( ErfTest, D1 )
{
    auto fun = funcy::Erf( x0() );
    auto dx = 2.;
    EXPECT_NEAR( fun.d1(), scale * std::exp( -x0() * x0() ), 1e-12 );
    EXPECT_NEAR( fun.d1( dx ), scale * std::exp( -x0() * x0() ) * dx, 1e-12 * dx );
}

TEST( ErfTest, D1DifferentialQuotient )
{
    auto fun = funcy::Erf( x0() );
    auto dx = 1e-8;
    auto f0 = fun();
    fun.update( x0() + dx );
    EXPECT_NEAR( fun.d1(), ( fun() - f0 ) / dx, dx );
}

TEST( ErfTest, D2 )
{
    const auto fun = funcy::Erf( x0() );
    const auto dx = 2.;
    const auto dy = 3.;
    EXPECT_NEAR( fun.d2(), -scale * 2 * x0() * std::exp( -x0() * x0() ), 1e-12 );
    EXPECT_NEAR( fun.d2( dx, dy ), -scale * 2 * x0() * std::exp( -x0() * x0() ) * dx * dy,
                 1e-12 * dx * dy );
}

TEST( ErfTest, D2DifferentialQuotient )
{
    auto fun = funcy::Erf( x0() );
    const auto dx = 1e-6;
    const auto f0 = fun();
    fun.update( x0() + dx );
    const auto f1 = fun();
    fun.update( x0() - dx );
    const auto f2 = fun();
    EXPECT_NEAR( fun.d2(), ( f1 + f2 - 2 * f0 ) / ( dx * dx ), 1e-5 );
}

TEST( ErfTest, D3 )
{
    auto fun = funcy::Erf( x0() );
    auto dx = 2., dy = 3., dz = 4.;
    EXPECT_NEAR( fun.d3(),
                 scale * 2 *
                     ( 2 * x0() * x0() * std::exp( -x0() * x0() ) - std::exp( -x0() * x0() ) ),
                 1e-12 );
}
