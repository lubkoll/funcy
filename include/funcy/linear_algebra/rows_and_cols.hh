#pragma once

#include <utility>
#include <funcy/util/extract_rows_and_cols.hh>
#include <funcy/util/static_checks_nrows_ncols.hh>
#include <funcy/util/static_checks.hh>

namespace funcy
{
  namespace linalg
  {
    /// @cond
    template <class Matrix, class = void> struct DynamicNumberOfRows;

    template < class Matrix >
    struct DynamicNumberOfRows< Matrix , void_t< concept::TryMemFn_rows<Matrix> > >
    {
      static auto apply(const Matrix& A)
      {
        return A.rows();
      }
    };

    template < class Matrix  >
    struct DynamicNumberOfRows< Matrix , void_t< concept::TryMem_n_rows<Matrix> > >
    {
      static const auto& apply(const Matrix& A) noexcept
      {
        return A.n_rows;
      }
    };

    template <class Vector>
    struct DynamicNumberOfRows< Vector, void_t<concept::TryMemFn_size<Vector> > >
    {
        static decltype(auto) apply(const Vector& v) noexcept
        {
            return v.size();
        }
    };


    template <class Matrix, class = void> struct DynamicNumberOfColumns;

    template < class Matrix >
    struct DynamicNumberOfColumns< Matrix , void_t< concept::TryMemFn_cols<Matrix> > >
    {
      static auto apply(const Matrix& A)
      {
        return A.cols();
      }
    };

    template < class Matrix  >
    struct DynamicNumberOfColumns< Matrix , void_t< concept::TryMem_n_cols<Matrix> > >
    {
      static const auto& apply(const Matrix& A) noexcept
      {
        return A.n_cols;
      }
    };
    /// @endcond


    /// Number of rows of a dynamic size matrix.
    template < class Matrix ,
               std::enable_if_t<!concept::isConstantSize<Matrix>()>* = nullptr >
    auto rows(const Matrix& A)
    {
      return DynamicNumberOfRows< Matrix >::apply( A );
    }

    /// Number of rows of a constant size matrix.
    template < class Matrix ,
               std::enable_if_t<concept::isConstantSize<Matrix>()>* = nullptr >
    constexpr auto rows()
    {
      return NumberOfRows< Matrix >::value;
    }

    /// Number of columns of a dynamic size matrix.
    template < class Matrix ,
               std::enable_if_t<!concept::isConstantSize<Matrix>()>* = nullptr>
    auto cols(const Matrix& A)
    {
      return DynamicNumberOfColumns< Matrix >::apply( A );
    }

    /// Number of columns of a constant size matrix.
    template < class Matrix ,
               std::enable_if_t<concept::isConstantSize<Matrix>()>* = nullptr >
    constexpr auto cols()
    {
      return NumberOfColumns< Matrix >::value;
    }
  }
}
