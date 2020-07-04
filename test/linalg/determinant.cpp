#include <Eigen/Dense>
#include <gtest/gtest.h>

#include <tuple>

#define FUNCY_ENABLE_EXCEPTIONS
#include <funcy/linalg.h>

namespace
{
    constexpr int dim = 3;

    using M = Eigen::Matrix< double, dim, dim >;
    using funcy::linalg::det;

    auto generateA()
    {
        M m;
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

    auto generateDA()
    {
        M m;
        m.fill( 0 );
        m( 0, 0 ) = 1;
        m( 1, 1 ) = 1;
        m( 2, 2 ) = 1;
        return m;
    }
} // namespace

TEST( DeterminantTest, D0 )
{
    auto d = det( generateA() );
    EXPECT_DOUBLE_EQ( d.d0(), 21. );
}

TEST( DeterminantTest, D1 )
{
    using funcy::linalg::compute_cofactor;
    auto d = det( generateA() );
    EXPECT_DOUBLE_EQ( d.d1( generateDA() ), -46. );
    auto c = compute_cofactor< 0, 0 >( generateA() ) + compute_cofactor< 1, 1 >( generateA() ) +
             compute_cofactor< 2, 2 >( generateA() );
    EXPECT_DOUBLE_EQ( d.d1( generateDA() ), c );
}

TEST( DeterminantTest, D2 )
{
    auto d = det( generateA() );
    EXPECT_DOUBLE_EQ( d.d2( generateDA(), generateDA() ), 10. );
}

TEST( DeterminantTest, D3 )
{
    auto d = det( generateA() );
    EXPECT_DOUBLE_EQ( d.d3( generateDA(), generateDA(), generateDA() ), 6. );
}
