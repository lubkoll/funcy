#pragma once

#include <funcy/util/type_traits.h>

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

    template < class T >
    concept Scalar = ( !Function< T > && is_arithmetic< T >::value );

    template < class T >
    concept Arithmetic = is_arithmetic< T >::value;
    /** @} */
} // namespace funcy
