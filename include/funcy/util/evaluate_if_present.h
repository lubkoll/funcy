#pragma once

#include <funcy/concepts.h>

#include <type_traits>
#include <utility>

namespace funcy
{
    /// @cond
    namespace detail
    {
        template < Function F, class Arg >
        using TryCallOfUpdate = decltype( std::declval< F >().update( std::declval< Arg >() ) );

        template < Function F, class Arg, int id >
        using TryCallOfUpdateWithIndex =
            decltype( std::declval< F >().template update< id >( std::declval< Arg >() ) );

        template < Function F, class Arg, class = void >
        struct HasUpdateWithoutIndex : std::false_type
        {
        };

        template < Function F, class Arg >
        struct HasUpdateWithoutIndex< F, Arg, std::void_t< TryCallOfUpdate< F, Arg > > >
            : std::true_type
        {
        };

        template < Function F, class Arg, int id, class = void >
        struct HasUpdateWithIndex : std::false_type
        {
        };

        template < Function F, class Arg, int id >
        struct HasUpdateWithIndex< F, Arg, id,
                                   std::void_t< TryCallOfUpdateWithIndex< F, Arg, id > > >
            : std::true_type
        {
        };

        template < Function F, class... IndexedArgs >
        struct BulkUpdate
        {
            static constexpr auto present = false;
        };

        template <
            Function F, class IndexedArg,
            bool = HasUpdateWithIndex< F, typename IndexedArg::type, IndexedArg::index >::value >
        struct BulkUpdateImpl
        {
            static constexpr auto present = false;

            static void apply( const F&, const IndexedArg& )
            {
            }
        };

        template < Function F, class IndexedArg >
        struct BulkUpdateImpl< F, IndexedArg, true >
        {
            static constexpr auto present = true;

            static void apply( const F& f, const IndexedArg& arg )
            {
                f.template update< IndexedArg::index >( arg.value );
            }
        };

        template < Function F, class IndexedArg >
        struct BulkUpdate< F, IndexedArg > : BulkUpdateImpl< F, std::decay_t< IndexedArg > >
        {
        };

        template < Function F, class IndexedArg, class... IndexedArgs >
        struct BulkUpdate< F, IndexedArg, IndexedArgs... >
        {
            static constexpr auto present =
                BulkUpdate< F, IndexedArg >::present && BulkUpdate< F, IndexedArgs... >::present;

            static void apply( const F& f, const IndexedArg& arg, const IndexedArgs&... args )
            {
                BulkUpdate< F, IndexedArg >::apply( f, arg );
                BulkUpdate< F, IndexedArgs... >::apply( f, args... );
            }
        };
    } // namespace detail
    /// @endcond

    template < Function F, class Arg,
               std::enable_if_t< !detail::HasUpdateWithoutIndex< F, Arg >::value >* = nullptr >
    void update_if_present( F&&, Arg&& )
    {
    }

    template < Function F, class Arg,
               std::enable_if_t< detail::HasUpdateWithoutIndex< F, Arg >::value >* = nullptr >
    void update_if_present( F&& f, Arg&& x )
    {
        f.update( std::forward< Arg >( x ) );
    }

    template < int id, Function F, class Arg,
               std::enable_if_t< !detail::HasUpdateWithIndex< F, Arg, id >::value >* = nullptr >
    void update_if_present( F&&, Arg&& )
    {
    }

    template < int id, Function F, class Arg,
               std::enable_if_t< detail::HasUpdateWithIndex< F, Arg, id >::value >* = nullptr >
    void update_if_present( F&& f, Arg&& x )
    {
        f.template update< id >( std::forward< Arg >( x ) );
    }

    template < Function F, class... IndexArgs,
               std::enable_if_t< detail::BulkUpdate< F, IndexArgs... >::present >* = nullptr >
    void bulk_update_if_present( F&& f, IndexArgs&&... x )
    {
        detail::BulkUpdate< F, IndexArgs... >::apply( std::forward< F >( f ),
                                                      std::forward< IndexArgs >( x )... );
    }
} // namespace funcy
