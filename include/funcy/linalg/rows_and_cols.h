#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/type_traits.h>

namespace funcy
{
    namespace linalg
    {
        /// Number of rows of a dynamic size matrix.
        template < class Mat >
        auto rows( const Mat& A ) requires( !ConstantSize< Mat > &&
                                            static_check::hasmem_fn_rows< Mat >() )
        {
            return A.rows();
        }

        /// Number of rows of a dynamic size matrix.
        template < class Mat >
        auto rows( const Mat& A ) requires( !ConstantSize< Mat > &&
                                            static_check::hasMem_n_rows< Mat >() )
        {
            return A.n_rows;
        }

        /// Number of rows of a constant size matrix.
        template < ConstantSize Mat >
        constexpr auto rows()
        {
            return NumberOfRows< Mat >::value;
        }

        /// Number of columns of a dynamic size matrix.
        template < class Mat >
        auto cols( const Mat& A ) requires( !ConstantSize< Mat > &&
                                            static_check::hasmem_fn_cols< Mat >() )
        {
            return A.cols();
        }

        /// Number of columns of a dynamic size matrix.
        template < class Mat >
        auto cols( const Mat& A ) requires( !ConstantSize< Mat > &&
                                            static_check::hasMem_n_cols< Mat >() )
        {
            return A.n_cols;
        }

        /// Number of columns of a constant size matrix.
        template < ConstantSize Mat >
        constexpr auto cols()
        {
            return NumberOfColumns< Mat >::value;
        }
    } // namespace linalg
} // namespace funcy
