#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/at.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/rows_and_cols.h>
#include <funcy/linalg/type_traits.h>
#include <funcy/util/mathop_traits.h>

namespace funcy::linalg
{
    /** @addtogroup LinearAlgebraGroup
     *  @{ */

    /// Compute tensor product \f$ M = v \otimes w \f$.
    template < ConstantSize Matrix, class Vector1, class Vector2 >
    [[nodiscard]] Matrix tensor_product( const Vector1& v, const Vector2& w )
    {
        auto result = zero< Matrix >();

        for ( int i = 0; i < rows< Matrix >(); ++i )
            for ( int j = 0; j < cols< Matrix >(); ++j )
                at( result, i, j ) = multiply_via_traist( v[ i ], w[ j ] );

        return result;
    }

    /// Compute tensor product \f$ M = v \otimes v \f$.
    template < class Matrix, class Vector >
    Matrix tensor_product( const Vector& v )
    {
        return tensor_product< Matrix >( v, v );
    }
    /** @} */
} // namespace funcy::linalg
