#include <funcy/cmath/pow.h>
#include <funcy/finalize.h>
#include <funcy/generate.h>

#include <gtest/gtest.h>

#include <gmock/gmock.h>

using ::testing::StrEq;

TEST( SubtractionTest, UpdateVariable )
{
    auto x = funcy::variable< 0 >( 1. );
    using funcy::Pow;
    auto fun = ( Pow< 3, 1 >( 2. ) - Pow< 3, 2 >( 1. ) )( x );
    EXPECT_DOUBLE_EQ( fun.d0(), 0 );
    EXPECT_NO_THROW( fun.update< 0 >( 4.0 ) );
    EXPECT_NO_THROW( fun.update( 0.0 ); );
    EXPECT_DOUBLE_EQ( fun.d0(), 56 );
}

TEST( SubtractionTest, D0 )
{
    using funcy::Pow;
    auto fun = Pow< 3, 1 >( 2. ) - Pow< 3, 2 >( 1. );
    EXPECT_DOUBLE_EQ( fun.d0(), 7 );
    fun.update( 1. );
    EXPECT_DOUBLE_EQ( fun.d0(), 0 );
}

TEST( SubtractionTest, D1 )
{
    using funcy::Pow;
    auto fun = funcy::finalize( Pow< 3, 1 >( 2. ) - Pow< 3, 2 >( 1. ) );
    EXPECT_DOUBLE_EQ( fun.d1( 1 ), 10.5 );
}

TEST( SubtractionTest, D2 )
{
    using funcy::Pow;
    auto fun = funcy::finalize( Pow< 3, 1 >( 2. ) - Pow< 3, 2 >( 1. ) );
    EXPECT_DOUBLE_EQ( fun.d2( 1, 1 ), 11.25 );
}

TEST( SubtractionTest, D3 )
{
    using funcy::Pow;
    auto fun = funcy::finalize( Pow< 3, 1 >( 2. ) - Pow< 3, 2 >( 1. ) );
    EXPECT_DOUBLE_EQ( fun.d3( 1, 1, 1 ), 6.375 );
}
