// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef FUNCY_LINEAR_ALGEBRA_DIMENSION_HH
#define FUNCY_LINEAR_ALGEBRA_DIMENSION_HH

#include <type_traits>
#include "funcy/util/extract_rows_and_cols.hh"

namespace funcy
{
  /// @cond
  namespace concepts { template <class> struct SquareMatrixConceptCheck; }
  /// @endcond

  namespace linalg
  {
    /// Specialize this for your matrix class. Dimension (number of rows/columns for square matrices) must be provided by a static member variable called value.
    template <class Matrix, class = concepts::SquareMatrixConceptCheck<Matrix> >
    struct ExtractDimension : NumberOfRows<Matrix> {};

    /// Dimension \f$n\f$ of a fixed size matrix in \f$\mathbb{R}^{n,n}\f$.
    template <class Matrix>
    constexpr int dim()
    {
      return ExtractDimension<Matrix>::value;
    }
  }
}

#endif // FUNCY_LINEAR_ALGEBRA_DIMENSION_HH
