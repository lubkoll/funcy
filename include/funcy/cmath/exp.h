#pragma once

#include <funcy/concepts.h>
#include <funcy/util/chainer.h>

#include <cmath>

namespace funcy
{
    /** @addtogroup CMathGroup
     *  @{ */

    /*!
      @brief Exponential function.

      For scalar functions directional derivatives are less interesting. Incorporating this function
      as building block for more complex functions requires directional derivatives. These occur
      during applications of the chain rule.
     */
    struct Exp : Chainer< Exp >
    {
        //! @copydoc Cos::d0()
        explicit Exp( double x = 0. ) noexcept
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( double x ) noexcept
        {
            e_x = ::exp( x );
        }

        //! @copydoc Cos::d0()
        [[nodiscard]] double d0() const noexcept
        {
            return e_x;
        }

        //! @copydoc Cos::d0()
        [[nodiscard]] double d1( double dx = 1. ) const noexcept
        {
            return e_x * dx;
        }

        //! @copydoc Cos::d0()
        [[nodiscard]] double d2( double dx = 1., double dy = 1. ) const noexcept
        {
            return e_x * dx * dy;
        }

        //! @copydoc Cos::d0()
        [[nodiscard]] double d3( double dx = 1., double dy = 1., double dz = 1. ) const noexcept
        {
            return e_x * dx * dy * dz;
        }

    private:
        double e_x = 1.;
    };

    /*!
      @brief Function \f$2^x\f$.

      For scalar functions directional derivatives are less interesting. Incorporating this function
      as building block for more complex functions requires directional derivatives. These occur
      during applications of the chain rule.
     */
    struct Exp2 : Chainer< Exp2 >
    {
        //! @copydoc Cos::Cos()
        explicit Exp2( double x = 0. ) noexcept
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( double x ) noexcept
        {
            value = exp2( x );
        }

        //! @copydoc Cos::d0()
        [[nodiscard]] double d0() const noexcept
        {
            return value;
        }

        //! @copydoc Cos::d1()
        [[nodiscard]] double d1( double dx = 1. ) const noexcept
        {
            return value * ln2 * dx;
        }

        //! @copydoc Cos::d2()
        [[nodiscard]] double d2( double dx = 1., double dy = 1. ) const noexcept
        {
            return value * ln2 * ln2 * dx * dy;
        }

        //! @copydoc Cos::d3()
        [[nodiscard]] double d3( double dx = 1., double dy = 1., double dz = 1. ) const noexcept
        {
            return value * ln2 * ln2 * ln2 * dx * dy * dz;
        }

    private:
        double value = 1., ln2 = log( 2. );
    };

    /*!
      @brief Generate \f$ \exp(f) \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Exp,Function>
     */
    template < Function F >
    [[nodiscard]] auto exp( const F& f )
    {
        return Exp()( f );
    }

    /*!
      @brief Generate \f$2^f\f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Exp2,Function>
     */
    template < Function F >
    [[nodiscard]] auto exp2( const F& f )
    {
        return Exp2()( f );
    }
    /** @} */
} // namespace funcy
