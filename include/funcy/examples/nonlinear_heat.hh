#pragma once

#include <funcy/finalize.hh>
#include <funcy/generate.hh>
#include <funcy/variable.hh>

namespace funcy
{
  /*!
    \brief Weak model for nonlinear heat transfer \f$ (c+du^2)\nabla u \f$.
    \param c weighing of linearity
    \param d weighing of nonlinearity
    \param u heat
    \param du heat gradient
   */
  template <class Scalar, class Vector>
  auto heatModel(double c, double d, Scalar u, const Vector& du)
  {
    auto f = (c+d*squared(variable<0>(u)))*variable<0>(du);
    return finalize( f );
  }
}
