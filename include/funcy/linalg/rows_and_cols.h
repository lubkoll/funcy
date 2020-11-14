#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/type_traits.h>

#include <type_traits>

namespace funcy::linalg
{
    /// Number of rows of a dynamic size matrix.
    template < class Mat >
    [[nodiscard]] auto rows( const Mat& A ) requires( !ConstantSize< Mat > &&
                                                      static_check::has_mem_fn_rows< Mat >() )
    {
        return A.rows();
    }

    /// Number of rows of a dynamic size matrix.
    template < class Mat >
    [[nodiscard]] auto rows( const Mat& A ) requires( !ConstantSize< Mat > &&
                                                      static_check::has_mem_n_rows< Mat >() )
    {
        return A.n_rows;
    }

    /// Number of rows of a constant size matrix.
    template < ConstantSize Mat >
    [[nodiscard]] constexpr auto rows()
    {
        return detail::NumberOfRows< Mat >::value;
    }

    /// Number of columns of a dynamic size matrix.
    template < class Mat >
    [[nodiscard]] auto cols( const Mat& A ) requires( !ConstantSize< Mat > &&
                                                      static_check::has_mem_fn_cols< Mat >() )
    {
        return A.cols();
    }

    /// Number of columns of a dynamic size matrix.
    template < class Mat >
    [[nodiscard]] auto cols( const Mat& A ) requires( !ConstantSize< Mat > &&
                                                      static_check::has_mem_n_cols< Mat >() )
    {
        return A.n_cols;
    }

    /// Number of columns of a constant size matrix.
    template < ConstantSize Mat >
    [[nodiscard]] constexpr auto cols()
    {
        return detail::NumberOfColumns< Mat >::value;
    }
} // namespace funcy::linalg
