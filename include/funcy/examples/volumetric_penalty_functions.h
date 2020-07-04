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
    auto volumetric_penalty( double d0, double d1, const M& A )
    {
        using linalg::det;
        auto f = ( d0 * Inflation() + d1 * Compression() )( det( A ) );
        return f - f();
    }

    /// Create the volumetric penalty function \f$ d_0 j^2 + d_1 \log(j),\ j=\det(A) \f$.
    template < Matrix M >
    auto volumetric_quad_and_log( double d0, double d1, const M& A )
    {
        return volumetric_penalty< Pow< 2 >, LN >( d0, d1, A );
    }

    /// Create the volumetric penalty function \f$ d_0 j^5 + d_1 j^{-5},\ j=\det(A) \f$.
    template < Matrix M >
    auto volumetric_hartmann_neff( double d0, double d1, const M& A )
    {
        return volumetric_penalty< Pow< 5 >, Pow< -5 > >( d0, d1, A );
    }
} // namespace funcy
