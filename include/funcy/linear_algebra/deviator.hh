// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef FUNCY_LINEAR_ALGEBRA_DEVIATOR_HH
#define FUNCY_LINEAR_ALGEBRA_DEVIATOR_HH

#include <type_traits>
#include "funcy/generate.hh"
#include "funcy/identity.hh"
#include "funcy/util/static_checks.hh"
#include "trace.hh"
#include "unit_matrix.hh"

namespace funcy
{
  /// @cond
  namespace Concepts { template <class> struct SquareMatrixConceptChecks; }
  /// @endcond

  namespace LinearAlgebra
  {
    /** @addtogroup LinearAlgebraGroup
     *  @{ */

    /// Generate %deviator \f$ \mathrm{dev}(A) = A - \frac{\mathrm{tr}(A)}{n}I \f$ of a matrix \f$ A\in\mathbb{R}^{n,n} \f$.
    template <class Matrix,
              int n = dim<Matrix>(),
              std::enable_if_t<Checks::isConstantSize<Matrix>() && !Checks::isFunction<Matrix>()>* = nullptr,
              class = Concepts::SquareMatrixConceptCheck<Matrix> >
    auto deviator(const Matrix& A)
    {
      return identity(A) + (-1./n) * ( trace(A) * constant( unitMatrix<Matrix>() ) );
    }

    /// Generate %deviator \f$ \mathrm{dev}(A) = A - \frac{\mathrm{tr}(A)}{n}I \f$ of a matrix \f$ A\in\mathbb{R}^{n,n} \f$.
    template <class Matrix,
              std::enable_if_t<!Checks::isConstantSize<Matrix>() && !Checks::isFunction<Matrix>()>* = nullptr,
              class = Concepts::SquareMatrixConceptCheck<Matrix>>
    auto deviator(const Matrix& A)
    {
      assert(rows(A)==cols(A));
      return identity(A) + (-1./rows(A)) * ( trace(A) * constant( unitMatrix<Matrix>() ) );
    }

    /// Generate %deviator \f$ \mathrm{dev}\circ f\f$.
    template <class F,
              std::enable_if_t<Checks::isFunction<F>()>* = nullptr>
    auto deviator(const F& f)
    {
      return deviator(f())( f );
    }

    /** @} */
  }
}

#endif // FUNCY_LINEAR_ALGEBRA_DEVIATOR_HH