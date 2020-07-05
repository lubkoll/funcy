#pragma once

#include <funcy/util/type_traits.h>

namespace funcy
{
    /** @addtogroup ConceptGroup
     *  @{ */

    /**
     * @brief Function concept.
     *
     * This is the main concept of funcy.
     */
    template < class T >
    concept Function = requires( T t )
    {
        { T( t ) };
        { t() };
    };

    /**
     * @brief Extensible concept for arithmetic types.
     *
     * You may extend this by registering your additional arithmetic types
     * by providing suitable overloads of funcy::is_arithmetic.
     */
    template < class T >
    concept Arithmetic = is_arithmetic< T >::value;
    /** @} */
} // namespace funcy
