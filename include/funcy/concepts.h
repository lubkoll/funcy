#pragma once

#include <funcy/util/extract_rows_and_cols.h>

#include <concepts>

namespace funcy
{
    /** @addtogroup ConceptGroup
     *  @{ */
    template < class T >
    concept Function = requires( T t )
    {
        { T( t ) };
        { t() };
    };

    template < class V >
    concept VectorSupportSquareBracketAccess = requires( V v )
    {
        { v[ 0 ] };
    };

    template < class V >
    concept VectorSupportRoundBracketAccess = requires( V v )
    {
        { v( 0 ) };
    };

    template < class M >
    concept MatrixSupportSquareBracketAccess = requires( M m )
    {
        { m[ 0 ][ 0 ] };
    };

    template < class M >
    concept MatrixSupportRoundBracketAccess = requires( M m )
    {
        { m( 0, 0 ) };
    };

    template < class V >
    concept ConstantSize = linalg::NumberOfRows< V >::value > 0;

    template < class M >
    concept SquareMatrix =
        linalg::NumberOfRows< M >::value ==
        linalg::NumberOfColumns< M >::value&& linalg::NumberOfRows< M >::value > 0;

    /** @} */
} // namespace funcy
