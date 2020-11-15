#include <funcy/linalg/at.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using funcy::linalg::at;

using testing::Eq;

namespace
{
    struct VectorSquareBrackets
    {
        int operator[]( int i ) const
        {
            return i;
        }

        VectorSquareBrackets& operator*=( double )
        {
            return *this;
        }
    };

    struct VectorRoundBrackets
    {
        int operator()( int i ) const
        {
            return 2 * i;
        }

        VectorRoundBrackets& operator*=( double )
        {
            return *this;
        }
    };

    struct MatrixRoundBrackets
    {
        int operator()( int i, int j ) const
        {
            return 10 * i + j;
        }

        MatrixRoundBrackets& operator*=( double )
        {
            return *this;
        }
    };

    struct ColumnVector
    {
        VectorSquareBrackets operator[]( int ) const
        {
            return {};
        }

        ColumnVector& operator*=( double )
        {
            return *this;
        }
    };
} // namespace

TEST( at, VectorSquareBracketAccess )
{
    const auto A = VectorSquareBrackets{};
    EXPECT_THAT( at( A, 3 ), Eq( 3 ) );
}

TEST( at, VectorRoundBracketAccess )
{
    const auto A = VectorRoundBrackets{};
    EXPECT_THAT( at( A, 3 ), Eq( 6 ) );
}

TEST( at, MatrixSquareBracketAccess )
{
    const auto A = ColumnVector{};
    EXPECT_THAT( at( A, 3, 4 ), Eq( 4 ) );
}

TEST( at, MatrixRoundBracketAccess )
{
    const auto A = MatrixRoundBrackets{};
    EXPECT_THAT( at( A, 3, 4 ), Eq( 34 ) );
}
