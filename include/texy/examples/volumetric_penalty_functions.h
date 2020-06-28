#pragma once

#include <texy/cmath/log.h>
#include <texy/cmath/pow.h>
#include <texy/generate.h>
#include <texy/linalg/determinant.h>

#include <string>

namespace texy
{
    /// Create volumetric penalty function composed of a penalty for inflation and one for
    /// compression.
    template < class Inflation, class Compression >
    auto volumetricPenalty( double d0, double d1, const std::string& A )
    {
        using linalg::det;
        auto f = ( d0 * Inflation() + d1 * Compression() )( det( A ) );
        return f - f.d0();
    }

    /// Create the volumetric penalty function \f$ d_0 j^2 + d_1 \log(j),\ j=\det(A) \f$.
    auto volumetricQuadAndLog( double d0, double d1, const std::string& A )
    {
        return volumetricPenalty< Pow< 2 >, LN >( d0, d1, A );
    }

    template < class Matrix >
    auto volumetricHartmannNeff( double d0, double d1, const std::string& A )
    {
        return volumetricPenalty< Pow< 5 >, Pow< -5 > >( d0, d1, A );
    }
}
