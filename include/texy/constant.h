#pragma once

#include <funcy/util/chainer.h>

#include <string>

namespace texy
{
    /// Wrap a constant.
    struct Constant : funcy::Chainer< Constant >
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
    Constant constant( const Arg& x )
    {
        using std::to_string;
        return Constant( to_string( x ) );
    }

    inline Constant constant( const std::string& x )
    {
        return Constant( x );
    }
} // namespace texy
