#pragma once

#include <type_traits>

namespace funcy
{
    /// @cond
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
                                        const T& rhs ) requires( !std::same_as< S, T > )
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
        std::same_as< std::decay_t< T >, std::decay_t< S > > && !Arithmetic< std::decay_t< T > > )
    {
        return MathOpTraits< std::decay_t< T > >::multiply( std::forward< T >( lhs ),
                                                            std::forward< S >( rhs ) );
    }

    template < class T, class S >
    auto multiply_via_traits( T&& lhs, S&& rhs ) requires(
        !std::same_as< std::decay_t< T >, std::decay_t< S > > && !Arithmetic< std::decay_t< T > > &&
        !Arithmetic< std::decay_t< S > > )
    {
        return MathOpTraits< std::decay_t< T > >::multiply( std::forward< T >( lhs ),
                                                            std::forward< S >( rhs ) );
    }

    template < Arithmetic T, Arithmetic S >
    auto multiply_via_traits( T lhs, S rhs )
    {
        return MathOpTraits< std::common_type_t< T, S > >::multiply( lhs, rhs );
    }

    template < Arithmetic T, class S >
    auto multiply_via_traits( T lhs, S&& rhs ) requires( !Arithmetic< std::decay_t< S > > )
    {
        return MathOpTraits< std::decay_t< S > >::multiply( lhs, std::forward< S >( rhs ) );
    }

    template < class T, Arithmetic S >
    auto multiply_via_traits( T&& lhs, S rhs ) requires( !Arithmetic< std::decay_t< T > > )
    {
        return MathOpTraits< std::decay_t< T > >::multiply( std::forward< T >( lhs ), rhs );
    }

    template < class T, class S >
    auto add_via_traits( T&& lhs,
                         S&& rhs ) requires( std::same_as< std::decay_t< T >, std::decay_t< S > > &&
                                             !Arithmetic< std::decay_t< T > > )
    {
        return MathOpTraits< std::decay_t< T > >::add( std::forward< T >( lhs ),
                                                       std::forward< S >( rhs ) );
    }

    template < Arithmetic T, Arithmetic S >
    auto add_via_traits( T lhs, S rhs )
    {
        return MathOpTraits< std::common_type_t< T, S > >::add( lhs, rhs );
    }
    /// @endcond
} // namespace funcy
