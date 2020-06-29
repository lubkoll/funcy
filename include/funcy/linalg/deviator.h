#pragma once

#include "trace.h"
#include "unit_matrix.h"

#include <funcy/concepts.h>
#include <funcy/generate.h>
#include <funcy/identity.h>
#include <funcy/util/static_checks.h>

#include <type_traits>

namespace funcy
{
    namespace linalg
    {
        /** @addtogroup LinearAlgebraGroup
         *  @{ */

        /// Generate %deviator \f$ \mathrm{dev}(A) = A - \frac{\mathrm{tr}(A)}{n}I \f$ of a matrix
        /// \f$ A\in\mathbb{R}^{n,n} \f$.
        template < SquareMatrix Matrix, int n = dim< Matrix >() >
        auto deviator( const Matrix& A )
        {
            return identity( A ) +
                   ( -1. / n ) * ( trace( A ) * constant( unitMatrix< Matrix >() ) );
        }

        /// Generate %deviator \f$ \mathrm{dev}(A) = A - \frac{\mathrm{tr}(A)}{n}I \f$ of a matrix
        /// \f$ A\in\mathbb{R}^{n,n} \f$.
        template < class Matrix >
        auto deviator( const Matrix& A )
        {
            assert( rows( A ) == cols( A ) );
            return identity( A ) +
                   ( -1. / rows( A ) ) * ( trace( A ) * constant( unitMatrix< Matrix >() ) );
        }

        /// Generate %deviator \f$ \mathrm{dev}\circ f\f$.
        template < Function F >
        auto deviator( const F& f )
        {
            return deviator( f() )( f );
        }

        /** @} */
    } // namespace linalg
} // namespace funcy
