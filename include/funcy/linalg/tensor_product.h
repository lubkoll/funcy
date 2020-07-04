#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/rows_and_cols.h>
#include <funcy/linalg/type_traits.h>
#include <funcy/util/at.h>

namespace funcy
{
    namespace linalg
    {
        /** @addtogroup LinearAlgebraGroup
         *  @{ */

        /// Compute tensor product \f$ M = v \otimes w \f$.
        template < ConstantSize Matrix, class Vector1, class Vector2 >
        Matrix tensor_product( const Vector1& v, const Vector2& w )
        {
            auto result = zero< Matrix >();

            for ( int i = 0; i < rows< Matrix >(); ++i )
                for ( int j = 0; j < cols< Matrix >(); ++j )
                    at( result, i, j ) = v[ i ] * w[ j ];

            return result;
        }

        /// Compute tensor product \f$ M = v \otimes v \f$.
        template < class Matrix, class Vector >
        Matrix tensor_product( const Vector& v )
        {
            return tensor_product< Matrix >( v, v );
        }
        /** @} */
    } // namespace linalg
} // namespace funcy
