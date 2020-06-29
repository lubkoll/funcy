#pragma once

#include <funcy/concepts.h>
#include <funcy/util/extract_rows_and_cols.h>

namespace funcy
{
    namespace linalg
    {
        /// Specialize this for your matrix class. Dimension (number of rows/columns for square
        /// matrices) must be provided by a static member variable called value.
        template < SquareMatrix Matrix >
        struct ExtractDimension : NumberOfRows< Matrix >
        {
        };

        /// Dimension \f$n\f$ of a fixed size matrix in \f$\mathbb{R}^{n,n}\f$.
        template < SquareMatrix Matrix >
        constexpr int dim()
        {
            return ExtractDimension< Matrix >::value;
        }
    } // namespace linalg
} // namespace funcy
