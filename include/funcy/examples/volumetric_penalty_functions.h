#pragma once

#include <funcy/generate.h>
#include <funcy/cmath/log.h>
#include <funcy/cmath/pow.h>
#include <funcy/linalg/determinant.h>

namespace funcy
{
  /// Create volumetric penalty function composed of a penalty for inflation and one for compression.
  template <class Inflation, class Compression, class Matrix>
  auto volumetricPenalty(double d0, double d1, const Matrix& A)
  {
    using linalg::det;
    auto f = ( d0*Inflation() + d1*Compression() ) ( det(A) );
    return f - f.d0();
  }

  /// Create the volumetric penalty function \f$ d_0 j^2 + d_1 \log(j),\ j=\det(A) \f$.
  template <class Matrix>
  auto volumetricQuadAndLog(double d0, double d1, const Matrix& A)
  {
    return volumetricPenalty< Pow<2> , LN >(d0,d1,A);
  }

  /// Create the volumetric penalty function \f$ d_0 j^5 + d_1 j^{-5},\ j=\det(A) \f$.
  template <class Matrix>
  auto volumetricHartmannNeff(double d0, double d1, const Matrix& A)
  {
    return volumetricPenalty< Pow<5> , Pow<-5> >(d0,d1,A);
  }
}
