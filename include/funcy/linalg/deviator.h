#pragma once

#include <type_traits>
#include <funcy/generate.h>
#include <funcy/identity.h>
#include <funcy/util/static_checks.h>
#include "trace.h"
#include "unit_matrix.h"

namespace funcy
{
  /// @cond
  namespace Concepts { template <class> struct SquareIsMatrixs; }
  /// @endcond

  namespace linalg
  {
    /** @addtogroup LinearAlgebraGroup
     *  @{ */

    /// Generate %deviator \f$ \mathrm{dev}(A) = A - \frac{\mathrm{tr}(A)}{n}I \f$ of a matrix \f$ A\in\mathbb{R}^{n,n} \f$.
    template <class Matrix,
              int n = dim<Matrix>(),
              std::enable_if_t<Concepts::isConstantSize<Matrix>() && !Concepts::isFunction<Matrix>()>* = nullptr,
              class = Concepts::SquareIsMatrix<Matrix> >
    auto deviator(const Matrix& A)
    {
      return identity(A) + (-1./n) * ( trace(A) * constant( unitMatrix<Matrix>() ) );
    }

    /// Generate %deviator \f$ \mathrm{dev}(A) = A - \frac{\mathrm{tr}(A)}{n}I \f$ of a matrix \f$ A\in\mathbb{R}^{n,n} \f$.
    template <class Matrix,
              std::enable_if_t<!Concepts::isConstantSize<Matrix>() && !Concepts::isFunction<Matrix>()>* = nullptr,
              class = Concepts::SquareIsMatrix<Matrix>>
    auto deviator(const Matrix& A)
    {
      assert(rows(A)==cols(A));
      return identity(A) + (-1./rows(A)) * ( trace(A) * constant( unitMatrix<Matrix>() ) );
    }

    /// Generate %deviator \f$ \mathrm{dev}\circ f\f$.
    template <class F,
              std::enable_if_t<Concepts::isFunction<F>()>* = nullptr>
    auto deviator(const F& f)
    {
      return deviator(f())( f );
    }

    /** @} */
  }
}
