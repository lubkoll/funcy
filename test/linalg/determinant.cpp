#include <Eigen/Dense>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <tuple>

#define FUNCY_ENABLE_EXCEPTIONS
#include <funcy/linalg.h>

using funcy::linalg::det;

using testing::DoubleEq;

namespace
{
    using M2d = Eigen::Matrix< double, 2, 2 >;
    using M3d = Eigen::Matrix< double, 3, 3 >;
    using MXd = Eigen::MatrixXd;

    auto get_first_matrix_2d()
    {
        M2d m;
        m.fill( 0 );
        m( 0, 0 ) = 0;
        m( 0, 1 ) = 1;
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
        m( 2, 2 ) = 1;
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

    auto get_first_matrix_x2d()
    {
        MXd m( 2, 2 );
        m << 0, 1, 3, 4;
        return m;
    }

    auto get_second_matrix_x2d()
    {
        MXd m( 2, 2 );
        m << 1, 0, 0, 1;
        return m;
    }

    auto get_first_matrix_x3d()
    {
        MXd m( 3, 3 );
        m.fill( 0 );
        m( 0, 0 ) = 0;
        m( 0, 1 ) = 1;
        m( 0, 2 ) = 2;
        m( 1, 0 ) = 3;
        m( 1, 1 ) = 4;
        m( 1, 2 ) = 5;
        m( 2, 0 ) = 6;
        m( 2, 1 ) = 7;
        m( 2, 2 ) = 1;
        return m;
    }

    auto get_second_matrix_x3d()
    {
        MXd m( 3, 3 );
        m.fill( 0 );
        m( 0, 0 ) = 1;
        m( 1, 1 ) = 1;
        m( 2, 2 ) = 1;
        return m;
    }
} // namespace

TEST( StaticDeterminantTest_2d, D0 )
{
    const auto d = det( get_first_matrix_2d() );
    EXPECT_THAT( d(), DoubleEq( -3 ) );
}

TEST( StaticDeterminantTest_2d, D1 )
{
    using funcy::linalg::compute_cofactor;
    const auto d = det( get_first_matrix_2d() );
    EXPECT_THAT( d.d1( get_second_matrix_2d() ), DoubleEq( 4 ) );
    const auto c = compute_cofactor< 0, 0 >( get_first_matrix_2d() ) +
                   compute_cofactor< 1, 1 >( get_first_matrix_2d() );
    EXPECT_THAT( d.d1( get_second_matrix_2d() ), DoubleEq( c ) );
}

TEST( StaticDeterminantTest_2d, D2 )
{
    const auto d = det( get_first_matrix_2d() );
    EXPECT_THAT( d.d2( get_second_matrix_2d(), get_second_matrix_2d() ), DoubleEq( 2 ) );
}

TEST( StaticDeterminantTest_3d, D0 )
{
    const auto d = det( get_first_matrix_3d() );
    EXPECT_THAT( d(), DoubleEq( 21 ) );
}

TEST( StaticDeterminantTest_3d, D1 )
{
    using funcy::linalg::compute_cofactor;
    const auto d = det( get_first_matrix_3d() );
    EXPECT_THAT( d.d1( get_second_matrix_3d() ), DoubleEq( -46 ) );
    const auto c = compute_cofactor< 0, 0 >( get_first_matrix_3d() ) +
                   compute_cofactor< 1, 1 >( get_first_matrix_3d() ) +
                   compute_cofactor< 2, 2 >( get_first_matrix_3d() );
    EXPECT_THAT( d.d1( get_second_matrix_3d() ), DoubleEq( c ) );
}

TEST( StaticDeterminantTest_3d, D2 )
{
    auto d = det( get_first_matrix_3d() );
    EXPECT_THAT( d.d2( get_second_matrix_3d(), get_second_matrix_3d() ), DoubleEq( 10 ) );
}

TEST( StaticDeterminantTest_3d, D3 )
{
    auto d = det( get_first_matrix_3d() );
    EXPECT_THAT( d.d3( get_second_matrix_3d(), get_second_matrix_3d(), get_second_matrix_3d() ),
                 DoubleEq( 6 ) );
}

TEST( DynamicDeterminantTest_2d, D0 )
{
    const auto d = det( get_first_matrix_x2d() );
    EXPECT_THAT( d(), DoubleEq( -3 ) );
}

TEST( DynamicDeterminantTest_2d, D1 )
{
    using funcy::linalg::compute_cofactor;
    const auto d = det( get_first_matrix_x2d() );
    EXPECT_THAT( d.d1( get_second_matrix_x2d() ), DoubleEq( 4 ) );
    const auto c = compute_cofactor< 0, 0 >( get_first_matrix_x2d() ) +
                   compute_cofactor< 1, 1 >( get_first_matrix_x2d() );
    EXPECT_THAT( d.d1( get_second_matrix_x2d() ), DoubleEq( c ) );
}

TEST( DynamicDeterminantTest_2d, D2 )
{
    const auto d = det( get_first_matrix_x2d() );
    EXPECT_THAT( d.d2( get_second_matrix_x2d(), get_second_matrix_x2d() ), DoubleEq( 2 ) );
}

TEST( DynamicDeterminantTest_3d, D0 )
{
    const auto d = det( get_first_matrix_x3d() );
    EXPECT_THAT( d(), DoubleEq( 21 ) );
}

TEST( DynamicDeterminantTest_3d, D1 )
{
    using funcy::linalg::compute_cofactor;
    const auto d = det( get_first_matrix_x3d() );
    EXPECT_THAT( d.d1( get_second_matrix_x3d() ), DoubleEq( -46 ) );
    const auto c = compute_cofactor< 0, 0 >( get_first_matrix_x3d() ) +
                   compute_cofactor< 1, 1 >( get_first_matrix_x3d() ) +
                   compute_cofactor< 2, 2 >( get_first_matrix_x3d() );
    EXPECT_THAT( d.d1( get_second_matrix_x3d() ), DoubleEq( c ) );
}

TEST( DynamicDeterminantTest_3d, D2 )
{
    auto d = det( get_first_matrix_x3d() );
    EXPECT_THAT( d.d2( get_second_matrix_x3d(), get_second_matrix_x3d() ), DoubleEq( 10 ) );
}

TEST( DynamicDeterminantTest_3d, D3 )
{
    auto d = det( get_first_matrix_x3d() );
    EXPECT_THAT( d.d3( get_second_matrix_x3d(), get_second_matrix_x3d(), get_second_matrix_x3d() ),
                 DoubleEq( 6 ) );
}

TEST( DynamicDeterminantTest_3d, NonSymmetricDynamicMatrixThrows )
{
    using M = Eigen::MatrixXd;
    auto m = M( 3, 2 );
    m << 1, 2, 3, 4, 5, 6;

    EXPECT_THROW( auto t = det( m ), funcy::NonSymmetricMatrixException );
}
