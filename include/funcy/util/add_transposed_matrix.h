#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/dimension.h>
#include <funcy/linalg/rows_and_cols.h>

#include <cassert>
#include <type_traits>

namespace funcy
{
    /**
     * @brief Overwrites \f$A\f$ with \f$A+A^T\f$.
     * @return \f$A+A^T\f$
     */
    template < ConstantSize Matrix >
    Matrix addTransposed( Matrix& A )
    {
        using linalg::dim;
        using Index = decltype( dim< Matrix >() );
        for ( Index i = 0; i < dim< Matrix >(); ++i )
            for ( Index j = i + 1; j < dim< Matrix >(); ++j )
                at( A, j, i ) = at( A, i, j ) = at( A, i, j ) + at( A, j, i );
        for ( Index i = 0; i < dim< Matrix >(); ++i )
            at( A, i, i ) *= 2;
        return A;
    }

    /**
     * @brief Overwrites \f$A\f$ with \f$A+A^T\f$.
     * @return \f$A+A^T\f$
     */
    template < class Matrix >
    Matrix addTransposed( Matrix& A )
    {
        using linalg::cols;
        using linalg::rows;
        assert( rows( A ) == cols( A ) );
        using Index = decltype( rows( std::declval< Matrix >() ) );
        for ( Index i = 0; i < rows( A ); ++i )
            for ( Index j = i + 1; j < cols( A ); ++j )
                at( A, j, i ) = at( A, i, j ) = at( A, i, j ) + at( A, j, i );
        for ( Index i = 0; i < rows( A ); ++i )
            at( A, i, i ) *= 2;
        return A;
    }
} // namespace funcy
