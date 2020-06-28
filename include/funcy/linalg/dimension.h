#pragma once

#include <type_traits>
#include <funcy/util/extract_rows_and_cols.h>

namespace funcy
{
  /// @cond
  namespace concept { template <class> struct SquareIsMatrix; }
  /// @endcond

  namespace linalg
  {
    /// Specialize this for your matrix class. Dimension (number of rows/columns for square matrices) must be provided by a static member variable called value.
    template <class Matrix, class = concept::SquareIsMatrix<Matrix> >
    struct ExtractDimension : NumberOfRows<Matrix> {};

    /// Dimension \f$n\f$ of a fixed size matrix in \f$\mathbb{R}^{n,n}\f$.
    template <class Matrix>
    constexpr int dim()
    {
      return ExtractDimension<Matrix>::value;
    }
  }
}
