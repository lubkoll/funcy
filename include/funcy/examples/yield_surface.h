#pragma once

#include <funcy/finalize.h>
#include <funcy/generate.h>
#include <funcy/linalg.h>

namespace funcy
{
  /// Yield surface \f$ \frac{\beta}{3}\iota_1(\sigma) + J_2(\sigma)-offset \f$, where \f$\iota_1\f$ is the first principal and \f$J_2\f$ is the second deviatoric invariant.  
  template <class Matrix>
  auto yieldSurface(double beta, double offset, Matrix sigma = linalg::unitMatrix<Matrix>())
  {
    auto i1 = linalg::FirstPrincipalInvariant<Matrix>( sigma );
    auto j2 = linalg::SecondDeviatoricInvariant<Matrix>( sigma );
    auto f = (beta/linalg::dimension<Matrix>())*i1 + j2 - offset;
    return finalize_scalar( f );
  }
}
