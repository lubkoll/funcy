#pragma once

#include <funcy/concepts.h>
#include <funcy/util/chainer.h>

#include <cmath>

namespace funcy
{
    /** @addtogroup CMathGroup
     *  @{ */

    /*!
      @brief Tangent function.

      For scalar functions directional derivatives are less interesting. Incorporating this function
      as building block for more complex functions requires directional derivatives. These occur
      during applications of the chain rule.
     */
    struct Tan : Chainer< Tan >
    {
        //! @copydoc Cos::Cos()
        explicit Tan( double x = 0. ) noexcept
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( double x ) noexcept
        {
            value = ::tan( x );
            firstDerivative = 1 + ( value * value );
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
            return ( 2 * value * firstDerivative ) * dx * dy;
        }

        //! @copydoc Cos::d3()
        [[nodiscard]] double d3( double dx = 1., double dy = 1., double dz = 1. ) const noexcept
        {
            return 2 * firstDerivative * ( 1 + ( 3 * value * value ) ) * dx * dy * dz;
        }

    private:
        double value = 0., firstDerivative = 1.;
    };

    /*!
      @brief Generate \f$ \tan\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Tan,Function>
     */
    template < Function F >
    [[nodiscard]] auto tan( const F& f )
    {
        return Tan()( f );
    }
    /** @} */
} // namespace funcy
