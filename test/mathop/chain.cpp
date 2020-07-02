#include <funcy/cmath/pow.h>
#include <funcy/finalize.h>
#include <funcy/generate.h>

#include <gtest/gtest.h>

TEST( ChainTest, UpdateVariable )
{
    using funcy::Pow;
    auto fun = Pow< 1, 4 >( 1. )( Pow< 2 >( 1. ) );
    EXPECT_DOUBLE_EQ( fun.d0(), 1. );
    EXPECT_NO_THROW( fun.update< 0 >( 9. ) );
    EXPECT_NO_THROW( fun.update( 4 ); );
    EXPECT_DOUBLE_EQ( fun.d0(), 2. );
}

TEST( ChainTest, D0 )
{
    using funcy::Pow;
    auto fun = Pow< 1, 4 >( 1. )( Pow< 2 >( 1. ) );
    EXPECT_DOUBLE_EQ( fun.d0(), 1. );
    fun.update( 9. );
    EXPECT_DOUBLE_EQ( fun.d0(), 3. );
}

TEST( ChainTest, D1 )
{
    using funcy::Pow;
    auto fun = Pow< 1, 4 >( 1. )( Pow< 2 >( 16. ) );
    EXPECT_DOUBLE_EQ( fun.d1< -1 >( 1. ), 1. / 8 );
}

TEST( ChainTest, D2 )
{
    using funcy::Pow;
    auto fun = funcy::finalize( Pow< 1, 4 >( 1. )( Pow< 2 >( 4. ) ) );
    auto val = -0.25 * Pow< -3, 2 >( 4. )();
    EXPECT_DOUBLE_EQ( fun.d2( 1, 1 ), val );
}

TEST( ChainTest, D3 )
{
    using funcy::Pow;
    auto fun = funcy::finalize( Pow< 1, 4 >( 1. )( Pow< 2 >( 4. ) ) );
    auto val = 3. / 8 * Pow< -5, 2 >( 4. )();
    EXPECT_DOUBLE_EQ( fun.d3( 1, 1, 1 ), val );
}
