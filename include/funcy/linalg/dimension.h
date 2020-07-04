#pragma once

#include <funcy/util/extract_rows_and_cols.h>

namespace funcy
{
    namespace linalg
    {
        /// Specialize this for your matrix class. Dimension (number of rows/columns for square
        /// matrices) must be provided by a static member variable called value.
        template < class Mat >
        struct ExtractDimension : NumberOfRows< Mat >
        {
        };

        /// Dimension \f$n\f$ of a fixed size matrix in \f$\mathbb{R}^{n,n}\f$.
        template < class Mat >
        constexpr int dim()
        {
            return ExtractDimension< Mat >::value;
        }
    } // namespace linalg
} // namespace funcy
