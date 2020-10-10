#include <gtest/gtest.h>
#define FUNCY_ENABLE_EXCEPTIONS
#include <funcy/cmath/log.h>

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

TEST( LNTest, Update )
{
    auto fun = funcy::LN( x0() );
    EXPECT_THROW( fun.update( 0 ), funcy::OutOfDomainException );
}

TEST( LNTest, D0 )
{
    auto fun = funcy::LN( x0() );
    EXPECT_DOUBLE_EQ( fun.d0(), log( x0() ) );
}

TEST( LNTest, D1 )
{
    auto fun = funcy::LN( x0() );
    const double dx = 2.;
    EXPECT_DOUBLE_EQ( fun.d1(), 1. );
    EXPECT_DOUBLE_EQ( fun.d1( dx ), dx );
}

TEST( LNTest, D1DifferentialQuotient )
{
    auto fun = funcy::LN( x0() );
    auto dx = 1e-8;
    auto f0 = fun();
    fun.update( x0() + dx );
    EXPECT_NEAR( fun.d1(), ( fun() - f0 ) / dx, dx * condition() );
}

TEST( LNTest, D2 )
{
    auto fun = funcy::LN( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    EXPECT_DOUBLE_EQ( fun.d2(), -1. );
    EXPECT_DOUBLE_EQ( fun.d2( dx, dy ), -dx * dy );
}

TEST( LNTest, D3 )
{
    auto fun = funcy::LN( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    const auto dz = 4.0;
    EXPECT_DOUBLE_EQ( fun.d3(), 2. );
    EXPECT_DOUBLE_EQ( fun.d3( dx, dy, dz ), 2 * dx * dy * dz );
}

///
TEST( Log2Test, Update )
{
    auto fun = funcy::Log2( x0() );
    EXPECT_THROW( fun.update( 0 ), funcy::OutOfDomainException );
}

TEST( Log2Test, D0 )
{
    auto fun = funcy::Log2( x0() );
    EXPECT_DOUBLE_EQ( fun.d0(), log2( x0() ) );
}

TEST( Log2Test, D1 )
{
    auto fun = funcy::Log2( x0() );
    const double dx = 2.;
    const double ln2 = log( 2 );
    EXPECT_DOUBLE_EQ( fun.d1(), 1 / ln2 );
    EXPECT_DOUBLE_EQ( fun.d1( dx ), dx / ln2 );
}

TEST( Log2Test, D1DifferentialQuotient )
{
    auto fun = funcy::Log2( x0() );
    auto dx = 1e-8;
    auto f0 = fun();
    fun.update( x0() + dx );
    EXPECT_NEAR( fun.d1(), ( fun() - f0 ) / dx, dx * condition() );
}

TEST( Log2Test, D2 )
{
    auto fun = funcy::Log2( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    const double ln2 = log( 2 );
    EXPECT_DOUBLE_EQ( fun.d2(), -1 / ln2 );
    EXPECT_DOUBLE_EQ( fun.d2( dx, dy ), -dx * dy / ln2 );
}

TEST( Log2Test, D3 )
{
    auto fun = funcy::Log2( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    const auto dz = 4.0;
    const double ln2 = log( 2 );
    EXPECT_DOUBLE_EQ( fun.d3(), 2 / ln2 );
    EXPECT_DOUBLE_EQ( fun.d3( dx, dy, dz ), 2 / ln2 * dx * dy * dz );
}

///
TEST( Log10Test, Update )
{
    auto fun = funcy::Log10( x0() );
    EXPECT_THROW( fun.update( 0 ), funcy::OutOfDomainException );
}

TEST( Log10Test, D0 )
{
    auto fun = funcy::Log10( x0() );
    EXPECT_DOUBLE_EQ( fun.d0(), log10( x0() ) );
}

TEST( Log10Test, D1 )
{
    auto fun = funcy::Log10( x0() );
    const double dx = 2.;
    const double ln10 = log( 10 );
    EXPECT_DOUBLE_EQ( fun.d1(), 1 / ln10 );
    EXPECT_DOUBLE_EQ( fun.d1( dx ), dx / ln10 );
}

TEST( Log10Test, D1DifferentialQuotient )
{
    auto fun = funcy::Log10( x0() );
    auto dx = 1e-8;
    auto f0 = fun();
    fun.update( x0() + dx );
    EXPECT_NEAR( fun.d1(), ( fun() - f0 ) / dx, dx * condition() );
}

TEST( Log10Test, D2 )
{
    auto fun = funcy::Log10( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    const double ln10 = log( 10 );
    EXPECT_DOUBLE_EQ( fun.d2(), -1 / ln10 );
    EXPECT_DOUBLE_EQ( fun.d2( dx, dy ), -dx * dy / ln10 );
}

TEST( Log10Test, D3 )
{
    auto fun = funcy::Log10( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    const auto dz = 4.0;
    const double ln10 = log( 10 );
    EXPECT_DOUBLE_EQ( fun.d3(), 2 / ln10 );
    EXPECT_DOUBLE_EQ( fun.d3( dx, dy, dz ), 2 / ln10 * dx * dy * dz );
}

TEST( LNTest, OutOfDomainException )
{
    auto fun = funcy::LN( x0() );
    EXPECT_THROW( fun.update( -2 ), funcy::OutOfDomainException );
}

TEST( Log2Test, OutOfDomainException )
{
    auto fun = funcy::Log2( x0() );
    EXPECT_THROW( fun.update( -2 ), funcy::OutOfDomainException );
}

TEST( Log10Test, OutOfDomainException )
{
    auto fun = funcy::Log10( x0() );
    EXPECT_THROW( fun.update( -2 ), funcy::OutOfDomainException );
}
