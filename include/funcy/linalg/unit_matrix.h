#pragma once

#include "dimension.h"

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/util/at.h>
#include <funcy/util/zero.h>

namespace funcy
{
    namespace linalg
    {
        /** @addtogroup LinearAlgebraGroup
         *  @{ */

        /// Compute unit matrix for the specified constant size matrix type. This requires that a
        /// corresponding specialization of Zero is provided.
        template < ConstantSize Matrix >
        Matrix unitMatrix()
        {
            Matrix A = zero< Matrix >();
            for ( int i = 0; i < dim< Matrix >(); ++i )
                at( A, i, i ) = 1;
            return A;
        }

        /// Compute unit matrix for the specified dynamic size matrix type. This requires that a
        /// corresponding specialization of Zero is provided.
        template < class Matrix >
        Matrix unitMatrix( int rows )
        {
            Matrix A = zero< Matrix >( rows, rows );
            for ( int i = 0; i < rows; ++i )
                at( A, i, i ) = 1;
            return A;
        }

        /** @} */
    } // namespace linalg
} // namespace funcy
