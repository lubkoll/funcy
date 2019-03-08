// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef FUNCY_EXAMPLES_VOLUMETRIC_PENALTY_FUNCTIONS_HH
#define FUNCY_EXAMPLES_VOLUMETRIC_PENALTY_FUNCTIONS_HH

#include "funcy/generate.hh"
#include "funcy/cmath/log.hh"
#include "funcy/cmath/pow.hh"
#include "funcy/linear_algebra/determinant.hh"

namespace funcy
{
  /// Create volumetric penalty function composed of a penalty for inflation and one for compression.
  template <class Inflation, class Compression, class Matrix>
  auto volumetricPenalty(double d0, double d1, const Matrix& A)
  {
    using LinearAlgebra::det;
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

#endif // FUNCY_EXAMPLES_VOLUMETRIC_PENALTY_FUNCTIONS_HH
