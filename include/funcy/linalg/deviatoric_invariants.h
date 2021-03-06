#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/deviator.h>
#include <funcy/linalg/frobenius_norm.h>

namespace funcy::linalg
{
    /**
     * @ingroup InvariantGroup
     * @brief Second deviatoric invariant \f$
     * j_2(\sigma)=\sqrt{\bar\sigma\negthinspace:\negthinspace\bar\sigma} \f$ with \f$\bar\sigma
     * = \sigma - \frac{\mathrm{tr}(\sigma)}{n}I\f$ and \f$\sigma\in\mathbb{R}^{n,n}\f$.
     */
    template < Matrix M >
    [[nodiscard]] auto j2( const M& A ) requires( !Function< M > )
    {
        return frobenius_norm( A )( deviator( A ) );
    }
} // namespace funcy::linalg
