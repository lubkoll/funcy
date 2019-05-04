#pragma once

#include <utility>
#include "voider.hh"

namespace funcy
{
  namespace concept
  {
    /// @cond
    template <class Matrix>
    using TryMemFn_rows = decltype(std::declval<Matrix>().rows());

    template <class Matrix>
    using TryMemFn_cols = decltype(std::declval<Matrix>().cols());

    template <class Matrix>
    using TryMem_n_rows = decltype(std::declval<Matrix>().n_rows);

    template <class Matrix>
    using TryMem_n_cols = decltype(std::declval<Matrix>().n_cols);

    template <class Vector>
    using TryMemFn_size = decltype (std::declval<Vector>().size());


    template <class Matrix, class=void>
    struct HasMemFn_nrows
        : std::false_type {};

    template <class Matrix>
    struct HasMemFn_nrows< Matrix, void_t< TryMemFn_rows< Matrix > > >
        : std::true_type {};


    template <class Matrix, class=void>
    struct HasMemFn_cols
        : std::false_type {};
    template <class Matrix>
    struct HasMemFn_cols< Matrix, void_t< TryMemFn_cols< Matrix > > >
        : std::true_type {};


    template <class Matrix, class=void>
    struct HasMem_n_rows
        : std::false_type {};
    template <class Matrix>
    struct HasMem_n_rows< Matrix, void_t < TryMem_n_rows<Matrix> > >
        : std::true_type {};


    template <class Matrix, class=void>
    struct HasMem_n_cols
        : std::false_type {};

    template <class Matrix>
    struct HasMem_n_cols< Matrix, void_t < TryMem_n_cols<Matrix> > >
        : std::true_type {};


    template <class Vector, class=void>
    struct HasMemFn_size
            : std::false_type {};

    template <class Vector>
    struct HasMemFn_size< Vector, void_t< TryMemFn_size<Vector> > >
            : std::true_type {};
    /// @endcond


    /** @addtogroup ConceptCheck
     *  @{ */
    /// Check if object of type Matrix has a member function rows().
    template <class Matrix>
    constexpr bool hasMemFn_rows()
    {
      return HasMemFn_nrows<Matrix>::value;
    }

    /// Check if object of type Matrix has a member n_rows.
    template <class Matrix>
    constexpr bool hasMem_n_rows()
    {
      return HasMem_n_rows<Matrix>::value;
    }

    /// Check if object of type Matrix has a member function cols().
    template <class Matrix>
    constexpr bool hasMemFn_cols()
    {
      return HasMemFn_cols<Matrix>::value;
    }

    /// Check if object of type Matrix has a member n_cols.
    template <class Matrix>
    constexpr bool hasMem_n_cols()
    {
      return HasMem_n_cols<Matrix>::value;
    }

    /// Check if object of type Vector has a member function size().
    template <class Vector>
    constexpr bool hasMemFn_size()
    {
      return HasMemFn_cols<Vector>::value;
    }
    /** @} */
  }
}
