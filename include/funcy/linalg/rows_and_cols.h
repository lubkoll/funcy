#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/util/extract_rows_and_cols.h>
#include <funcy/util/static_checks.h>
#include <funcy/util/static_checks_nrows_ncols.h>

#include <utility>

namespace funcy
{
    namespace linalg
    {
        /// Number of rows of a dynamic size matrix.
        template < class Matrix >
        auto rows( const Matrix& A ) requires( static_check::hasMemFn_rows< Matrix >() )
        {
            return A.rows();
        }

        /// Number of rows of a dynamic size matrix.
        template < class Matrix >
        auto rows( const Matrix& A ) requires( static_check::hasMem_n_rows< Matrix >() )
        {
            return A.n_rows;
        }

        /// Number of rows of a dynamic size matrix.
        template < class Matrix >
        auto rows( const Matrix& A ) requires( static_check::hasMemFn_size< Matrix >() )
        {
            return A.size();
        }

        /// Number of rows of a constant size matrix.
        template < ConstantSize Matrix >
        constexpr auto rows()
        {
            return NumberOfRows< Matrix >::value;
        }

        /// Number of columns of a dynamic size matrix.
        template < class Matrix >
        auto cols( const Matrix& A ) requires( static_check::hasMemFn_cols< Matrix >() )
        {
            return A.cols();
        }

        /// Number of columns of a dynamic size matrix.
        template < class Matrix >
        auto cols( const Matrix& A ) requires( static_check::hasMem_n_cols< Matrix >() )
        {
            return A.n_cols;
        }

        /// Number of columns of a constant size matrix.
        template < ConstantSize Matrix >
        constexpr auto cols()
        {
            return NumberOfColumns< Matrix >::value;
        }
    } // namespace linalg
} // namespace funcy
