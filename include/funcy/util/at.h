#pragma once

#include "macros.h"

#include <funcy/concepts.h>

namespace funcy
{
// suppress warnings coming from the __attribute__((always_inline))
#if defined( __GNUC__ ) || defined( __GNUG__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

    /// Access matrix entry \f$A_{ij}\f via square brackets$.
    template < class Matrix, class Index >
    FUNCY_ALWAYS_INLINE decltype( auto )
    at( Matrix&& A, Index i, Index j ) requires MatrixSupportSquareBracketAccess< Matrix >
    {
        return A[ i ][ j ];
    }

    /// Access matrix entry \f$A_{ij}\f via square brackets$.
    template < class Matrix, class Index >
    FUNCY_ALWAYS_INLINE decltype( auto )
    at( Matrix&& A, Index i, Index j ) requires MatrixSupportRoundBracketAccess< Matrix >
    {
        return A( i, j );
    }

    /// Access vector entry \f$\v_if$.
    template < class Vector, class Index >
    FUNCY_ALWAYS_INLINE decltype( auto )
    at( Vector&& v, Index i ) requires VectorSupportSquareBracketAccess< Vector >
    {
        return v[ i ];
    }

    /// Access vector entry \f$\v_if$.
    template < class Vector, class Index >
    FUNCY_ALWAYS_INLINE decltype( auto )
    at( Vector&& v, Index i ) requires VectorSupportRoundBracketAccess< Vector >
    {
        return v( i );
    }
} // namespace funcy
#if defined( __GNUC__ ) || defined( __GNUG__ )
#pragma GCC diagnostic pop
#endif
