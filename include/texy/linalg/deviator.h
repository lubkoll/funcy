#pragma once

#include "trace.h"

#include <funcy/util/static_checks.h>

#include <texy/constant.h>
#include <texy/generate.h>
#include <texy/identity.h>
#include <type_traits>

namespace texy
{
    namespace linalg
    {
        /** @addtogroup TexifyLinearAlgebraGroup
         *  @{ */

        /// Generate %deviator \f$ \mathrm{dev}(A) = A - \frac{\mathrm{tr}(A)}{n}I \f$ of a matrix
        /// \f$ A\in\mathbb{R}^{n,n} \f$.
        template < int n >
        auto deviator( const std::string& A )
        {
            return identity( A ) + ( -1. / n ) * ( trace( A ) * constant( "I" ) );
        }

        /// Generate %deviator \f$ \mathrm{dev}\circ f\f$.
        template < class F, std::enable_if_t< funcy::static_check::isFunction< F >() >* = nullptr >
        auto deviator( const F& f )
        {
            return deviator( f() )( f );
        }

        /** @} */
    } // namespace linalg
} // namespace texy
