#pragma once

#include <funcy/concepts.h>

#include <type_traits>
#include <utility>

namespace funcy
{
    template < Function F, class Arg >
    void update_if_present( F&&, Arg&& )
    {
    }

    template < Function F, class Arg >
    void update_if_present( F&& f, Arg&& x ) requires requires
    {
        { f.update( std::forward< Arg >( x ) ) };
    }
    {
        f.update( std::forward< Arg >( x ) );
    }

    template < int id, Function F, class Arg >
    void update_if_present( F&&, Arg&& )
    {
    }

    template < int id, Function F, class Arg >
    void update_if_present( F&& f, Arg&& x ) requires requires
    {
        { f.template update< id >( std::forward< Arg >( x ) ) };
    }
    {
        f.template update< id >( std::forward< Arg >( x ) );
    }

    template < Function F, class... IndexedArgs >
    void bulk_update_if_present( F&&, IndexedArgs&&... )
    {
    }

    template < Function F, class IndexedArg, class... IndexedArgs >
    void bulk_update_if_present( F&& f, IndexedArg&& x0, IndexedArgs&&... x )
    {
        using IArg = std::decay_t< IndexedArg >;
        update_if_present< IArg::index >( std::forward< F >( f ),
                                          std::forward< typename IArg::type >( x0.value ) );
        if constexpr ( sizeof...( x ) > 0 )
        {
            bulk_update_if_present( f, std::forward< IndexedArgs >( x )... );
        }
    }
} // namespace funcy
