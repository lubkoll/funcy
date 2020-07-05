#pragma once

#include <concepts>
#include <type_traits>

namespace funcy
{
    namespace linalg
    {
        namespace detail
        {
            /** @addtogroup ConceptGroup
             *  @{ */
            /**
             * @brief Get number of rows for constant size matrices.
             *
             * If necessary, specialize this for your matrix class.
             */
            template < class Matrix >
            struct NumberOfRows : std::integral_constant< int, -1 >
            {
            };

            /**
             * @brief Get number of columns for constant size matrices.
             *
             * If necessary, specialize this for your matrix class.
             */
            template < class Matrix >
            struct NumberOfColumns : std::integral_constant< int, -1 >
            {
            };

            /**
             * @brief Get transposed of constant-size matrix.
             *
             * If necessary, specialize this for your matrix class.
             */
            template < class >
            struct GetTransposed;
            /** @} */
        } // namespace detail

        /** @addtogroup ConceptGroup
         *  @{ */
        /**
         * @brief Constant-size matrix concept.
         */
        template < class V >
        concept ConstantSize = linalg::detail::NumberOfRows< V >::value > 0;

        /**
         * @brief Constant-size square matrix concept.
         */
        template < class M >
        concept SquareMatrix = ( ( linalg::detail::NumberOfRows< M >::value ==
                                   linalg::detail::NumberOfColumns< M >::value ) &&
                                 ConstantSize< M > );

        /// clang-format off
        /**
         * @brief Vector concept.
         */
        template < class T >
        concept Vector = (
                             requires( T t ) { { t[ 0 ][ 0 ] }; } ||
                             requires( T t ) { { t( 0, 0 ) }; } ) &&
                         (
                             requires( T t ) { { t *= 0.0 }; } ||
                             requires( T t ) { { 0.0 * t }; } ) &&
                         std::copy_constructible< T >;

        /**
         * @brief Matrix concept.
         */
        template < class T >
        concept Matrix = (
                             requires( T t ) { { t[ 0 ] }; } || requires( T t ) { { t( 0 ) }; } ) &&
                         (
                             requires( T t ) { { t *= 0.0 }; } ||
                             requires( T t ) { { 0.0 * t }; } ) &&
                         std::copy_constructible< T >;
        /// clang-format on
        /** @} */
    } // namespace linalg
} // namespace funcy
