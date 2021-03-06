#include <funcy/cmath/pow.h>
#include <funcy/finalize.h>
#include <funcy/generate.h>
#include <funcy/variable.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::StrEq;

TEST( SquaredTest, Update )
{
    auto fun = squared( funcy::Pow< 2 >( 2. ) );
    EXPECT_NO_THROW( fun.update( -2 ) );
    EXPECT_DOUBLE_EQ( fun.d0(), 16. );
}

TEST( SquaredTest, UpdateVariable )
{
    auto x = funcy::variable< 0 >( 2. );
    auto fun = squared( funcy::Pow< 2, 1 >()( x ) );
    EXPECT_DOUBLE_EQ( fun.d0(), 16. );
    EXPECT_NO_THROW( fun.update< 0 >( -1. ) );
    EXPECT_NO_THROW( fun.update( 0 ); );
    EXPECT_DOUBLE_EQ( fun.d0(), 1. );
}

TEST( SquaredTest, D0 )
{
    using funcy::Pow;
    auto fun = squared( Pow< 2 >( 2. ) );
    EXPECT_DOUBLE_EQ( fun.d0(), 16. );
}

// TEST( StringifySquaredTest, D0 )
//{
//    using stringy::Pow;
//    auto f = squared( Pow< 2 >() );
//    EXPECT_THAT( f.d0(), StrEq( "x^2*x^2" ) );
//}

TEST( SquaredTest, D1 )
{
    using funcy::Pow;
    auto fun = funcy::finalize( squared( Pow< 2 >( 2. ) ) );
    EXPECT_DOUBLE_EQ( fun.d1( 1 ), 32. );
}

// TEST( StringifySquaredTest, D1 )
//{
//    using stringy::Pow;
//    auto f = funcy::finalize( squared( Pow< 2 >() ) );
//    EXPECT_THAT( f.d1( "" ), StrEq( "2*x^2*2x" ) );
//}

TEST( SquaredTest, D2 )
{
    using funcy::Pow;
    auto fun = funcy::finalize( squared( Pow< 2 >( 2. ) ) );
    EXPECT_DOUBLE_EQ( fun.d2( 1, 1 ), 48. );
}

// TEST( StringifySquaredTest, D2 )
//{
//    using stringy::Pow;
//    auto f = funcy::finalize( squared( Pow< 2 >() ) );
//    EXPECT_THAT( f.d2( "", "" ), StrEq( "2*(x^2*2 + 2x*2x)" ) );
//}

TEST( SquaredTest, D3 )
{
    using funcy::Pow;
    auto fun = funcy::finalize( squared( Pow< 2 >( 2. ) ) );
    EXPECT_DOUBLE_EQ( fun.d3( 1, 1, 1 ), 48. );
}

// TEST( StringifySquaredTest, D3 )
//{
//    using stringy::Pow;
//    auto f = funcy::finalize( squared( Pow< 2 >() ) );
//    EXPECT_THAT( f.d3( "", "", "" ), StrEq( "2*(2x*2 + 2x*2 + 2*2x)" ) );
//}
