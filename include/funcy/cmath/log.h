#pragma once

#include <funcy/concepts.h>
#include <funcy/util/chainer.h>
#include <funcy/util/exceptions.h>
#include <funcy/util/macros.h>

#include <cmath>

namespace funcy
{
    /** @addtogroup CMathGroup
     *  @{ */

    /**
     * @brief Natural logarithm.
     *
     * For scalar functions directional derivatives are less interesting. Incorporating this
     * function as building block for more complex functions requires directional derivatives. These
     * occur during applications of the chain rule.
     */
    struct LN : Chainer< LN >
    {
        //! @copydoc Cos::Cos()
        explicit LN( double x = 1. ) FUNCY_NOEXCEPT
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( double x ) FUNCY_NOEXCEPT
        {
#ifdef FUNCY_ENABLE_EXCEPTIONS
            if ( x <= 0 )
                throw OutOfDomainException( "LN", "]0,inf[", x, __FILE__, __LINE__ );
#endif
            x_inv = 1. / x;
            value = ::log( x );
        }

        //! @copydoc Cos::d0()
        double d0() const noexcept
        {
            return value;
        }

        //! @copydoc Cos::d1()
        double d1( double dx = 1. ) const noexcept
        {
            return x_inv * dx;
        }

        //! @copydoc Cos::d2()
        double d2( double dx = 1., double dy = 1. ) const noexcept
        {
            return -x_inv * x_inv * dx * dy;
        }

        //! @copydoc Cos::d3()
        double d3( double dx = 1., double dy = 1., double dz = 1. ) const noexcept
        {
            return 2 * x_inv * x_inv * x_inv * dx * dy * dz;
        }

    private:
        double value = 0., x_inv = 1.;
    };

    /**
     * @brief Common (base 10) logarithm.
     *
     * For scalar functions directional derivatives are less interesting. Incorporating this
     * function as building block for more complex functions requires directional derivatives. These
     * occur during applications of the chain rule.
     */
    struct Log10 : Chainer< Log10 >
    {
        //! @copydoc Cos::Cos()
        explicit Log10( double x = 1. ) FUNCY_NOEXCEPT
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( double x ) FUNCY_NOEXCEPT
        {
#ifdef FUNCY_ENABLE_EXCEPTIONS
            if ( x <= 0 )
                throw OutOfDomainException( "Log10", "]0,inf[", x, __FILE__, __LINE__ );
#endif
            x_inv = 1. / x;
            value = ::log10( x );
        }

        //! @copydoc Cos::d0()
        double d0() const noexcept
        {
            return value;
        }

        //! @copydoc Cos::d1()
        double d1( double dx = 1. ) const noexcept
        {
            return ln10inv * x_inv * dx;
        }

        //! @copydoc Cos::d2()
        double d2( double dx = 1., double dy = 1. ) const noexcept
        {
            return -ln10inv * x_inv * x_inv * dx * dy;
        }

        //! @copydoc Cos::d3()
        double d3( double dx = 1., double dy = 1., double dz = 1. ) const noexcept
        {
            return 2 * ln10inv * x_inv * x_inv * x_inv * dx * dy * dz;
        }

    private:
        double value = 0., x_inv = 1., ln10inv = 1 / log( 10. );
    };

    /**
     * @brief %Base 2 logarithm.
     *
     * For scalar functions directional derivatives are less interesting. Incorporating this
     * function as building block for more complex functions requires directional derivatives. These
     * occur during applications of the chain rule.
     */
    struct Log2 : Chainer< Log2 >
    {
        //! @copydoc Cos::Cos()
        explicit Log2( double x = 1. ) FUNCY_NOEXCEPT
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( double x ) FUNCY_NOEXCEPT
        {
#ifdef FUNCY_ENABLE_EXCEPTIONS
            if ( x <= 0 )
                throw OutOfDomainException( "Log2", "]0,inf[", x, __FILE__, __LINE__ );
#endif
            x_inv = 1. / x;
            value = ::log2( x );
        }

        //! @copydoc Cos::d0()
        double d0() const noexcept
        {
            return value;
        }

        //! @copydoc Cos::d1()
        double d1( double dx = 1. ) const noexcept
        {
            return ln2inv * x_inv * dx;
        }

        //! @copydoc Cos::d2()
        double d2( double dx = 1., double dy = 1. ) const noexcept
        {
            return -ln2inv * x_inv * x_inv * dx * dy;
        }

        //! @copydoc Cos::d3()
        double d3( double dx = 1., double dy = 1., double dz = 1. ) const noexcept
        {
            return 2 * ln2inv * x_inv * x_inv * x_inv * dx * dy * dz;
        }

    private:
        double value = 0., x_inv = 1., ln2inv = 1 / log( 2. );
    };

    /*!
      @brief Generate \f$ \mathrm{ln}\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Log,Function>
     */
    template < Function F >
    auto ln( const F& f )
    {
        return LN()( f );
    }

    /*!
      @brief Generate \f$ \mathrm{log}_{10}\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Log10,Function>
     */
    template < Function F >
    auto log10( const F& f )
    {
        return Log10()( f );
    }

    /*!
      @brief Generate \f$ \mathrm{log}_{2}\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Log2,Function>
     */
    template < Function F >
    auto log2( const F& f )
    {
        return Log2()( f );
    }
    /** @} */
} // namespace funcy
