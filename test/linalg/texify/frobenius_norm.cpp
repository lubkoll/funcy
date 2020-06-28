#include <funcy/finalize.h>
#include <texy/linalg/frobenius_norm.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq;
using texy::linalg::FrobeniusNorm;

TEST( TexifyFrobeniusNormTest, D0 )
{
    const auto f = FrobeniusNorm( "B" );
    EXPECT_THAT( f(), Eq( "(\\sum_{i,j}B_{ij}^2)^{1/2}" ) );
}

TEST( TexifyFrobeniusNormTest, D1 )
{
    const auto f = funcy::finalize( FrobeniusNorm( "C" ) );
    EXPECT_THAT( f.d1( "dA" ),
                 Eq( "1/2*(\\sum_{i,j}C_{ij}^2)^{-1/2}*2\\sum_{i,j}(C_{ij}*dA_{ij})" ) );
}
