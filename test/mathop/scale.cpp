//#include <stringy/cmath/pow.hh>
//#include <texy/generate.hh>
#include <funcy/cmath/pow.h>
#include <funcy/finalize.h>
#include <funcy/generate.h>
#include <funcy/variable.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;
using ::testing::StrEq;

TEST( ScaleTest, Update )
{
    auto fun = 2 * funcy::Pow< 3, 1 >( 2. );
    EXPECT_NO_THROW( fun.update( -1 ) );
    EXPECT_DOUBLE_EQ( fun.d0(), -2. );
}

TEST( ScaleTest, UpdateVariable )
{
    auto x = funcy::variable< 0 >( 2. );
    auto fun = ( 2 * funcy::Pow< 3, 1 >() )( x );
    EXPECT_DOUBLE_EQ( fun.d0(), 16. );
    EXPECT_NO_THROW( fun.update< 0 >( -1. ) );
    EXPECT_NO_THROW( fun.update( 0 ); );
    EXPECT_DOUBLE_EQ( fun.d0(), -2. );
}

TEST( ScaleTest, D0 )
{
    using funcy::Pow;
    const auto fun = 2 * Pow< 3, 1 >( 2. );
    EXPECT_DOUBLE_EQ( fun.d0(), 16. );
}

// TEST( StringifyScaleTest, D0 )
//{
//    using stringy::Pow;
//    const auto fun = 2 * Pow< 3, 1 >();
//    EXPECT_THAT( fun.d0(), StrEq( "2*x^3" ) );
//}

TEST( ScaleTest, D1 )
{
    using funcy::Pow;
    const auto fun = funcy::finalize( 2 * Pow< 3, 1 >( 2. ) );
    EXPECT_DOUBLE_EQ( fun.d1( 1 ), 24. );
}

// TEST( StringifyScaleTest, D1 )
//{
//    using stringy::Pow;
//    const auto fun = funcy::finalize( 2 * Pow< 3, 1 >() );
//    EXPECT_THAT( fun.d1( "" ), StrEq( "2*3x^2" ) );
//}

TEST( ScaleTest, D2 )
{
    using funcy::Pow;
    const auto fun = funcy::finalize( 2 * Pow< 3, 1 >( 2. ) );
    EXPECT_DOUBLE_EQ( fun.d2( 1, 1 ), 24. );
}

// TEST( StringifyScaleTest, D2 )
//{
//    using stringy::Pow;
//    const auto fun = funcy::finalize( 2 * Pow< 3, 1 >() );
//    EXPECT_THAT( fun.d2( "", "" ), StrEq( "2*6x" ) );
//}

TEST( ScaleTest, D3 )
{
    using funcy::Pow;
    const auto fun = funcy::finalize( 2 * Pow< 3, 1 >( 2. ) );
    EXPECT_DOUBLE_EQ( fun.d3( 1, 1, 1 ), 12. );
}

// TEST( StringifyScaleTest, D3 )
//{
//    using stringy::Pow;
//    auto fun = funcy::finalize( 2 * Pow< 3, 1 >() );
//    EXPECT_THAT( fun.d3( "", "", "" ), StrEq( "2*6" ) );
//}
