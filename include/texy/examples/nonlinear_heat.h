#pragma once

#include <funcy/finalize.h>

#include <string>
#include <texy/constant.h>
#include <texy/generate.h>
#include <texy/variable.h>

namespace texy
{
    /*!
      @brief Weak model for nonlinear heat transfer \f$ (c+du^2)\nabla u \f$.
      \param c weighing of linearity
      \param d weighing of nonlinearity
      \param u heat
      \param du heat gradient
     */
    auto heatModel( const std::string& c = "c", const std::string& d = "d",
                    const std::string& u = "u", const std::string& du = "du" )
    {
        return ( constant( c ) + constant( d ) * squared( variable< 0, 0 >( u ) ) ) *
               variable< 0, 1 >( du );
    }
} // namespace texy
