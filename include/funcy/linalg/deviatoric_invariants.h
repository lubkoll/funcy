#pragma once

#include "deviator.h"
#include "frobenius_norm.h"
#include <funcy/util/static_checks.h>

namespace funcy
{
  namespace linalg
  {
    /**
     * @ingroup InvariantGroup
     * @brief Second deviatoric invariant \f$ j_2(\sigma)=\sqrt{\bar\sigma\negthinspace:\negthinspace\bar\sigma} \f$ with
     * \f$\bar\sigma = \sigma - \frac{\mathrm{tr}(\sigma)}{n}I\f$ and \f$\sigma\in\mathbb{R}^{n,n}\f$.
     */
    template <class Matrix,
              std::enable_if_t<!Concepts::isFunction<Matrix>()>* = nullptr>
    auto j2(const Matrix& A)
    {
      return frobeniusNorm(A)( deviator(A) );
    }
  }
}
