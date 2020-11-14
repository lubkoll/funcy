#include <funcy/cmath/pow.h>
#include <funcy/cmath/sine.h>
#include <funcy/finalize.h>
#include <funcy/generate.h>
#include <funcy/variable.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;

namespace
{
    auto generateTestFunction()
    {
        using namespace funcy;
        auto f = ( variable< 0 >( 1. ) + variable< 1 >( 2. ) ) * pow< 2 >( variable< 2 >( 3. ) );
        return finalize( f );
    }
} // namespace

TEST( HasVariableTest, Sum )
{
    using namespace funcy;
    const auto f = finalize( variable< 0 >( 1. ) + 1 );
    EXPECT_TRUE( static_check::has::variable< decltype( f ) >() );
    const auto g = finalize( 1 + variable< 0 >( 1. ) );
    EXPECT_TRUE( static_check::has::variable< decltype( g ) >() );
    const auto h = finalize( variable< 0 >( 1. ) + variable< 1 >( 2 ) );
    EXPECT_TRUE( static_check::has::variable< decltype( h ) >() );
    const auto k = Pow< 2, 1 >() + variable< 1 >( 1 );
    EXPECT_TRUE( static_check::has::variable< decltype( k ) >() );
}

TEST( HasVariableTest, Scale )
{
    using namespace funcy;
    const auto f = finalize( variable< 0 >( 1. ) * 2 );
    EXPECT_TRUE( static_check::has::variable< decltype( f ) >() );
    const auto g = finalize( 2 * variable< 0 >( 1. ) );
    EXPECT_TRUE( static_check::has::variable< decltype( g ) >() );
}

TEST( HasVariableTest, Multiply )
{
    using namespace funcy;
    const auto f = finalize( variable< 0 >( 1. ) * variable< 1 >( 2. ) );
    EXPECT_TRUE( static_check::has::variable< decltype( f ) >() );
    const auto g = finalize( funcy::Sin( 1 ) * variable< 0 >( 1. ) );
    EXPECT_TRUE( static_check::has::variable< decltype( g ) >() );
}

TEST( HasVariableTest, Squared )
{
    using namespace funcy;
    auto f = finalize( squared( variable< 0 >( 1. ) ) );
    EXPECT_TRUE( static_check::has::variable< decltype( f ) >() );
}

TEST( VariableTypeTest, IF_applied_to_variable_THEN_RETURNS_its_type )
{
    using G = funcy::Variable< double, 1 >;
    const auto result = std::is_same< funcy::Variable_t< G, 1 >, double >::value;
    EXPECT_TRUE( result );
}

TEST( VariableTypeTest, IF_applied_to_const_variable_THEN_RETURNS_its_type )
{
    using G = const funcy::Variable< double, 1 >;
    const auto result = std::is_same< funcy::Variable_t< G, 1 >, double >::value;
    EXPECT_TRUE( result );
}

TEST( HasVariableIdTest, Sum )
{
    using namespace funcy;
    const auto f = finalize( variable< 0 >( 1. ) + 1 );
    auto result = static_check::has::variable_id< decltype( f ), 0 >();
    EXPECT_TRUE( result );
    result = static_check::has::variable_id< decltype( f ), 1 >();
    EXPECT_FALSE( result );
    const auto g = finalize( 1 + variable< 0 >( 1. ) );
    result = static_check::has::variable_id< decltype( g ), 0 >();
    EXPECT_TRUE( result );
    result = static_check::has::variable_id< decltype( g ), 1 >();
    EXPECT_FALSE( result );
    const auto h = finalize( variable< 0 >( 1. ) + variable< 1 >( 2 ) );
    result = static_check::has::variable_id< decltype( h ), 0 >();
    EXPECT_TRUE( result );
    result = static_check::has::variable_id< decltype( h ), 1 >();
    EXPECT_TRUE( result );
    const auto k = Pow< 2, 1 >() + variable< 1 >( 1 );
    result = static_check::has::variable_id< decltype( k ), 0 >();
    EXPECT_FALSE( result );
    result = static_check::has::variable_id< decltype( k ), 1 >();
    EXPECT_TRUE( result );
}

TEST( HasVariableIdTest, Scale )
{
    using namespace funcy;
    const auto f = finalize( variable< 0 >( 1. ) * 2 );
    auto result = static_check::has::variable_id< decltype( f ), 0 >();
    EXPECT_TRUE( result );
    result = static_check::has::variable_id< decltype( f ), 1 >();
    EXPECT_FALSE( result );
    const auto g = finalize( 2 * variable< 0 >( 1. ) );
    result = static_check::has::variable_id< decltype( g ), 0 >();
    EXPECT_TRUE( result );
    result = static_check::has::variable_id< decltype( g ), 1 >();
    EXPECT_FALSE( result );
}

TEST( HasVariableIdTest, Multiply )
{
    using namespace funcy;
    const auto f = finalize( variable< 0 >( 1. ) * variable< 1 >( 2. ) );
    auto result = static_check::has::variable_id< decltype( f ), 0 >();
    EXPECT_TRUE( result );
    result = static_check::has::variable_id< decltype( f ), 1 >();
    EXPECT_TRUE( result );
    const auto g = finalize( funcy::Sin( 1 ) * variable< 0 >( 1. ) );
    result = static_check::has::variable_id< decltype( g ), 0 >();
    EXPECT_TRUE( result );
    result = static_check::has::variable_id< decltype( g ), 1 >();
    EXPECT_FALSE( result );
}

TEST( HasVariableIdTest, Squared )
{
    using namespace funcy;
    const auto f = finalize( squared( variable< 0 >( 1. ) ) );
    auto result = static_check::has::variable_id< decltype( f ), 0 >();
    EXPECT_TRUE( result );
    result = static_check::has::variable_id< decltype( f ), 1 >();
    EXPECT_FALSE( result );
}

TEST( VariableTest, D0 )
{
    auto fun = generateTestFunction();
    EXPECT_DOUBLE_EQ( fun.d0(), 27. );
}

TEST( VariableTest, D1 )
{
    auto fun = generateTestFunction();
    EXPECT_DOUBLE_EQ( fun.d1< 0 >(), 9. );
    EXPECT_DOUBLE_EQ( fun.d1< 1 >(), 9. );
    EXPECT_DOUBLE_EQ( fun.d1< 2 >(), 18. );
}

TEST( VariableTest, D2 )
{
    auto fun = generateTestFunction();
    auto val = fun.d2< 0, 0 >();
    EXPECT_DOUBLE_EQ( val, 0. );
    val = fun.d2< 1, 1 >();
    EXPECT_DOUBLE_EQ( val, 0. );
    val = fun.d2< 2, 2 >();
    EXPECT_DOUBLE_EQ( val, 6. );
    val = fun.d2< 0, 1 >();
    EXPECT_DOUBLE_EQ( val, 0. );
    auto val2 = fun.d2< 1, 0 >();
    EXPECT_DOUBLE_EQ( val, val2 );
    val = fun.d2< 0, 2 >();
    EXPECT_DOUBLE_EQ( val, 6. );
    val2 = fun.d2< 2, 0 >();
    EXPECT_DOUBLE_EQ( val, val2 );
    val = fun.d2< 1, 2 >();
    EXPECT_DOUBLE_EQ( val, 6. );
    val2 = fun.d2< 2, 1 >();
    EXPECT_DOUBLE_EQ( val, val2 );
}

TEST( MaxVariableIdTest, IF_applied_to_variable_THEN_RETURNS_its_id )
{
    using namespace funcy;
    auto f = variable< 1 >( 1 );
    EXPECT_THAT( detail::MaxVariableId< decltype( f ) >::value, Eq( 1 ) );
}

TEST( MaxVariableIdTest, IF_applied_to_const_variable_THEN_RETURNS_its_id )
{
    using namespace funcy;
    const auto f = variable< 1 >( 1 );
    EXPECT_THAT( detail::MaxVariableId< decltype( f ) >::value, Eq( 1 ) );
}

TEST( MinVariableIdTest, IF_applied_to_variable_THEN_RETURNS_its_id )
{
    using namespace funcy;
    auto f = variable< 1 >( 1 );
    EXPECT_THAT( detail::MinVariableId< decltype( f ) >::value, Eq( 1 ) );
}

TEST( MinVariableIdTest, IF_applied_to_const_variable_THEN_RETURNS_its_id )
{
    using namespace funcy;
    const auto f = variable< 1 >( 1 );
    EXPECT_THAT( detail::MinVariableId< decltype( f ) >::value, Eq( 1 ) );
}

TEST( MaxVariableIdTest, IF_noVariablesInSum_THEN_RETURNS_lowest_int )
{
    using namespace funcy;
    auto f = finalize( Pow< 1, 2 >() + Pow< 2, 1 >() );
    EXPECT_THAT( detail::MaxVariableId< decltype( f ) >::value,
                 Eq( std::numeric_limits< int >::lowest() ) );
}

TEST( MinVariableIdTest, IF_noVariablesInSum_THEN_RETURNS_max_int )
{
    using namespace funcy;
    auto f = finalize( Pow< 1, 2 >() + Pow< 2, 1 >() );
    EXPECT_THAT( detail::MinVariableId< decltype( f ) >::value,
                 Eq( std::numeric_limits< int >::max() ) );
}

TEST( MaxVariableIdTest, IF_oneVariableInSum_THEN_RETURNS_its_id )
{
    using namespace funcy;
    auto f = finalize( Pow< 2, 1 >() + variable< 1 >( 1 ) );
    EXPECT_THAT( detail::MaxVariableId< decltype( f ) >::value, Eq( 1 ) );
}

TEST( MinVariableIdTest, IF_oneVariableInSum_THEN_RETURNS_its_id )
{
    using namespace funcy;
    auto f = Pow< 2, 1 >() + variable< 1 >( 1 );
    EXPECT_THAT( detail::MinVariableId< decltype( f ) >::value, Eq( 1 ) );
}

TEST( MaxVariableIdTest, IF_twoVariablesInSum_THEN_RETURNS_the_bigger_id )
{
    using namespace funcy;
    auto f = variable< -3 >( 1 ) + variable< 2 >( 1 );
    EXPECT_THAT( detail::MaxVariableId< decltype( f ) >::value, Eq( 2 ) );
}

TEST( MinVariableIdTest, IF_twoVariablesInSum_THEN_RETURNS_the_smaller_id )
{
    using namespace funcy;
    auto f = variable< -3 >( 1 ) + variable< 2 >( 1 );
    EXPECT_THAT( detail::MinVariableId< decltype( f ) >::value, Eq( -3 ) );
}

TEST( MaxVariableIdTest, IF_noVariablesInScale_THEN_RETURNS_lowest_int )
{
    using namespace funcy;
    auto f = finalize( 2 * Pow< 2, 1 >() );
    EXPECT_THAT( detail::MaxVariableId< decltype( f ) >::value,
                 Eq( std::numeric_limits< int >::lowest() ) );
}

TEST( MinVariableIdTest, IF_noVariablesInScale_THEN_RETURNS_max_int )
{
    using namespace funcy;
    auto f = finalize( 2 * Pow< 2, 1 >() );
    EXPECT_THAT( detail::MinVariableId< decltype( f ) >::value,
                 Eq( std::numeric_limits< int >::max() ) );
}

TEST( MaxVariableIdTest, IF_oneVariableInScale_THEN_RETURNS_its_id )
{
    using namespace funcy;
    auto f = 2 * variable< 1 >( 1 );
    EXPECT_THAT( detail::MaxVariableId< decltype( f ) >::value, Eq( 1 ) );
}

TEST( MinVariableIdTest, IF_oneVariableInScale_THEN_RETURNS_its_id )
{
    using namespace funcy;
    auto f = 2 * variable< 1 >( 1 );
    EXPECT_THAT( detail::MinVariableId< decltype( f ) >::value, Eq( 1 ) );
}

TEST( VariableT, Variable )
{
    using namespace funcy;
    using F = decltype( variable< 0 >( 1. ) );
    using VT = Variable_t< F, 0 >;
    const auto correct_type = std::is_same< VT, double >::value;
    EXPECT_TRUE( correct_type );
}

TEST( VariableT, Squared )
{
    using namespace funcy;
    using F = decltype( squared( variable< 0 >( 1. ) ) );
    using VT = Variable_t< F, 0 >;
    const auto correct_type = std::is_same< VT, double >::value;
    EXPECT_TRUE( correct_type );
}

TEST( VariableT, FinalizeSquared )
{
    using namespace funcy;
    using F = decltype( finalize( squared( variable< 0 >( 1. ) ) ) );
    using VT = Variable_t< F, 0 >;
    const auto correct_type = std::is_same< VT, double >::value;
    EXPECT_TRUE( correct_type );
}

TEST( CheckArgumentTest, Squared )
{
    using namespace funcy;
    using F = decltype( squared( variable< 0 >( 1. ) ) );
    const auto value = static_check::check_argument< F, double, 0 >();
    EXPECT_TRUE( value );
}

TEST( CheckArgumentTest, FinalizeSquared )
{
    using namespace funcy;
    using F = decltype( finalize( squared( variable< 0 >( 1. ) ) ) );
    const auto value = static_check::check_argument< F, double, 0 >();
    EXPECT_TRUE( value );
}

TEST( CheckArgumentTest, FinalizeScale )
{
    using namespace funcy;
    using F = decltype( finalize( 2.0 * variable< 0 >( 1. ) ) );
    const auto value = static_check::check_argument< F, double, 0 >();
    EXPECT_TRUE( value );
}

TEST( CheckArgumentTest, FinalizeSumSquared )
{
    using namespace funcy;
    using F = decltype( finalize( squared( variable< 0 >( 1. ) ) +
                                  2.0 * squared( variable< 1 >( 1. ) ) ) );
    const auto value = static_check::check_argument< F, double, 1 >();
    EXPECT_TRUE( value );
}

TEST( CheckArgumentTest, FinalizeTrackingType )
{
    using namespace funcy;
    using F = decltype( finalize( squared( variable< 0 >( 1.0 ) - variable< 4 >( 1.0 ) ) +
                                  2.0 * squared( variable< 1 >( 1.0 ) ) ) );
    const auto value = static_check::check_argument< F, double, 1 >();
    EXPECT_TRUE( value );
}

TEST( VariableTest, D3 )
{
    auto fun = generateTestFunction();
    auto val = fun.d3< 0, 0, 0 >();
    EXPECT_DOUBLE_EQ( val, 0. );
    val = fun.d3< 1, 1, 1 >();
    EXPECT_DOUBLE_EQ( val, 0. );
    val = fun.d3< 2, 2, 2 >();
    EXPECT_DOUBLE_EQ( val, 0. );
    val = fun.d3< 0, 2, 2 >();
    EXPECT_DOUBLE_EQ( val, 2. );
    auto val2 = fun.d3< 2, 0, 2 >();
    EXPECT_DOUBLE_EQ( val, val2 );
    val2 = fun.d3< 2, 2, 0 >();
    EXPECT_DOUBLE_EQ( val, val2 );
    val = fun.d3< 0, 1, 2 >();
    EXPECT_DOUBLE_EQ( val, 0. );
    val2 = fun.d3< 2, 1, 0 >();
    EXPECT_DOUBLE_EQ( val, val2 );
    val = fun.d3< 0, 2, 1 >();
    EXPECT_DOUBLE_EQ( val, 0. );
    val2 = fun.d3< 1, 2, 0 >();
    EXPECT_DOUBLE_EQ( val, val2 );
    val = fun.d3< 2, 1, 0 >();
    EXPECT_DOUBLE_EQ( val, val2 );
}
