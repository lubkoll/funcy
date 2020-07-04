#pragma once

#include <concepts>
#include <type_traits>

namespace funcy
{
    /** @addtogroup ConceptGroup
     *  @{ */
    namespace linalg
    {
        namespace detail
        {
            /// If necessary, specialize this for your matrix class. Number of rows must be provided
            /// by a static member variable 'value'.
            template < class Matrix >
            struct NumberOfRows : std::integral_constant< int, -1 >
            {
            };

            /// If necessary, specialize this for your matrix class. Number of columns must be
            /// provided by a static member variable 'value'.
            template < class Matrix >
            struct NumberOfColumns : std::integral_constant< int, -1 >
            {
            };

            /// If necessary, specialize this for your matrix class. The transposed type must be
            /// provided as nested member 'type'.
            template < class >
            struct GetTransposed;
        } // namespace detail

        template < class V >
        concept ConstantSize = linalg::detail::NumberOfRows< V >::value > 0;

        template < class M >
        concept SquareMatrix = ( ( linalg::detail::NumberOfRows< M >::value ==
                                   linalg::detail::NumberOfColumns< M >::value ) &&
                                 ConstantSize< M > );

        template < class T >
        concept Vector = (
                             requires( T t ) { { t[ 0 ][ 0 ] }; } ||
                             requires( T t ) { { t( 0, 0 ) }; } ) &&
                         (
                             requires( T t ) { { t *= 0.0 }; } ||
                             requires( T t ) { { 0.0 * t }; } ) &&
                         std::copy_constructible< T >;

        template < class T >
        concept Matrix = (
                             requires( T t ) { { t[ 0 ] }; } || requires( T t ) { { t( 0 ) }; } ) &&
                         (
                             requires( T t ) { { t *= 0.0 }; } ||
                             requires( T t ) { { 0.0 * t }; } ) &&
                         std::copy_constructible< T >;

    } // namespace linalg
    /** @} */
} // namespace funcy
