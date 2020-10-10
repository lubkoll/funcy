#define FUNCY_ENABLE_EXCEPTIONS
#include <funcy/cmath/arccos.h>

#include <gtest/gtest.h>

namespace
{
    auto x0()
    {
        return 0.5;
    }

    auto condition()
    {
        return 1e1;
    }
} // namespace

TEST( ArccosTest, Update )
{
    auto fun = funcy::ACos( x0() );
    ASSERT_THROW( fun.update( -1.1 ), funcy::OutOfDomainException );
    ASSERT_THROW( fun.update( 1.1 ), funcy::OutOfDomainException );
}

TEST( ArccosTest, D0 )
{
    auto fun = funcy::ACos( x0() );
    EXPECT_DOUBLE_EQ( fun(), acos( .5 ) );
}

TEST( ArccosTest, D1 )
{
    auto fun = funcy::ACos( x0() );
    double dx = 2.;
    EXPECT_DOUBLE_EQ( fun.d1(), -1 / sqrt( 0.75 ) );
    EXPECT_DOUBLE_EQ( fun.d1( dx ), -1 / sqrt( 0.75 ) * dx );
}

TEST( ArccosTest, D1DifferentialQuotient )
{
    auto fun = funcy::ACos( x0() );
    auto dx = 1e-8;
    auto f0 = fun();
    fun.update( x0() + dx );
    EXPECT_NEAR( fun.d1(), ( fun() - f0 ) / dx, dx * condition() );
}

TEST( ArccosTest, D2 )
{
    auto fun = funcy::ACos( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    EXPECT_DOUBLE_EQ( fun.d2(), -.5 / pow( sqrt( 0.75 ), 3 ) );
    EXPECT_DOUBLE_EQ( fun.d2( dx, dy ), -.5 / pow( sqrt( 0.75 ), 3 ) * dx * dy );
}

TEST( ArccosTest, D3 )
{
    auto fun = funcy::ACos( x0() );
    const auto dx = 2.0;
    const auto dy = 3.0;
    const auto dz = 4.0;
    EXPECT_DOUBLE_EQ( fun.d3(), -1 / sqrt( pow( 0.75, 3 ) ) * ( 1 + 0.75 * 0.75 ) );
    EXPECT_DOUBLE_EQ( fun.d3( dx, dy, dz ),
                      -1 / sqrt( pow( 0.75, 3 ) ) * ( 1 + 0.75 * 0.75 ) * dx * dy * dz );
}

TEST( ArccosTest, OutOfDomainException )
{
    auto fun = funcy::ACos( x0() );
    EXPECT_THROW( fun.update( -2 ), funcy::OutOfDomainException );
}
