#pragma once

#include <texy/util/chainer.hh>

#include <string>

namespace stringy
{
    /// Wrap a constant.
    struct Constant : texy::Chainer< Constant >
    {
        Constant() = default;

        Constant( const std::string& t_ ) : t( t_ )
        {
        }

        /// Function value.
        const std::string& d0() const noexcept
        {
            return t;
        }

    private:
        std::string t;
    };

    /**
     * @brief Wrap a constant.
     * @return Constant(to_string(x))
     */
    template < class Arg >
    auto constant( const Arg& x )
    {
        using std::to_string;
        return Constant( to_string( x ) );
    }

    inline auto constant( const std::string& x )
    {
        return Constant( x );
    }
}
