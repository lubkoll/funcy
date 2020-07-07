#include <funcy/finalize.h>
#include <funcy/generate.h>

#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <texy/cmath/pow.h>

namespace
{
    using funcy::finalize;
    using funcy::squared;
    using ::testing::StrEq;
} // namespace

TEST( TexifySquaredTest, D0 )
{
    using texy::Pow;
    auto f = squared( Pow< 2 >() );
    EXPECT_THAT( f.d0(), StrEq( "x^2*x^2" ) );
}

TEST( TexifySquaredTest, D1 )
{
    using texy::Pow;
    auto f = finalize( squared( Pow< 2 >() ) );
    EXPECT_THAT( f.d1( "" ), StrEq( "2*x^2*2x" ) );
}
