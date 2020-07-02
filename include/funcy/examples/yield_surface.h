#pragma once

#include <funcy/concepts.h>
#include <funcy/finalize.h>
#include <funcy/generate.h>
#include <funcy/linalg.h>

namespace funcy
{
    /// Yield surface \f$ \frac{\beta}{3}\iota_1(\sigma) + J_2(\sigma)-offset \f$, where
    /// \f$\iota_1\f$ is the first principal and \f$J_2\f$ is the second deviatoric invariant.
    template < Matrix M >
    auto yieldSurface( double beta, double offset, M sigma = linalg::unitMatrix< M >() )
    {
        auto i1 = linalg::FirstPrincipalInvariant< M >( sigma );
        auto j2 = linalg::SecondDeviatoricInvariant< M >( sigma );
        auto f = ( beta / linalg::dimension< M >() ) * i1 + j2 - offset;
        return finalize( f );
    }
} // namespace funcy
