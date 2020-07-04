#pragma once

#include <funcy/concepts.h>

#include <type_traits>

namespace funcy
{
    namespace meta
    {
        template < class F, template < class > class Operation,
                   template < class... > class Combine >
        struct Traverse : Operation< F >
        {
        };

        // for Finalize
        template < template < class, bool > class G, class F, bool has_variable,
                   template < class > class Operation, template < class, class > class Combine >
        struct Traverse< G< F, has_variable >, Operation, Combine >
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

        // For Sum, Product, Chain, Min, Max
        template < template < Function, Function > class H, Function F, Function G,
                   template < class > class Operation, template < class, class > class Combine >
        struct Traverse< H< F, G >, Operation, Combine >
            : Combine< Traverse< F, Operation, Combine >, Traverse< G, Operation, Combine > >
        {
        };

        template < class F, template < class > class Operation >
        using AnyOf = Traverse< F, Operation, std::disjunction >;
    } // namespace meta
} // namespace funcy
