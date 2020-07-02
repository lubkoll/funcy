#pragma once

#include <funcy/linalg/concepts.h>

#include <type_traits>
#include <utility>

namespace funcy
{
    /**
     * @brief Requires that a specialization of struct Zero exists for Matrix.
     * @return constant size zero matrix
     */
    template < class Matrix >
    constexpr Matrix zero()
    {
        return Matrix( 0 );
    }

    /**
     * @brief Requires that a specialization of struct Zero exists for Matrix.
     * @return constant size zero matrix
     */
    template < ConstantSize Matrix >
    constexpr Matrix zero() requires(
        std::is_default_constructible_v< Matrix >&& requires( Matrix m ) { m.fill( 0 ); } )
    {
        Matrix m;
        m.fill( 0 );
        return m;
    }

    /**
     * @brief Requires that a specialization of struct Zero exists for Matrix.
     * @return dynamic size zero matrix
     */
    template < class Matrix >
    Matrix zero( int rows, int cols ) requires(
        std::is_default_constructible_v< Matrix, int, int >&& requires( Matrix m ) {
            m.fill( 0 );
        } )
    {
        Matrix m( rows, cols );
        m.fill( 0 );
        return m;
    }

    template < class V >
    constexpr V zero() requires std::is_arithmetic_v< V >
    {
        return V( 0 );
    }
} // namespace funcy
