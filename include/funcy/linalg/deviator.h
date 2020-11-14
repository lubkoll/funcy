#pragma once

#include <funcy/concepts.h>
#include <funcy/constant.h>
#include <funcy/generate.h>
#include <funcy/identity.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/trace.h>
#include <funcy/linalg/unit_matrix.h>
#include <funcy/util/macros.h>

#include <type_traits>

namespace funcy::linalg
{
    /** @addtogroup LinearAlgebraGroup
     *  @{ */

    /// Generate %deviator \f$ \mathrm{dev}(A) = A - \frac{\mathrm{tr}(A)}{n}I \f$ of a matrix
    /// \f$ A\in\mathbb{R}^{n,n} \f$.
    template < SquareMatrix M, int n = dim< M >() >
    [[nodiscard]] auto deviator( const M& A )
    {
        return identity( A ) + ( -1. / n ) * ( trace( A ) * constant( unit_matrix< M >() ) );
    }

    /// Generate %deviator \f$ \mathrm{dev}(A) = A - \frac{\mathrm{tr}(A)}{n}I \f$ of a matrix
    /// \f$ A\in\mathbb{R}^{n,n} \f$.
    template < class Matrix >
    [[nodiscard]] auto deviator( const Matrix& A )
    {
        FUNCY_ASSERT( rows( A ) == cols( A ) );
        return identity( A ) +
               ( -1. / rows( A ) ) * ( trace( A ) * constant( unit_matrix< Matrix >() ) );
    }

    /// Generate %deviator \f$ \mathrm{dev}\circ f\f$.
    template < Function F >
    [[nodiscard]] auto deviator( const F& f )
    {
        return deviator( f() )( f );
    }

    /** @} */
} // namespace funcy::linalg
