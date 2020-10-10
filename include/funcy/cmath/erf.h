#pragma once

#include <funcy/concepts.h>
#include <funcy/util/chainer.h>

#include <cmath>

namespace funcy
{
    /** @addtogroup CMathGroup
     *  @{ */

    /*!
      @brief Error function.

      For scalar functions directional derivatives are less interesting. Incorporating this function
      as building block for more complex functions requires directional derivatives. These occur
      during applications of the chain rule.
     */
    struct Erf : Chainer< Erf >
    {
        //! @copydoc Cos::Cos()
        explicit Erf( double x = 0. ) noexcept
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( double x ) noexcept
        {
            x_ = x;
            value = std::erf( x_ );
            firstDerivative = scale * std::exp( -x_ * x_ );
        }

        //! @copydoc Cos::d0()
        [[nodiscard]] double d0() const noexcept
        {
            return value;
        }

        //! @copydoc Cos::d1()
        [[nodiscard]] double d1( double dx = 1. ) const noexcept
        {
            return firstDerivative * dx;
        }

        //! @copydoc Cos::d2()
        [[nodiscard]] double d2( double dx = 1., double dy = 1. ) const noexcept
        {
            return -2 * x_ * d1( dx ) * dy;
        }

        //! @copydoc Cos::d3()
        [[nodiscard]] double d3( double dx = 1., double dy = 1., double dz = 1. ) const noexcept
        {
            return ( 4 * x_ * x_ - 2 ) * d1( dx ) * dy * dz;
        }

    private:
        double scale = 2 / std::sqrt( M_PI );
        double value = 0.;
        double firstDerivative = 1.;
        double x_ = 0;
    };

    /*!
      @brief Generate \f$ \mathrm{erf}\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type MathematicalOperations::Chain<Erf,Function>
     */
    template < Function F >
    [[nodiscard]] auto erf( const F& f )
    {
        return Erf( f() )( f );
    }
    /** @} */
} // namespace funcy
