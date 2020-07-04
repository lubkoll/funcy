#pragma once

#include <funcy/linalg/concepts.h>

#include <type_traits>

namespace funcy
{
    namespace static_check
    {
        /** @addtogroup ConceptCheck
         *  @{ */
        /// Check if object of type Matrix has a member function rows().
        template < class Mat >
        constexpr bool hasmem_fn_rows()
        {
            return false;
        }

        /// Check if object of type Matrix has a member function rows().
        template < class Mat >
        constexpr bool hasmem_fn_rows() requires requires( Mat m )
        {
            { m.rows() };
        }
        {
            return true;
        }

        /// Check if object of type Matrix has a member n_rows.
        template < class Mat >
        constexpr bool hasMem_n_rows()
        {
            return false;
        }

        /// Check if object of type Matrix has a member n_rows.
        template < class Mat >
        constexpr bool hasMem_n_rows() requires requires( Mat m )
        {
            { m.n_rows };
        }
        {
            return true;
        }

        /// Check if object of type Matrix has a member function cols().
        template < class Mat >
        constexpr bool hasmem_fn_cols()
        {
            return false;
        }

        /// Check if object of type Matrix has a member function cols().
        template < class Mat >
        constexpr bool hasmem_fn_cols() requires requires( Mat m )
        {
            { m.cols() };
        }
        {
            return true;
        }

        /// Check if object of type Matrix has a member n_cols.
        template < class Mat >
        constexpr bool hasMem_n_cols()
        {
            return false;
        }

        /// Check if object of type Matrix has a member n_cols.
        template < class Mat >
        constexpr bool hasMem_n_cols() requires requires( Mat m )
        {
            { m.n_cols };
        }
        {
            return true;
        }

        /// Check if object of type Vector has a member function size().
        template < class Vec >
        constexpr bool hasmem_fn_size()
        {
            return false;
        }

        /// Check if object of type Vector has a member function size().
        template < class Vec >
        constexpr bool hasmem_fn_size() requires requires( Vec v )
        {
            { v.size() };
        }
        {
            return true;
        }
        /** @} */
    } // namespace static_check

    /**
     * @brief Requires that a specialization of struct Zero exists for Matrix.
     * @return constant size zero matrix
     */
    template < class Mat >
    constexpr Mat zero()
    {
        return Mat( 0 );
    }

    /**
     * @brief Requires that a specialization of struct Zero exists for Matrix.
     * @return constant size zero matrix
     */
    template < ConstantSize Mat >
    constexpr Mat zero() requires( std::is_default_constructible_v< Mat >&& requires( Mat m ) {
        m.fill( 0 );
    } )
    {
        Mat m;
        m.fill( 0 );
        return m;
    }

    /**
     * @brief Requires that a specialization of struct Zero exists for Matrix.
     * @return dynamic size zero matrix
     */
    template < class Mat >
    Mat zero( int rows,
              int cols ) requires( std::is_constructible_v< Mat, int, int >&& requires( Mat m ) {
        m.fill( 0 );
    } )
    {
        Mat m( rows, cols );
        m.fill( 0 );
        return m;
    }

    template < class Vec >
    constexpr Vec zero() requires std::is_arithmetic_v< Vec >
    {
        return Vec( 0 );
    }
} // namespace funcy
