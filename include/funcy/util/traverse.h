#pragma once

#include <funcy/concepts.h>

namespace funcy
{
    namespace Meta
    {
        template < class F, template < class > class Operation,
                   template < class, class > class Combine >
        struct Traverse : Operation< F >
        {
        };

        // for Finalize
        template < template < class, bool > class G, class F, bool hasVariable,
                   template < class > class Operation, template < class, class > class Combine >
        struct Traverse< G< F, hasVariable >, Operation, Combine >
            : Traverse< F, Operation, Combine >
        {
        };

        // for Scale
        template < template < class, Function > class G, class Scalar, Function F,
                   template < class > class Operation, template < class, class > class Combine >
        struct Traverse< G< Scalar, F >, Operation, Combine > : Traverse< F, Operation, Combine >
        {
        };

        // for Squared
        template < template < Function > class G, Function F, template < class > class Operation,
                   template < class, class > class Combine >
        struct Traverse< G< F >, Operation, Combine > : Traverse< F, Operation, Combine >
        {
        };

        // For Sum, Product, Chain
        template < template < Function, Function > class H, Function F, Function G,
                   template < class > class Operation, template < class, class > class Combine >
        struct Traverse< H< F, G >, Operation, Combine >
            : Combine< Traverse< F, Operation, Combine >, Traverse< G, Operation, Combine > >
        {
        };

        template < class F, class G >
        using And = std::integral_constant< bool, F::value && G::value >;

        template < class F, class G >
        using Or = std::integral_constant< bool, F::value || G::value >;

        template < class F, template < class > class Operation >
        using AllOf = Traverse< F, Operation, And >;

        template < class F, template < class > class Operation >
        using AnyOf = Traverse< F, Operation, Or >;
    } // namespace Meta
} // namespace funcy
