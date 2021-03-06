#include <funcy/cmath/pow.h>
#include <funcy/mathop/min.h>
#include <funcy/variable.h>

#include <gtest/gtest.h>

#include <gmock/gmock.h>

using testing::DoubleEq;

TEST( MinTest, LhsIsFunction_UpdateAndD0 )
{
    const auto x = funcy::Pow< 1 >( 2.0 );
    auto fun = funcy::min( x, 1.0 );
    EXPECT_THAT( fun(), DoubleEq( 1.0 ) );
    fun.update( 0.5 );
    EXPECT_THAT( fun(), DoubleEq( 0.5 ) );
}

TEST( MinTest, LhsIsFunction_D1 )
{
    const auto x = funcy::Pow< 1 >( 2.0 );
    auto fun = funcy::min( x, 1.0 );
    EXPECT_THAT( fun.d1< -1 >( 1.0 ), DoubleEq( 0.0 ) );
    EXPECT_THAT( fun.d1< -1 >( 2.0 ), DoubleEq( 0.0 ) );
    fun.update( 0.5 );
    EXPECT_THAT( fun.d1< -1 >( 1.0 ), DoubleEq( 1.0 ) );
    EXPECT_THAT( fun.d1< -1 >( 2.0 ), DoubleEq( 2.0 ) );
}

TEST( MinTest, LhsIsFunction_D2 )
{
    const auto x = funcy::Pow< 2 >( 2.0 );
    auto fun = funcy::min( x, 1.0 );
    const auto f1 = fun.d2< -1, -1 >( 1.0, 1.0 );
    EXPECT_THAT( f1, DoubleEq( 0.0 ) );
    const auto f2 = fun.d2< -1, -1 >( 2.0, 1.0 );
    EXPECT_THAT( f2, DoubleEq( 0.0 ) );
    fun.update( 0.5 );
    const auto f3 = fun.d2< -1, -1 >( 1.0, 1.0 );
    EXPECT_THAT( f3, DoubleEq( 2.0 ) );
    const auto f4 = fun.d2< -1, -1 >( 2.0, 1.0 );
    EXPECT_THAT( f4, DoubleEq( 4.0 ) );
}

TEST( MinTest, LhsIsFunction_D3 )
{
    const auto x = funcy::Pow< 3 >( 2.0 );
    auto fun = funcy::min( x, 1.0 );
    const auto f1 = fun.d3< -1, -1, -1 >( 1.0, 1.0, 1.0 );
    EXPECT_THAT( f1, DoubleEq( 0.0 ) );
    const auto f2 = fun.d3< -1, -1, -1 >( 1.0, 2.0, 1.0 );
    EXPECT_THAT( f2, DoubleEq( 0.0 ) );
    fun.update( 0.5 );
    const auto f3 = fun.d3< -1, -1, -1 >( 1.0, 1.0, 1.0 );
    EXPECT_THAT( f3, DoubleEq( 6.0 ) );
    const auto f4 = fun.d3< -1, -1, -1 >( 1.0, 1.0, 2.0 );
    EXPECT_THAT( f4, DoubleEq( 12.0 ) );
}

TEST( MinTest, RhsIsFunction_UpdateAndD0 )
{
    const auto x = funcy::Pow< 1 >( 2.0 );
    auto fun = funcy::min( 1.0, x );
    EXPECT_THAT( fun(), DoubleEq( 1.0 ) );
    fun.update( 0.5 );
    EXPECT_THAT( fun(), DoubleEq( 0.5 ) );
}

TEST( MinTest, RhsIsFunction_D1 )
{
    const auto x = funcy::Pow< 1 >( 2.0 );
    auto fun = funcy::min( 1.0, x );
    EXPECT_THAT( fun.d1< -1 >( 1.0 ), DoubleEq( 0.0 ) );
    EXPECT_THAT( fun.d1< -1 >( 2.0 ), DoubleEq( 0.0 ) );
    fun.update( 0.5 );
    EXPECT_THAT( fun.d1< -1 >( 1.0 ), DoubleEq( 1.0 ) );
    EXPECT_THAT( fun.d1< -1 >( 2.0 ), DoubleEq( 2.0 ) );
}

TEST( MinTest, LhsAndRhsAreFunction_UpdateAndD0 )
{
    const auto x = funcy::Pow< 1 >( 1.0 );
    const auto y = funcy::Pow< 2 >( 2.0 );
    auto fun = funcy::min( x, y );
    EXPECT_THAT( fun(), DoubleEq( 1.0 ) );
    fun.update( 0.5 );
    EXPECT_THAT( fun(), DoubleEq( 0.25 ) );
}

TEST( MinTest, LhsAndRhsAreFunction_D1 )
{
    const auto x = funcy::Pow< 1 >( 1.0 );
    const auto y = funcy::Pow< 2 >( 2.0 );
    auto fun = funcy::min( x, y );
    EXPECT_THAT( fun.d1< -1 >( 1.0 ), DoubleEq( 1.0 ) );
    EXPECT_THAT( fun.d1< -1 >( 2.0 ), DoubleEq( 2.0 ) );
    fun.update( 0.3 );
    EXPECT_THAT( fun.d1< -1 >( 1.0 ), DoubleEq( 0.6 ) );
    EXPECT_THAT( fun.d1< -1 >( 2.0 ), DoubleEq( 1.2 ) );
}

TEST( MinTest, LhsIsVariable_UpdateAndD0 )
{
    const auto x = funcy::variable< 0 >( 2.0 );
    const auto y = funcy::Pow< 2 >( 2.0 );
    auto fun = funcy::min( x, y );
    EXPECT_THAT( fun(), DoubleEq( 2.0 ) );
    fun.update( 1.0 );
    EXPECT_THAT( fun(), DoubleEq( 1.0 ) );
    fun.update< 0 >( 0.5 );
    EXPECT_THAT( fun(), DoubleEq( 0.5 ) );
}

TEST( MinTest, LhsIsVariable_D1 )
{
    const auto x = funcy::variable< 0 >( 2.0 );
    const auto y = funcy::Pow< 2 >( 2.0 );
    auto fun = funcy::min( x, y );
    EXPECT_THAT( fun.d1< 0 >( 1.0 ), DoubleEq( 1.0 ) );
    EXPECT_THAT( fun.d1< 0 >( 2.0 ), DoubleEq( 2.0 ) );
    fun.update( 0.3 );
    EXPECT_THAT( fun.d1< -1 >( 1.0 ), DoubleEq( 0.6 ) );
    EXPECT_THAT( fun.d1< -1 >( 2.0 ), DoubleEq( 1.2 ) );
    fun.update< 0 >( 0.01 );
    EXPECT_THAT( fun.d1< 0 >( 1.0 ), DoubleEq( 1.0 ) );
    EXPECT_THAT( fun.d1< 0 >( 2.0 ), DoubleEq( 2.0 ) );
}
