#pragma once

#include <funcy/util/chainer.h>

#include <texy/concepts.h>
#include <texy/util/string.h>
#include <type_traits>

namespace texy
{
    /** @addtogroup TexifyCMathGroup
     *  @{ */

    /*!
      @brief Power function with rational exponent \f$ k = \frac{dividend}{divisor} \f$ including
      first three derivatives.

      For scalar functions directional derivatives are less interesting. Incorporating this function
      as building block for more complex functions requires directional derivatives. These occur
      during applications of the chain rule.
      For the cases \f$k=-1\f$ and \f$k=2\f$ specializations are used that avoid the use of
      std::pow.
     */
    template < int dividend, int divisor = 1 >
    struct Pow : funcy::Chainer< Pow< dividend, divisor > >
    {
        //! @copydoc Cos::Cos()
        explicit Pow( std::string x = "x" )
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( std::string x )
        {
            this->x = addStrictScope( x );
        }

        //! @copydoc Cos::d0()
        std::string d0() const noexcept
        {
            return xtp( k );
        }

        //! @copydoc Cos::d1()
        std::string d1( const std::string& dx = "" ) const
        {
            return std::string( k ).append( "*" ).append(
                xtp( k1 ).append( multiply_if_not_empty( dx ) ) );
        }

        //! @copydoc Cos::d2()
        std::string d2( const std::string& dx = "", const std::string& dy = "" ) const
        {
            return std::string( kk1 ).append( "*" ).append(
                xtp( k2 ).append( multiply_if_not_empty( dx, dy ) ) );
        }

        //! @copydoc Cos::d3()
        std::string d3( const std::string& dx = "", const std::string& dy = "",
                        const std::string& dz = "" ) const
        {
            return std::string( kk1k2 ).append( "*" ).append(
                xtp( k3 ).append( multiply_if_not_empty( dx, dy, dz ) ) );
        }

    private:
        std::string xtp( const std::string& k ) const
        {
            return std::string( x ).append( "^" ).append( addTexScope( k ) );
        }

        std::string x;
        const std::string k =
            std::to_string( dividend ).append( "/" ).append( std::to_string( divisor ) );
        const std::string k1 =
            std::to_string( dividend - divisor ).append( "/" ).append( std::to_string( divisor ) );
        const std::string kk1 = std::to_string( dividend * ( dividend - divisor ) )
                                    .append( "/" )
                                    .append( std::to_string( divisor * divisor ) );
        const std::string k2 = std::to_string( dividend - 2 * divisor )
                                   .append( "/" )
                                   .append( std::to_string( divisor ) );
        const std::string kk1k2 =
            std::to_string( dividend * ( dividend - divisor ) * ( dividend - 2 * divisor ) )
                .append( "/" )
                .append( std::to_string( divisor * divisor * divisor ) );
        const std::string k3 = std::to_string( dividend - 3 * divisor )
                                   .append( "/" )
                                   .append( std::to_string( divisor ) );
    };

    /// @cond
    template <>
    struct Pow< 1, 1 > : funcy::Chainer< Pow< 1, 1 > >
    {
        //! @copydoc Cos::Cos()
        explicit Pow( std::string x = "x" )
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( const std::string& x )
        {
            this->x = x;
        }

        //! @copydoc Cos::d0()
        std::string d0() const noexcept
        {
            return x;
        }

        //! @copydoc Cos::d1()
        std::string d1( std::string dx = "" ) const
        {
            return std::string( "1" ).append( multiply_if_not_empty( dx ) );
        }

    private:
        std::string x;
    };

    /// @cond
    template <>
    struct Pow< 2, 1 > : funcy::Chainer< Pow< 2, 1 > >
    {
        //! @copydoc Cos::Cos()
        explicit Pow( std::string x = "x" )
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( const std::string& x )
        {
            this->x = addStrictScope( x );
        }

        //! @copydoc Cos::d0()
        std::string d0() const noexcept
        {
            return std::string( x ).append( "^2" );
        }

        //! @copydoc Cos::d1()
        std::string d1( const std::string& dx = "" ) const
        {
            return std::string( "2" ).append( x ).append( multiply_if_not_empty( dx ) );
        }

        //! @copydoc Cos::d2()
        std::string d2( const std::string& dx = "", const std::string& dy = "" ) const
        {
            return std::string( "2" ).append( multiply_if_not_empty( dx, dy ) );
        }

    private:
        std::string x;
    };

    /// @cond
    template <>
    struct Pow< 3, 1 > : funcy::Chainer< Pow< 3, 1 > >
    {
        //! @copydoc Cos::Cos()
        explicit Pow( const std::string& x = "x" )
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( const std::string& x )
        {
            this->x = addStrictScope( x );
        }

        //! @copydoc Cos::d0()
        std::string d0() const noexcept
        {
            return std::string( x ).append( "^3" );
        }

        //! @copydoc Cos::d1()
        std::string d1( const std::string& dx = "" ) const
        {
            return std::string( "3" ).append( x ).append( "^2" ).append(
                multiply_if_not_empty( dx ) );
        }

        //! @copydoc Cos::d2()
        std::string d2( const std::string& dx = "", const std::string& dy = "" ) const
        {
            return std::string( "6" ).append( x ).append( multiply_if_not_empty( dx, dy ) );
        }

        //! @copydoc Cos::d3()
        std::string d3( const std::string& dx = "", const std::string& dy = "",
                        const std::string& dz = "" ) const
        {
            return std::string( "6" ).append( multiply_if_not_empty( dx, dy, dz ) );
        }

    private:
        std::string x;
    };

    template < int dividend >
    struct Pow< dividend, 1 > : funcy::Chainer< Pow< dividend, 1 > >
    {
        //! @copydoc Cos::Cos()
        explicit Pow( const std::string& x = "x" )
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( const std::string& x )
        {
            this->x = addStrictScope( x );
        }

        //! @copydoc Cos::d0()
        std::string d0() const noexcept
        {
            return std::string( x ).append( "^" ).append( std::to_string( dividend ) );
        }

        //! @copydoc Cos::d1()
        std::string d1( const std::string& dx = "" ) const
        {
            return std::to_string( dividend )
                .append( x )
                .append( "^" )
                .append( std::to_string( dividend - 1 ) )
                .append( multiply_if_not_empty( dx ) );
        }

        //! @copydoc Cos::d2()
        std::string d2( const std::string& dx = "", const std::string& dy = "" ) const
        {
            return std::to_string( dividend * ( dividend - 1 ) )
                .append( x )
                .append( "^" )
                .append( std::to_string( dividend - 2 ) )
                .append( multiply_if_not_empty( dx, dy ) );
        }

        //! @copydoc Cos::d3()
        std::string d3( const std::string& dx = "", const std::string& dy = "",
                        const std::string& dz = "" ) const
        {
            return std::to_string( dividend * ( dividend - 1 ) * ( dividend - 2 ) )
                .append( x )
                .append( ( dividend - 3 == 1 )
                             ? std::string( "" )
                             : std::string( "^" ).append( std::to_string( dividend - 3 ) ) )
                .append( multiply_if_not_empty( dx, dy, dz ) );
        }

    private:
        std::string x;
    };

    /*!
      @brief Generate \f$ \sqrt{f} \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Sqrt,Function>
     */
    template < Function F >
    auto sqrt( const F& f )
    {
        return Pow< 1, 2 >()( f );
    }

    /*!
      @brief Generate \f$ \sqrt[3]{f} \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Cbrt,Function>
     */
    template < Function F >
    auto cbrt( const F& f )
    {
        return Pow< 1, 3 >()( f );
    }

    /*!
      @brief Generate \f$ \sqrt[3]{f^2}\f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Cbrt2,Function>
     */
    template < Function F >
    auto cbrt2( const F& f )
    {
        return Pow< 2, 3 >()( f );
    }

    /*!
      @brief Generate \f$ f^{k/l} \f$.
      @param f function mapping into a scalar space
      @tparam k dividend
      @tparam l divisor
      @return object of type mathop::Chain< Pow<dividend,divisor> , Function >
     */
    template < int k, int l, Function F >
    auto pow( const F& f )
    {
        return Pow< k, l >()( f );
    }

    /*!
      @brief Generate \f$ f^k,\ k\in\mathbb{N}\f$.
      @param f function mapping into a scalar space
      @tparam k exponent
      @return object of type mathop::Chain< Pow<dividend,divisor> , Function >
     */
    template < int k, Function F >
    auto pow( const F& f )
    {
        return Pow< k >()( f );
    }
    /** @} */
} // namespace texy
