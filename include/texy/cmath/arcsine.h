#pragma once

#include <funcy/util/chainer.h>

#include <texy/concepts.h>
#include <texy/util/string.h>

/*!
  @ingroup TexifyCMathGroup

  @brief Arc sine function (based on asin(std::string) in
  \<cmath\>).

  For scalar functions directional derivatives are less interesting. Incorporating this function
  as building block for more complex functions requires directional derivatives. These occur
  during applications of the chain rule.
 */
namespace texy
{
    struct ASin : funcy::Chainer< ASin >
    {
        //! @copydoc Cos::Cos()
        explicit ASin( const std::string& x = "x" )
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
            return std::string( "\\arcsin" ).append( addTexScope( forceAddScope( x ) ) );
        }

        //! @copydoc Cos::d1()
        std::string d1( const std::string& dx = "" ) const
        {
            return std::string( "\\frac{1}{\\sqrt{1-" )
                .append( addScope( x ) )
                .append( "^2}}" )
                .append( multiply_if_not_empty( dx ) );
        }

        //! @copydoc Cos::d2()
        std::string d2( const std::string& dx = "", const std::string& dy = "" ) const
        {
            return addScope( x )
                .append( "*(1" )
                .append( "-" )
                .append( addScope( x ) )
                .append( "^2)^{-3/2}" )
                .append( multiply_if_not_empty( dx ) )
                .append( multiply_if_not_empty( dy ) );
        }

        //! @copydoc Cos::d3()
        std::string d3( const std::string& dx = "", const std::string& dy = "",
                        const std::string& dz = "" ) const
        {
            auto first =
                std::string( "\\frac{1}{(1-" ).append( addScope( x ) ).append( "^2)^{3/2}}*" );
            const auto second = std::string( "(1 + \\frac{3*" )
                                    .append( addScope( x ) )
                                    .append( "^2" )
                                    .append( "}{1-x^2})" );
            return first.append( second )
                .append( multiply_if_not_empty( dx ) )
                .append( multiply_if_not_empty( dy ) )
                .append( multiply_if_not_empty( dz ) );
        }

    private:
        std::string d1p3() const
        {
            return std::string( "(1-" ).append( addScope( x ) ).append( "^2" ).append( "^(-3/2)" );
        }

        std::string x;
    };

    /*!
      @ingroup TexifyCMathGroup
      @brief Generate \f$ \arcsin\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<ASin,Function>
     */
    template < Function F >
    auto asin( const F& f )
    {
        return ASin()( f );
    }
} // namespace texy
