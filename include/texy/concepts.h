#pragma once

#include <funcy/concepts.h>

namespace texy
{
    /** @addtogroup ConceptGroup
     *  @{ */
    template < class T >
    concept Function = funcy::Function< T >;

    template < class T >
    concept Arithmetic = funcy::Arithmetic< T >;
    /** @} */
} // namespace texy
