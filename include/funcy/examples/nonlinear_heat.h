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
    template < class Scalar, Vector V >
    auto heatModel( double c, double d, Scalar u, const V& du )
    {
        auto f = ( c + d * squared( variable< 0 >( u ) ) ) * variable< 0 >( du );
        return finalize( f );
    }
} // namespace funcy
