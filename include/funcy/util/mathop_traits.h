#pragma once

#include <type_traits>

namespace funcy
{
    template < class T, class = void >
    struct MathOpTraits
    {
        template < class S >
        static constexpr auto multiply( const T& lhs, const S& rhs )
        {
            return lhs * rhs;
        }

        template < class S >
        static constexpr auto multiply( const S& lhs,
                                        const T& rhs ) requires( !std::is_same< S, T >::value )
        {
            return lhs * rhs;
        }

        static constexpr auto add( const T& lhs, const T& rhs )
        {
            return lhs + rhs;
        }
    };

    template < class T >
    struct MathOpTraits< T, std::enable_if_t< std::is_arithmetic< T >::value > >
    {
        static constexpr auto multiply( T lhs, T rhs ) noexcept
        {
            return lhs * rhs;
        }

        static constexpr auto add( T lhs, T rhs ) noexcept
        {
            return lhs + rhs;
        }
    };

    template < class T, class S >
    auto multiply_via_traits( T&& lhs, S&& rhs ) requires(
        std::is_same< std::decay_t< T >, std::decay_t< S > >::value &&
        !std::is_arithmetic< std::decay_t< T > >::value )
    {
        return MathOpTraits< std::decay_t< T > >::multiply( std::forward< T >( lhs ),
                                                            std::forward< S >( rhs ) );
    }

    template < class T, class S >
    auto multiply_via_traits( T&& lhs, S&& rhs ) requires(
        !std::is_same< std::decay_t< T >, std::decay_t< S > >::value &&
        !std::is_arithmetic< std::decay_t< T > >::value &&
        !std::is_arithmetic< std::decay_t< S > >::value )
    {
        return MathOpTraits< std::decay_t< T > >::multiply( std::forward< T >( lhs ),
                                                            std::forward< S >( rhs ) );
    }

    template < class T, class S >
    auto multiply_via_traits( T lhs, S rhs ) requires(
        std::is_arithmetic< T >::value&& std::is_arithmetic< S >::value )
    {
        return MathOpTraits< std::common_type_t< T, S > >::multiply( lhs, rhs );
    }

    template < class T, class S >
    auto multiply_via_traits( T lhs,
                              S&& rhs ) requires( std::is_arithmetic< T >::value &&
                                                  !std::is_arithmetic< std::decay_t< S > >::value )
    {
        return MathOpTraits< std::decay_t< S > >::multiply( lhs, std::forward< S >( rhs ) );
    }

    template < class T, class S >
    auto multiply_via_traits( T&& lhs,
                              S rhs ) requires( std::is_arithmetic< S >::value &&
                                                !std::is_arithmetic< std::decay_t< T > >::value )
    {
        return MathOpTraits< std::decay_t< T > >::multiply( std::forward< T >( lhs ), rhs );
    }

    template < class T, class S >
    auto add_via_traits( T&& lhs, S&& rhs ) requires(
        std::is_same< std::decay_t< T >, std::decay_t< S > >::value &&
        !std::is_arithmetic< std::decay_t< T > >::value )
    {
        return MathOpTraits< std::decay_t< T > >::add( std::forward< T >( lhs ),
                                                       std::forward< S >( rhs ) );
    }

    template < class T, class S >
    auto add_via_traits( T lhs, S rhs ) requires(
        std::is_arithmetic< T >::value&& std::is_arithmetic< S >::value )
    {
        return MathOpTraits< std::common_type_t< T, S > >::add( lhs, rhs );
    }
} // namespace funcy
