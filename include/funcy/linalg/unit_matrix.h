#pragma once

#include <funcy/util/at.h>
#include <funcy/util/extract_rows_and_cols.h>
#include <funcy/util/voider.h>
#include <funcy/util/zero.h>
#include "dimension.h"

namespace funcy
{
  namespace linalg
  {
    /** @addtogroup LinearAlgebraGroup
     *  @{ */

    /// Compute unit matrix for the specified constant size matrix type. This requires that a corresponding specialization of Zero is provided.
    template <class Matrix, class = std::enable_if_t<Concepts::isConstantSize<Matrix>()> >
    Matrix unitMatrix()
    {
      Matrix A = zero<Matrix>();
      for(int i=0; i<dim<Matrix>(); ++i) at(A,i,i) = 1;
      return A;
    }

    /// Compute unit matrix for the specified dynamic size matrix type. This requires that a corresponding specialization of Zero is provided.
    template <class Matrix, class = std::enable_if_t<!Concepts::isConstantSize<Matrix>()> >
    Matrix unitMatrix(int rows)
    {
      Matrix A = zero<Matrix>(rows,rows);
      for(int i=0; i<rows; ++i) at(A,i,i) = 1;
      return A;
    }

    /** @} */
  }
}
