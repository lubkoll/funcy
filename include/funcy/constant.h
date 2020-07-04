#pragma once

#include <type_traits>
#include <utility>

namespace funcy
{
    /// Wrap a constant.
    template < class Type >
    struct Constant
    {
        constexpr Constant() = default;

        constexpr Constant( Type&& t_ ) noexcept( std::is_nothrow_move_constructible_v< Type > )
            : t( std::move( t_ ) )
        {
        }

        constexpr Constant( const Type& t_ ) noexcept(
            std::is_nothrow_copy_constructible_v< Type > )
            : t( t_ )
        {
        }

        /// Function value.
        constexpr const Type& operator()() const noexcept
        {
            return t;
        }

    private:
        Type t;
    };

    /**
     * @brief Generate a constant function that stores its argument as constant reference.
     *
     * This admits to use variable constant arguments, i.e. parameters that we want to study.
     */
    template < class Arg >
    auto const_ref( const Arg& x ) noexcept( std::is_nothrow_copy_constructible_v< Arg > )
    {
        return Constant< const Arg& >( x );
    }

    /**
     * @brief Wrap a constant.
     * \return Constant<Arg>(x)
     */
    template < class Arg >
    constexpr auto constant( Arg&& x ) noexcept(
        (std::is_rvalue_reference_v< Arg > && std::is_nothrow_move_constructible_v< Arg >) ||
        (std::is_lvalue_reference_v< Arg > && std::is_nothrow_copy_constructible_v< Arg >))
    {
        return Constant( std::forward< Arg >( x ) );
    }
} // namespace funcy
