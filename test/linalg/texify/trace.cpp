#include <texy/linalg/trace.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Eq;
using texy::linalg::Trace;

TEST( TexifyTraceTest, D0 )
{
    const auto f = Trace( "B" );
    EXPECT_THAT( f(), Eq( "\\mathrm{tr}(B)" ) );
}

TEST( TexifyTraceTest, D1 )
{
    const auto f = Trace( "B" );
    EXPECT_THAT( f.d1( "dB" ), Eq( "\\mathrm{tr}(dB)" ) );
}
