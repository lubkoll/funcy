#pragma once

#include <funcy/util/at.h>
#include "rows_and_cols.h"
#include <funcy/util/static_checks.h>
#include <funcy/util/zero.h>

namespace funcy
{
  namespace linalg
  {
    /** @addtogroup LinearAlgebraGroup
     *  @{ */

    /// Compute tensor product \f$ M = v \otimes w \f$.
    template <class Matrix, class Vector1, class Vector2,
              std::enable_if_t<Concepts::isConstantSize<Matrix>()>* = nullptr>
    Matrix tensorProduct(const Vector1& v, const Vector2& w)
    {
      auto result = zero<Matrix>();

      for( int i=0; i<rows<Matrix>(); ++i )
        for( int j=0; j<cols<Matrix>(); ++j )
          at(result,i,j) = v[i] * w[j];

      return result;
    }

    /// Compute tensor product \f$ M = v \otimes v \f$.
    template <class Matrix, class Vector>
    Matrix tensorProduct(const Vector& v)
    {
      return tensorProduct<Matrix>(v,v);
    }

    /** @} */
  }
}
