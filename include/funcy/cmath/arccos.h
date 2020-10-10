#pragma once

#include <funcy/concepts.h>
#include <funcy/util/chainer.h>
#include <funcy/util/exceptions.h>
#include <funcy/util/macros.h>

#include <cmath>

namespace funcy
{
    /*!
      @ingroup CMathGroup

      @brief Arc cosine function (based on acos(double) in
      \<cmath\>).

      For scalar functions directional derivatives are less interesting. Incorporating this function
      as building block for more complex functions requires directional derivatives. These occur
      during applications of the chain rule.
     */
    struct ACos : Chainer< ACos >
    {
        //! @copydoc Cos::Cos()
        explicit ACos( double x = 0. ) FUNCY_NOEXCEPT
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( double x ) FUNCY_NOEXCEPT
        {
#ifdef FUNCY_ENABLE_EXCEPTIONS
            if ( x < -1 || x > 1 )
                throw OutOfDomainException( "ACos", "[-1,1]", x, __FILE__, __LINE__ );
#endif
            value = ::acos( x );
            firstDerivative = -1 / ::sqrt( 1 - ( x * x ) );
            firstDerivative3 = firstDerivative * firstDerivative * firstDerivative;
            x_ = x;
        }

        //! @copydoc Cos::d0()
        [[nodiscard]] double d0() const noexcept
        {
            return value;
        }

        //! @copydoc Cos::d1()
        [[nodiscard]] double d1( double dx = 1 ) const noexcept
        {
            return firstDerivative * dx;
        }

        //! @copydoc Cos::d2()
        [[nodiscard]] double d2( double dx = 1, double dy = 1 ) const noexcept
        {
            return x_ * firstDerivative3 * dx * dy;
        }

        //! @copydoc Cos::d3()
        [[nodiscard]] double d3( double dx = 1, double dy = 1, double dz = 1 ) const noexcept
        {
            return firstDerivative3 *
                   ( 1 + ( 3 * x_ * x_ / ( firstDerivative * firstDerivative ) ) ) * dx * dy * dz;
        }

    private:
        double value = 0., firstDerivative = 1., firstDerivative3 = 1., x_ = 0.;
    };

    /*!
      @ingroup CMathGroup
      @brief Generate \f$ \arccos\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<ACos,F>
     */
    template < Function F >
    [[nodiscard]] auto acos( const F& f )
    {
        return ACos()( f );
    }
} // namespace funcy
