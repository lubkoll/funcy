// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef FUNCY_LINEAR_ALGEBRA_TENSOR_PRODUCT_HH
#define FUNCY_LINEAR_ALGEBRA_TENSOR_PRODUCT_HH

#include "funcy/util/at.hh"
#include "rows_and_cols.hh"
#include "funcy/util/static_checks.hh"
#include "funcy/util/zero.hh"

namespace funcy
{
  namespace linalg
  {
    /** @addtogroup LinearAlgebraGroup
     *  @{ */

    /// Compute tensor product \f$ M = v \otimes w \f$.
    template <class Matrix, class Vector1, class Vector2,
              std::enable_if_t<concept::isConstantSize<Matrix>()>* = nullptr>
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

#endif // FUNCY_LINEAR_ALGEBRA_TENSOR_PRODUCT_HH
