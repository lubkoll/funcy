#pragma once

#include <funcy/concepts.h>
#include <funcy/util/chainer.h>

#include <cmath>

namespace funcy
{
    /*!
      @ingroup CMathGroup

      @brief Sine function (based on sin(double) in \<cmath\>).

      For scalar functions directional derivatives are less interesting. Incorporating this function
      as building block for more complex functions requires directional derivatives. These occur
      during applications of the chain rule.
     */
    struct Sin : Chainer< Sin >
    {
        //! @copydoc Cos::Cos()
        explicit Sin( double x = 0 ) noexcept
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( double x ) noexcept
        {
            sinx = ::sin( x );
            cosx = ::cos( x );
        }

        //! @copydoc Cos::d0()
        [[nodiscard]] double d0() const noexcept
        {
            return sinx;
        }

        //! @copydoc Cos::d1()
        [[nodiscard]] double d1( double dx = 1. ) const noexcept
        {
            return cosx * dx;
        }

        //! @copydoc Cos::d2()
        [[nodiscard]] double d2( double dx = 1., double dy = 1. ) const noexcept
        {
            return -sinx * dx * dy;
        }

        //! @copydoc Cos::d3()
        [[nodiscard]] double d3( double dx = 1., double dy = 1., double dz = 1. ) const noexcept
        {
            return -cosx * dx * dy * dz;
        }

    private:
        double sinx = 0, cosx = 1;
    };

    /*!
      @ingroup CMathGroup
      @brief Generate \f$ \sin\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Sin,Function>
     */
    template < Function F >
    [[nodiscard]] auto sin( const F& f )
    {
        return Sin()( f );
    }
} // namespace funcy
