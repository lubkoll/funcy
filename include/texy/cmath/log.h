#pragma once

#include <texy/concepts.h>
#include <texy/util/chainer.h>
#include <texy/util/string.h>

/** @addtogroup TexifyCMathGroup
 *  @{ */

/**
 * @brief Natural logarithm including first three derivatives.
 *
 * For scalar functions directional derivatives are less interesting. Incorporating this
 * function
 * as building block for more complex functions requires directional derivatives. These occur
 * during applications of the chain rule.
 */
namespace texy
{
    struct LN : Chainer< LN >
    {
        //! @copydoc Cos::Cos()
        explicit LN( const std::string& x = "x" )
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
            return std::string( "\\ln(" ).append( x ).append( ")" );
        }

        //! @copydoc Cos::d1()
        std::string d1( const std::string& dx = "" ) const
        {
            return std::string( "x^{-1}" ).append( multiplyIfNotEmpty( dx ) );
        }

        //! @copydoc Cos::d2()
        std::string d2( const std::string& dx = "", const std::string& dy = "" ) const
        {
            return std::string( "-(x^{-2})" ).append( multiplyIfNotEmpty( dx, dy ) );
        }

        //! @copydoc Cos::d3()
        std::string d3( const std::string& dx = "", const std::string& dy = "",
                        const std::string& dz = "" ) const
        {
            return std::string( "2(x^{-3})" ).append( multiplyIfNotEmpty( dx, dy, dz ) );
        }

    private:
        std::string x;
    };

    /**
     * @brief Common (base 10) logarithm including first three derivatives.
     *
     * For scalar functions directional derivatives are less interesting. Incorporating this
     * function
     * as building block for more complex functions requires directional derivatives. These
     * occur
     * during applications of the chain rule.
     */
    struct Log10 : Chainer< Log10 >
    {
        //! @copydoc Cos::Cos()
        explicit Log10( const std::string& x = "x" )
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
            return std::string( "\\log_10(" ).append( x ).append( ")" );
        }

        //! @copydoc Cos::d1()
        std::string d1( const std::string& dx = "" ) const
        {
            return std::string( "(" ).append( ln10 ).append( "*x)" ).append( "^{-1}" ).append(
                multiplyIfNotEmpty( dx ) );
        }

        //! @copydoc Cos::d2()
        std::string d2( const std::string& dx = "", const std::string& dy = "" ) const
        {
            return std::string( "-" )
                .append( ln10 )
                .append( "^{-1}" )
                .append( x )
                .append( "^{-2}" )
                .append( multiplyIfNotEmpty( dx, dy ) );
        }

        //! @copydoc Cos::d3()
        std::string d3( const std::string& dx = "", const std::string& dy = "",
                        const std::string& dz = "" ) const
        {
            return std::string( "2" )
                .append( ln10 )
                .append( "^{-1}" )
                .append( x )
                .append( "^{-3}" )
                .append( multiplyIfNotEmpty( dx, dy, dz ) );
        }

    private:
        std::string x;
        std::string ln10{ "\\ln(10)" };
    };

    /**
     * @brief %Base 2 logarithm including first three derivatives.
     *
     * For scalar functions directional derivatives are less interesting. Incorporating this
     * function
     * as building block for more complex functions requires directional derivatives. These
     * occur
     * during applications of the chain rule.
     */
    struct Log2 : Chainer< Log2 >
    {
        //! @copydoc Cos::Cos()
        explicit Log2( const std::string& x = "x" )
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
            return std::string( "\\log_2" ).append( forceAddScope( x ) );
        }

        //! @copydoc Cos::d1()
        std::string d1( const std::string& dx = "" ) const
        {
            return std::string( "(" )
                .append( ln2 )
                .append( "*" )
                .append( x )
                .append( ")^{-1}" )
                .append( multiplyIfNotEmpty( dx ) );
        }

        //! @copydoc Cos::d2()
        std::string d2( const std::string& dx = "", const std::string& dy = "" ) const
        {
            return std::string( "-" )
                .append( ln2 )
                .append( "^{-1}" )
                .append( x )
                .append( "^{-2}" )
                .append( multiplyIfNotEmpty( dx, dy ) );
        }

        //! @copydoc Cos::d3()
        std::string d3( const std::string& dx = "", const std::string& dy = "",
                        const std::string& dz = "" ) const
        {
            return std::string( "2" )
                .append( ln2 )
                .append( "^{-1}" )
                .append( x )
                .append( "^{-3}" )
                .append( multiplyIfNotEmpty( dx, dy, dz ) );
        }

    private:
        std::string x;
        std::string ln2{ "\\ln(2)" };
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
} // namespace texy
/** @} */
