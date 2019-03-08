// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef FUNCY_LINEAR_ALGEBRA_DEVIATORIC_INVARIANTS_HH
#define FUNCY_LINEAR_ALGEBRA_DEVIATORIC_INVARIANTS_HH

#include "deviator.hh"
#include "frobenius_norm.hh"
#include "funcy/mathematical_operations/chain.hh"
#include "funcy/util/static_checks.hh"

namespace funcy
{
  namespace LinearAlgebra
  {
    /**
     * @ingroup InvariantGroup
     * @brief Second deviatoric invariant \f$ j_2(\sigma)=\sqrt{\bar\sigma\negthinspace:\negthinspace\bar\sigma} \f$ with
     * \f$\bar\sigma = \sigma - \frac{\mathrm{tr}(\sigma)}{n}I\f$ and \f$\sigma\in\mathbb{R}^{n,n}\f$.
     */
    template <class Matrix,
              std::enable_if_t<!Checks::isFunction<Matrix>()>* = nullptr>
    auto j2(const Matrix& A)
    {
      return frobeniusNorm(A)( deviator(A) );
    }
  }
}
#endif // FUNCY_LINEAR_ALGEBRA_DEVIATORIC_INVARIANTS_HH
