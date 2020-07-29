#include <funcy/cmath/cnd.h>

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <limits>

namespace
{
    using ::testing::DoubleEq;
    using ::testing::DoubleNear;

    const auto max_double = std::numeric_limits< double >::max();
    const auto min_double = std::numeric_limits< double >::lowest();
    const auto div_sqrt2pi = 1 / std::sqrt( 2 * M_PI );
} // namespace

TEST( CNDTest, D0 )
{
    auto fun = funcy::CumulativeNormalDistribution( 0.0 );
    EXPECT_THAT( fun(), DoubleEq( 0.5 ) );
    fun.update( min_double );
    EXPECT_THAT( fun(), DoubleEq( 0.0 ) );
    fun.update( max_double );
    EXPECT_THAT( fun(), DoubleEq( 1.0 ) );
}

TEST( CNDTest, D1 )
{
    auto fun = funcy::CumulativeNormalDistribution( 0.0 );
    const auto dx = 2.;
    EXPECT_THAT( fun.d1(), DoubleEq( div_sqrt2pi ) );
    EXPECT_THAT( fun.d1( dx ), DoubleEq( div_sqrt2pi * dx ) );
    fun.update( 1.0 );
    EXPECT_THAT( fun.d1(), DoubleEq( div_sqrt2pi * std::exp( -0.5 ) ) );
    EXPECT_THAT( fun.d1( dx ), DoubleEq( div_sqrt2pi * std::exp( -0.5 ) * dx ) );
}

TEST( CNDTest, D1DifferentialQuotient )
{
    auto fun = funcy::CumulativeNormalDistribution( 0.0 );
    const auto dx = 1e-8;
    const auto f0 = fun();
    const auto fun_d1 = fun.d1();
    fun.update( dx );
    EXPECT_THAT( fun_d1, DoubleNear( ( fun() - f0 ) / dx, dx ) );
}

TEST( CNDTest, D2 )
{
    auto fun = funcy::CumulativeNormalDistribution( 0.0 );
    const auto dx = 2.0;
    const auto dy = 3.0;
    EXPECT_THAT( fun.d2(), DoubleEq( 0.0 ) );
    EXPECT_THAT( fun.d2( dx, dy ), DoubleEq( 0.0 ) );
    fun.update( 1.0 );
    EXPECT_THAT( fun.d2(), DoubleEq( -div_sqrt2pi * std::exp( -0.5 ) ) );
    EXPECT_THAT( fun.d2( dx, dy ), DoubleEq( -div_sqrt2pi * std::exp( -0.5 ) * dx * dy ) );
}

TEST( CNDTest, D3 )
{
    auto fun = funcy::CumulativeNormalDistribution( 0.0 );
    const auto dx = 2.0;
    const auto dy = 3.0;
    const auto dz = 4.0;
    EXPECT_THAT( fun.d3(), DoubleEq( -div_sqrt2pi ) );
    EXPECT_THAT( fun.d3( dx, dy, dz ), DoubleEq( -div_sqrt2pi * dx * dy * dz ) );
    fun.update( 1.0 );
    EXPECT_THAT( fun.d3(), DoubleEq( 0.0 ) );
    EXPECT_THAT( fun.d3( dx, dy, dz ), DoubleEq( 0.0 ) );
}
