#pragma once

#include <funcy/util/chainer.h>

#include <texy/concepts.h>
#include <texy/util/string.h>

/** @addtogroup TexifyCMathGroup
 *  @{ */

/*!
  @brief Tangent function.

  For scalar functions directional derivatives are less interesting. Incorporating this function
  as building block for more complex functions requires directional derivatives. These occur
  during applications of the chain rule.
*/
namespace texy
{
    struct Tan : funcy::Chainer< Tan >
    {
        //! @copydoc Cos::Cos()
        explicit Tan( const std::string& x = "x" )
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( const std::string& x )
        {
            this->x = forceAddScope( x );
        }

        //! @copydoc Cos::d0()
        std::string d0() const noexcept
        {
            return std::string( "\\tan" ).append( x );
        }

        //! @copydoc Cos::d1()
        std::string d1( const std::string& dx = "" ) const
        {
            return std::string( "(1+" )
                .append( "\\tan^2" )
                .append( x )
                .append( ")" )
                .append( multiply_if_not_empty( dx ) );
        }

        //! @copydoc Cos::d2()
        std::string d2( const std::string& dx = "", const std::string& dy = "" ) const
        {
            return std::string( "2*" )
                .append( d0() )
                .append( "*" )
                .append( d1( dx ) )
                .append( multiply_if_not_empty( dy ) );
        }

        //! @copydoc Cos::d3()
        std::string d3( const std::string& dx = "", const std::string& dy = "",
                        const std::string& dz = "" ) const
        {
            return std::string( "2*" )
                .append( d1( "" ) )
                .append( "*" )
                .append( "(1 + 3*\\tan^2" )
                .append( x )
                .append( ")" )
                .append( multiply_if_not_empty( dx, dy, dz ) );
        }

    private:
        std::string x;
    };

    /*!
      @brief Generate \f$ \tan\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Tan,Function>
     */
    template < Function F >
    auto tan( const F& f )
    {
        return Tan()( f );
    }
} // namespace texy
/** @} */
