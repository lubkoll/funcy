#include <funcy/cmath/pow.h>
#include <funcy/constant.h>
#include <funcy/generate.h>

#include <gtest/gtest.h>

#include <gmock/gmock.h>

namespace
{
    using testing::DoubleEq;
}

TEST( Division, WithPowMinusTwo )
{
    using funcy::Pow;
    auto f = 1 / Pow< 2 >( 2 );
    EXPECT_THAT( f(), DoubleEq( 0.25 ) );
    f.update( 0.5 );
    EXPECT_THAT( f(), DoubleEq( 4 ) );
    EXPECT_THAT( f.d1< -1 >( 1.0 ), DoubleEq( -16 ) );
}

TEST( Division, WithConstantTwo )
{
    using funcy::constant;
    auto f = 1 / constant( 2 );
    EXPECT_THAT( f(), DoubleEq( 0.5 ) );
}
