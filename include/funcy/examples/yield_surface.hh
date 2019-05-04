// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef FUNCY_EXAMPLES_YIELD_SURFACE_HH
#define FUNCY_EXAMPLES_YIELD_SURFACE_HH

#include "funcy/finalize.hh"
#include "funcy/generate.hh"
#include "funcy/linear_algebra.hh"

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

#endif // FUNCY_EXAMPLES_YIELD_SURFACE_HH
