#define FUNCY_ENABLE_EXCEPTIONS
#include <funcy/linalg/trace.h>

#include <Eigen/Dense>
#include <gtest/gtest.h>

#include <gmock/gmock.h>

using funcy::linalg::trace;

using testing::DoubleEq;

TEST( Trace, NonSymmetricDynamicMatrixThrows )
{
    using M = Eigen::MatrixXd;
    auto m = M( 3, 2 );
    m << 1, 2, 3, 4, 5, 6;

    EXPECT_THROW( auto t = trace( m ), funcy::NonSymmetricMatrixException );
}
