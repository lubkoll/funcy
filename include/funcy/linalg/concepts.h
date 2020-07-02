#pragma once

#include <funcy/util/extract_rows_and_cols.h>
#include <funcy/util/static_checks.h>
#include <funcy/util/type_traits.h>

#include <concepts>

namespace funcy
{
    template < class V >
    concept ConstantSize = linalg::NumberOfRows< V >::value > 0;

    template < class M >
    concept SquareMatrix = ( ( linalg::NumberOfRows< M >::value ==
                               linalg::NumberOfColumns< M >::value ) &&
                             ConstantSize< M > );

    template < class T >
    concept Vector = (
                         requires( T t ) { { t[ 0 ][ 0 ] }; } ||
                         requires( T t ) { { t( 0, 0 ) }; } ) &&
                     (
                         requires( T t ) { { t *= 0.0 }; } || requires( T t ) { { 0.0 * t }; } ) &&
                     std::copy_constructible< T >;

    template < class T >
    concept Matrix = (
                         requires( T t ) { { t[ 0 ] }; } || requires( T t ) { { t( 0 ) }; } ) &&
                     (
                         requires( T t ) { { t *= 0.0 }; } || requires( T t ) { { 0.0 * t }; } ) &&
                     std::copy_constructible< T >;
    /** @} */
} // namespace funcy
