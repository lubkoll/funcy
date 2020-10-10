#include <Eigen/Dense>
#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <tuple>

#define FUNCY_ENABLE_EXCEPTIONS
#include <funcy/linalg.h>

using testing::DoubleEq;

namespace
{
    using M2d = Eigen::Matrix< double, 2, 2 >;
    using M3d = Eigen::Matrix< double, 3, 3 >;
    using funcy::linalg::compute_cofactor;
    using funcy::linalg::compute_cofactor_directional_derivative;

    auto get_first_matrix_3d()
    {
        M3d m;
        m.fill( 0 );
        m( 0, 0 ) = 0;
        m( 0, 1 ) = 1;
        m( 0, 2 ) = 2;
        m( 1, 0 ) = 3;
        m( 1, 1 ) = 4;
        m( 1, 2 ) = 5;
        m( 2, 0 ) = 6;
        m( 2, 1 ) = 7;
        m( 2, 2 ) = 8;
        return m;
    }

    auto get_second_matrix_3d()
    {
        M3d m;
        m.fill( 0 );
        m( 0, 0 ) = 1;
        m( 1, 1 ) = 1;
        m( 2, 2 ) = 1;
        return m;
    }

    auto get_first_matrix_2d()
    {
        M2d m;
        m.fill( 0 );
        m( 0, 0 ) = 1;
        m( 0, 1 ) = 2;
        m( 1, 0 ) = 3;
        m( 1, 1 ) = 4;
        return m;
    }

    auto get_second_matrix_2d()
    {
        M2d m;
        m.fill( 0 );
        m( 0, 0 ) = 1;
        m( 1, 1 ) = 1;
        return m;
    }

    template < int i, int j >
    auto symmetric_derivative( const M2d& A, const M2d& B )
    {
        return compute_cofactor_directional_derivative< i, j >( A, B );
    }

    template < int i, int j >
    auto symmetric_derivative( const M3d& A, const M3d& B )
    {
        return compute_cofactor_directional_derivative< i, j >( A, B ) +
               compute_cofactor_directional_derivative< i, j >( B, A );
    }

} // namespace

TEST( CofactorTest_3d, D0 )
{
    const auto A = get_first_matrix_3d();

    auto value = compute_cofactor< 0, 0 >( A );
    EXPECT_THAT( value, DoubleEq( A( 1, 1 ) * A( 2, 2 ) - A( 1, 2 ) * A( 2, 1 ) ) );

    value = compute_cofactor< 0, 1 >( A );
    EXPECT_THAT( value, DoubleEq( -A( 1, 0 ) * A( 2, 2 ) + A( 2, 0 ) * A( 1, 2 ) ) );

    value = compute_cofactor< 0, 2 >( A );
    EXPECT_THAT( value, DoubleEq( A( 1, 0 ) * A( 2, 1 ) - A( 2, 0 ) * A( 1, 1 ) ) );

    value = compute_cofactor< 1, 0 >( A );
    EXPECT_THAT( value, DoubleEq( -A( 0, 1 ) * A( 2, 2 ) + A( 2, 1 ) * A( 0, 2 ) ) );

    value = compute_cofactor< 1, 1 >( A );
    EXPECT_THAT( value, DoubleEq( A( 0, 0 ) * A( 2, 2 ) - A( 2, 0 ) * A( 0, 2 ) ) );

    value = compute_cofactor< 1, 2 >( A );
    EXPECT_THAT( value, DoubleEq( -A( 0, 0 ) * A( 2, 1 ) + A( 2, 0 ) * A( 0, 1 ) ) );

    value = compute_cofactor< 2, 0 >( A );
    EXPECT_THAT( value, DoubleEq( A( 0, 1 ) * A( 1, 2 ) - A( 1, 1 ) * A( 0, 2 ) ) );

    value = compute_cofactor< 2, 1 >( A );
    EXPECT_THAT( value, DoubleEq( -A( 0, 0 ) * A( 1, 2 ) + A( 1, 0 ) * A( 0, 2 ) ) );

    value = compute_cofactor< 2, 2 >( A );
    EXPECT_THAT( value, DoubleEq( A( 0, 0 ) * A( 1, 1 ) - A( 1, 0 ) * A( 0, 1 ) ) );
}

TEST( CofactorTest_3d, D1 )
{
    const auto A = get_first_matrix_3d();
    const auto dA = get_second_matrix_3d();
    auto value = symmetric_derivative< 0, 0 >( A, dA );
    EXPECT_THAT( value, DoubleEq( A( 1, 1 ) + A( 2, 2 ) ) );

    value = symmetric_derivative< 0, 1 >( A, dA );
    EXPECT_THAT( value, DoubleEq( -A( 1, 0 ) ) );

    value = symmetric_derivative< 0, 2 >( A, dA );
    EXPECT_THAT( value, DoubleEq( -A( 2, 0 ) ) );

    value = symmetric_derivative< 1, 0 >( A, dA );
    EXPECT_THAT( value, DoubleEq( -A( 0, 1 ) ) );

    value = symmetric_derivative< 1, 1 >( A, dA );
    EXPECT_THAT( value, DoubleEq( A( 0, 0 ) + A( 2, 2 ) ) );

    value = symmetric_derivative< 1, 2 >( A, dA );
    EXPECT_THAT( value, DoubleEq( -A( 2, 1 ) ) );

    value = symmetric_derivative< 2, 0 >( A, dA );
    EXPECT_THAT( value, DoubleEq( -A( 0, 2 ) ) );

    value = symmetric_derivative< 2, 1 >( A, dA );
    EXPECT_THAT( value, DoubleEq( -A( 1, 2 ) ) );

    value = symmetric_derivative< 2, 2 >( A, dA );
    EXPECT_THAT( value, DoubleEq( A( 0, 0 ) + A( 1, 1 ) ) );
}

TEST( CofactorTest_2d, D0 )
{
    const auto A = get_first_matrix_2d();

    auto value = compute_cofactor< 0, 0 >( A );
    EXPECT_THAT( value, DoubleEq( A( 1, 1 ) ) );

    value = compute_cofactor< 0, 1 >( A );
    EXPECT_THAT( value, DoubleEq( -A( 1, 0 ) ) );

    value = compute_cofactor< 1, 0 >( A );
    EXPECT_THAT( value, DoubleEq( -A( 0, 1 ) ) );

    value = compute_cofactor< 1, 1 >( A );
    EXPECT_THAT( value, DoubleEq( A( 0, 0 ) ) );
}

TEST( CofactorTest_2d, D1 )
{
    const auto A = get_first_matrix_2d();
    const auto dA = get_second_matrix_2d();
    auto value = symmetric_derivative< 0, 0 >( A, dA );
    EXPECT_THAT( value, DoubleEq( dA( 1, 1 ) ) );

    value = symmetric_derivative< 0, 1 >( A, dA );
    EXPECT_THAT( value, DoubleEq( -dA( 1, 0 ) ) );

    value = symmetric_derivative< 1, 0 >( A, dA );
    EXPECT_THAT( value, DoubleEq( -dA( 0, 1 ) ) );

    value = symmetric_derivative< 1, 1 >( A, dA );
    EXPECT_THAT( value, DoubleEq( dA( 0, 0 ) ) );

    // value = symmetric_derivative< 0, 2 >( A, dA );
    // EXPECT_THAT( value, DoubleEq( -A( 2, 0 ) ) );

    // value = symmetric_derivative< 1, 0 >( A, dA );
    // EXPECT_THAT( value, DoubleEq( -A( 0, 1 ) ) );

    // value = symmetric_derivative< 1, 1 >( A, dA );
    // EXPECT_THAT( value, DoubleEq( A( 0, 0 ) + A( 2, 2 ) ) );

    // value = symmetric_derivative< 1, 2 >( A, dA );
    // EXPECT_THAT( value, DoubleEq( -A( 2, 1 ) ) );

    // value = symmetric_derivative< 2, 0 >( A, dA );
    // EXPECT_THAT( value, DoubleEq( -A( 0, 2 ) ) );

    // value = symmetric_derivative< 2, 1 >( A, dA );
    // EXPECT_THAT( value, DoubleEq( -A( 1, 2 ) ) );

    // value = symmetric_derivative< 2, 2 >( A, dA );
    // EXPECT_THAT( value, DoubleEq( A( 0, 0 ) + A( 1, 1 ) ) );
}
