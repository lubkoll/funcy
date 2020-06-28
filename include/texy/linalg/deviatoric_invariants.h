#pragma once

#include "deviator.h"
#include "frobenius_norm.h"

namespace texy
{
    namespace linalg
    {
        /**
         * @ingroup InvariantGroup
         * @brief Second deviatoric invariant \f$
         * j_2(\sigma)=\sqrt{\bar\sigma\negthinspace:\negthinspace\bar\sigma} \f$ with
         * \f$\bar\sigma = \sigma - \frac{\mathrm{tr}(\sigma)}{n}I\f$ and
         * \f$\sigma\in\mathbb{R}^{n,n}\f$.
         */
        template < int n >
        auto j2( const std::string& A )
        {
            return frobeniusNorm( A )( deviator< n >( A ) );
        }
    }
}
