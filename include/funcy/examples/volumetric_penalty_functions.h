#pragma once

#include <funcy/cmath/log.h>
#include <funcy/cmath/pow.h>
#include <funcy/concepts.h>
#include <funcy/generate.h>
#include <funcy/linalg/determinant.h>

namespace funcy
{
    /// Create volumetric penalty function composed of a penalty for inflation and one for
    /// compression.
    template < class Inflation, class Compression, Matrix M >
    auto volumetricPenalty( double d0, double d1, const M& A )
    {
        using linalg::det;
        auto f = ( d0 * Inflation() + d1 * Compression() )( det( A ) );
        return f - f();
    }

    /// Create the volumetric penalty function \f$ d_0 j^2 + d_1 \log(j),\ j=\det(A) \f$.
    template < Matrix M >
    auto volumetricQuadAndLog( double d0, double d1, const M& A )
    {
        return volumetricPenalty< Pow< 2 >, LN >( d0, d1, A );
    }

    /// Create the volumetric penalty function \f$ d_0 j^5 + d_1 j^{-5},\ j=\det(A) \f$.
    template < Matrix M >
    auto volumetricHartmannNeff( double d0, double d1, const M& A )
    {
        return volumetricPenalty< Pow< 5 >, Pow< -5 > >( d0, d1, A );
    }
} // namespace funcy
