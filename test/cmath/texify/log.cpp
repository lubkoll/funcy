#include <texy/cmath/log.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq;
using texy::LN;
using texy::Log10;
using texy::Log2;

TEST( TexifyLNTest, D0 )
{
    const auto fun = LN();
    EXPECT_THAT( fun.d0(), Eq( "\\ln(x)" ) );
}

TEST( TexifyLNTest, D1 )
{
    const auto fun = LN();
    EXPECT_THAT( fun.d1( "dx" ), Eq( "x^{-1}*dx" ) );
}

TEST( TexifyLNTest, D2 )
{
    const auto fun = LN();
    EXPECT_THAT( fun.d2( "dx", "dy" ), Eq( "-(x^{-2})*dx*dy" ) );
}

TEST( TexifyLNTest, D3 )
{
    const auto fun = LN();
    EXPECT_THAT( fun.d3( "dx", "dy", "dz" ), Eq( "2(x^{-3})*dx*dy*dz" ) );
}

TEST( TexifyLog10Test, D0 )
{
    const auto fun = Log10();
    EXPECT_THAT( fun.d0(), Eq( "\\log_10(x)" ) );
}

TEST( TexifyLog10Test, D1 )
{
    const auto fun = Log10();
    EXPECT_THAT( fun.d1( "dx" ), Eq( "(\\ln(10)*x)^{-1}*dx" ) );
}

TEST( TexifyLog10Test, D2 )
{
    const auto fun = Log10();
    EXPECT_THAT( fun.d2( "dx", "dy" ), Eq( "-\\ln(10)^{-1}x^{-2}*dx*dy" ) );
}

TEST( TexifyLog10Test, D3 )
{
    const auto fun = Log10();
    EXPECT_THAT( fun.d3( "dx", "dy", "dz" ), Eq( "2\\ln(10)^{-1}x^{-3}*dx*dy*dz" ) );
}

TEST( TexifyLog2Test, D0 )
{
    const auto fun = Log2();
    EXPECT_THAT( fun.d0(), Eq( "\\log_2(x)" ) );
}

TEST( TexifyLog2Test, D1 )
{
    const auto fun = Log2();
    EXPECT_THAT( fun.d1( "dx" ), Eq( "(\\ln(2)*x)^{-1}*dx" ) );
}

TEST( TexifyLog2Test, D2 )
{
    const auto fun = Log2();
    EXPECT_THAT( fun.d2( "dx", "dy" ), Eq( "-\\ln(2)^{-1}x^{-2}*dx*dy" ) );
}

TEST( TexifyLog2Test, D3 )
{
    const auto fun = Log2();
    EXPECT_THAT( fun.d3( "dx", "dy", "dz" ), Eq( "2\\ln(2)^{-1}x^{-3}*dx*dy*dz" ) );
}
