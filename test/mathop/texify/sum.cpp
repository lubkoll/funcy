#include <funcy/finalize.h>
#include <funcy/generate.h>

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <texy/cmath/pow.h>

namespace
{
    using funcy::finalize;
    using ::testing::StrEq;
} // namespace

TEST( TexifySumTest, D0 )
{
    using texy::Pow;
    auto fun = Pow< 3, 1 >( "x" ) + Pow< 3, 2 >( "y" );
    EXPECT_THAT( fun.d0(), StrEq( "x^3 + y^{3/2}" ) );
}

TEST( TexifySumTest, D1 )
{
    using texy::Pow;
    auto fun = finalize( Pow< 3, 1 >( "x" ) + Pow< 3, 2 >( "y" ) );
    EXPECT_THAT( fun.d1( "" ), StrEq( "3x^2 + 3/2*y^{1/2}" ) );
}

TEST( TexifySumTest, D2 )
{
    using texy::Pow;
    auto fun = finalize( Pow< 3, 1 >( "x" ) + Pow< 3, 2 >( "y" ) );
    EXPECT_THAT( fun.d2( "", "" ), StrEq( "6x + 3/4*y^{-1/2}" ) );
}

TEST( TexifySumTest, D3 )
{
    using texy::Pow;
    auto fun = finalize( Pow< 3, 1 >( "x" ) + Pow< 3, 2 >( "y" ) );
    EXPECT_THAT( fun.d3( "", "", "" ), StrEq( "6 + -3/8*y^{-3/2}" ) );
}
