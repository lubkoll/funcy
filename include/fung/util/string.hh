#pragma once

#include <string>
#include <type_traits>
#include <utility>
#include <ostream>
#include <regex>

namespace FunG
{
    inline std::string addScope( std::string str )
    {
        static std::regex notSimple{".*[a-zA-Z0-9]+\\s*[+|-].*"};
        if ( std::regex_match( str, notSimple ) )
        {
            return std::string( "(" ).append( std::move( str ) ).append( ")" );
        }
        return str;
    }

    inline std::string addStrictScope( std::string str )
    {
        static std::regex notSimple{".+[+|-|\\*|/|\\(|\\^].*"};
        if ( std::regex_match( str, notSimple ) )
        {
            return std::string( "(" ).append( std::move( str ) ).append( ")" );
        }
        return str;
    }

    inline std::string addTexScope( std::string str )
    {
        return std::string( "{" ).append( std::move( str ) ).append( "}" );
    }

    inline std::string addAllScopes( std::string str )
    {
        return addTexScope( addScope( std::move( str ) ) );
    }

    inline std::string multiplyIfNotEmpty( const std::string& dx )
    {
        return dx.empty() ? dx : std::string( "*" ).append( dx );
    }

    inline std::string multiplyIfNotEmpty( const std::string& dx, const std::string& dy )
    {
        return multiplyIfNotEmpty( dx ).append( multiplyIfNotEmpty( dy ) );
    }

    inline std::string multiplyIfNotEmpty( const std::string& dx, const std::string& dy,
                                           const std::string& dz )
    {
        return multiplyIfNotEmpty( dx, dy ).append( multiplyIfNotEmpty( dz ) );
    }

    template <>
    struct MathOpTraits< std::string, void >
    {
        static auto multiply( const std::string& lhs, const std::string& rhs )
        {
            return std::string{addScope( lhs ) + "*" + addScope( rhs )};
        }

        template < class S, std::enable_if_t< std::is_arithmetic< S >::value >* = nullptr >
        static auto multiply( S lhs, const std::string& rhs )
        {
            return std::to_string( lhs ).append( "*" ).append( addScope( rhs ) );
        }

        template < class S, std::enable_if_t< std::is_arithmetic< S >::value >* = nullptr >
        static auto multiply( const std::string& lhs, S rhs )
        {
            return addScope( lhs ).append( "*" ).append( std::to_string( rhs ) );
        }

        static auto add( const std::string& lhs, const std::string& rhs )
        {
            return std::string{lhs + " + " + rhs};
        }
    };
}
