#pragma once

#include <utility>

#include "static_checks.h"
#include "type_traits.h"

namespace funcy
{
  /// @cond
  namespace Concepts
  {
    template <class Matrix>
    using TryCallToZeroes = decltype(std::declval<Matrix>().zeros());

    template <class Matrix>
    using TryCallToFill   = decltype(std::declval<Matrix>().fill(0));
  }
  /// @endcond

  /// Specialize this struct for your matrix type if a zero matrix cannot be generated via Matrix(0.).
  template <class Matrix, class = void>
  struct Zero
  {
    /// @return zero matrix
    static Matrix generate()
    {
      return Matrix(0.);
    }
  };

  /// Specialization for the case that a matrix can be set to zero by calling the member function fill(0).
  template <class Matrix>
  struct Zero< Matrix , void_t<Concepts::TryCallToFill<Matrix> > >
  {
    /// @return zero matrix
    static Matrix generate()
    {
      Matrix m;
      m.fill(0);
      return m;
    }

    /// Set all entries of m to 0.
    static Matrix& generate(Matrix& m)
    {
      m.fill(0);
      return m;
    }
  };

  /**
   * @brief Requires that a specialization of struct Zero exists for Matrix.
   * @return constant size zero matrix
   */
  template <class Matrix,
            class = std::enable_if_t<Concepts::isConstantSize<Matrix>() || is_arithmetic<Matrix>::value> >
  Matrix zero()
  {
    return Zero<Matrix>::generate();
  }

  /**
   * @brief Requires that a specialization of struct Zero exists for Matrix.
   * @return dynamic size zero matrix
   */
  template <class Matrix,
            class = std::enable_if_t<!Concepts::isConstantSize<Matrix>() && !is_arithmetic<Matrix>::value> >
  constexpr Matrix zero(int rows, int cols)
  {
    Matrix m(rows,cols);
    return Zero<Matrix>::generate(m);
  }
}
