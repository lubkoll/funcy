#pragma once

#include <funcy/concepts.h>
#include <funcy/constant.h>
#include <funcy/generate.h>
#include <funcy/identity.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/trace.h>
#include <funcy/linalg/unit_matrix.h>
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
        template < SquareMatrix M, int n = dim< M >() >
        auto deviator( const M& A )
        {
            return identity( A ) + ( -1. / n ) * ( trace( A ) * constant( unitMatrix< M >() ) );
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
