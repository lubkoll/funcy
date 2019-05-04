// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef FUNCY_LINEAR_ALGEBRA_UNIT_MATRIX_HH
#define FUNCY_LINEAR_ALGEBRA_UNIT_MATRIX_HH

#include "funcy/util/at.hh"
#include "funcy/util/extract_rows_and_cols.hh"
#include "funcy/util/voider.hh"
#include "funcy/util/zero.hh"
#include "dimension.hh"

namespace funcy
{
  namespace linalg
  {
    /** @addtogroup LinearAlgebraGroup
     *  @{ */

    /// Compute unit matrix for the specified constant size matrix type. This requires that a corresponding specialization of Zero is provided.
    template <class Matrix, class = std::enable_if_t<Checks::isConstantSize<Matrix>()> >
    Matrix unitMatrix()
    {
      Matrix A = zero<Matrix>();
      for(int i=0; i<dim<Matrix>(); ++i) at(A,i,i) = 1;
      return A;
    }

    /// Compute unit matrix for the specified dynamic size matrix type. This requires that a corresponding specialization of Zero is provided.
    template <class Matrix, class = std::enable_if_t<!Checks::isConstantSize<Matrix>()> >
    Matrix unitMatrix(int rows)
    {
      Matrix A = zero<Matrix>(rows,rows);
      for(int i=0; i<rows; ++i) at(A,i,i) = 1;
      return A;
    }

    /** @} */
  }
}

#endif // FUNCY_LINEAR_ALGEBRA_UNIT_MATRIX_HH
