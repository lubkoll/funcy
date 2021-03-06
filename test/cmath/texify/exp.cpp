#include <texy/cmath/exp.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq;
using texy::Exp;

TEST( TexifyExpTest, D0 )
{
    const auto fun = Exp();
    EXPECT_THAT( fun.d0(), Eq( "e^{x}" ) );
}

TEST( TexifyExpTest, D1 )
{
    const auto fun = Exp();
    EXPECT_THAT( fun.d1( "dx" ), Eq( "e^{x}*dx" ) );
}

TEST( TexifyExpTest, D2 )
{
    const auto fun = Exp();
    EXPECT_THAT( fun.d2( "dx", "dy" ), Eq( "e^{x}*dx*dy" ) );
}

TEST( TexifyExpTest, D3 )
{
    const auto fun = Exp();
    EXPECT_THAT( fun.d3( "dx", "dy", "dz" ), Eq( "e^{x}*dx*dy*dz" ) );
}
