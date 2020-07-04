#pragma once

#include <funcy/concepts.h>
#include <funcy/finalize.h>
#include <funcy/generate.h>
#include <funcy/variable.h>

namespace funcy
{
    /*!
      @brief Weak model for nonlinear heat transfer \f$ (c+du^2)\nabla u \f$.
      \param c weighing of linearity
      \param d weighing of nonlinearity
      \param u heat
      \param du heat gradient
     */
    template < class Scalar, Vector Vec, idx = 0 >
    auto heat_model( double c, double d, Scalar u, const Vec& du )
    {
        auto f = ( c + d * squared( variable< idx >( u ) ) ) * variable< idx >( du );
        return finalize( f );
    }
} // namespace funcy
