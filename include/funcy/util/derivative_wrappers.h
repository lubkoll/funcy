#pragma once

#include <funcy/concepts.h>
#include <funcy/util/static_checks.h>

#include <type_traits>
#include <utility>

namespace funcy
{
    /// @cond
    namespace detail
    {
        /// Don't call f.d1(dx).
        template < Function F, class IndexedArg, bool IsPresent, bool hasIndex,
                   class Arg = typename IndexedArg::type, int id = IndexedArg::index >
        struct D1Impl
        {
            static constexpr bool present = false;
            D1Impl( F const&, const Arg& )
            {
            }
            D1Impl( const D1Impl& ) = delete;
            D1Impl& operator=( const D1Impl& ) = delete;
        };

        /// Call f.d1<id>(dx).
        template < Function F, class IndexedArg, class Arg, int id >
        struct D1Impl< F, IndexedArg, true, true, Arg, id >
        {
            static constexpr bool present = true;

            D1Impl( const F& f, const Arg& dx ) : value( f.template d1< id >( dx ) )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            D1Impl( const D1Impl& ) = delete;
            D1Impl& operator=( const D1Impl& ) = delete;

        private:
            std::decay_t< decltype(
                std::declval< F >().template d1< id >( std::declval< Arg >() ) ) >
                value;
        };

        /// Call f.d1(dx).
        template < Function F, class IndexedArg, class Arg >
        struct D1Impl< F, IndexedArg, true, false, Arg, -1 >
        {
            static constexpr bool present = true;

            D1Impl( const F& f, const Arg& dx ) : value( f.d1( dx ) )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            D1Impl( const D1Impl& ) = delete;
            D1Impl& operator=( const D1Impl& ) = delete;

        private:
            std::decay_t< decltype( std::declval< F >().d1( std::declval< Arg >() ) ) > value;
        };

        /// Don't call f.d2(dx,dy).
        template < Function F, class IndexedArgX, class IndexedArgY, bool IsPresent, bool hasIndex,
                   class ArgX = typename IndexedArgX::type, class ArgY = typename IndexedArgY::type,
                   int idx = IndexedArgX::index, int idy = IndexedArgY::index >
        struct D2Impl
        {
            static constexpr bool present = false;
            D2Impl( const F&, const ArgX&, const ArgY& )
            {
            }
            D2Impl( const D2Impl& ) = delete;
            D2Impl& operator=( const D2Impl& ) = delete;
        };

        /// Call f.d2<idx,idy>(dx,dy).
        template < Function F, class IndexedArgX, class IndexedArgY, class ArgX, class ArgY,
                   int idx, int idy >
        struct D2Impl< F, IndexedArgX, IndexedArgY, true, true, ArgX, ArgY, idx, idy >
        {
            static constexpr bool present = true;

            D2Impl( const F& f, const ArgX& dx, const ArgY& dy )
                : value( f.template d2< idx, idy >( dx, dy ) )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            D2Impl( const D2Impl& ) = delete;
            D2Impl& operator=( const D2Impl& ) = delete;

        private:
            std::decay_t< decltype( std::declval< F >().template d2< idx, idy >(
                std::declval< ArgX >(), std::declval< ArgY >() ) ) >
                value;
        };

        /// Call f.d2(dx,dy).
        template < Function F, class IndexedArgX, class IndexedArgY, class ArgX, class ArgY >
        struct D2Impl< F, IndexedArgX, IndexedArgY, true, false, ArgX, ArgY, -1, -1 >
        {
            static constexpr bool present = true;

            D2Impl( const F& f, const ArgX& dx, const ArgY& dy ) : value( f.d2( dx, dy ) )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            D2Impl( const D2Impl& ) = delete;
            D2Impl& operator=( const D2Impl& ) = delete;

        private:
            std::decay_t< decltype(
                std::declval< F >().d2( std::declval< ArgX >(), std::declval< ArgY >() ) ) >
                value;
        };

        /// Don't call f.d3(dx,dy,dz).
        template < Function F, class IndexedArgX, class IndexedArgY, class IndexedArgZ,
                   bool IsPresent, bool hasIndex, class ArgX = typename IndexedArgX::type,
                   class ArgY = typename IndexedArgY::type, class ArgZ = typename IndexedArgZ::type,
                   int idx = IndexedArgX::index, int idy = IndexedArgY::index,
                   int idz = IndexedArgZ::index >
        struct D3Impl
        {
            static constexpr bool present = false;
            D3Impl( const F&, const ArgX&, const ArgY&, const ArgZ& )
            {
            }
            D3Impl( const D3Impl& ) = delete;
            D3Impl& operator=( const D3Impl& ) = delete;
        };

        /// Call f.d3<idx,idy,idz>(dx,dy,dz).
        template < Function F, class IndexedArgX, class IndexedArgY, class IndexedArgZ, class ArgX,
                   class ArgY, class ArgZ, int idx, int idy, int idz >
        struct D3Impl< F, IndexedArgX, IndexedArgY, IndexedArgZ, true, true, ArgX, ArgY, ArgZ, idx,
                       idy, idz >
        {
            static constexpr bool present = true;

            D3Impl( const F& f, const ArgX& dx, const ArgY& dy, const ArgZ& dz )
                : value( f.template d3< idx, idy, idz >( dx, dy, dz ) )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            D3Impl( const D3Impl& ) = delete;
            D3Impl& operator=( const D3Impl& ) = delete;

        private:
            std::decay_t< decltype( std::declval< F >().template d3< idx, idy, idz >(
                std::declval< ArgX >(), std::declval< ArgY >(), std::declval< ArgZ >() ) ) >
                value;
        };

        /// Call f.d3(dx,dy,dz).
        template < Function F, class IndexedArgX, class IndexedArgY, class IndexedArgZ, class ArgX,
                   class ArgY, class ArgZ >
        struct D3Impl< F, IndexedArgX, IndexedArgY, IndexedArgZ, true, false, ArgX, ArgY, ArgZ, -1,
                       -1, -1 >
        {
            static constexpr bool present = true;

            D3Impl( const F& f, const ArgX& dx, const ArgY& dy, const ArgZ& dz )
                : value( f.d3( dx, dy, dz ) )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            D3Impl( const D3Impl& ) = delete;
            D3Impl& operator=( const D3Impl& ) = delete;

        private:
            std::decay_t< decltype( std::declval< F >().d3(
                std::declval< ArgX >(), std::declval< ArgY >(), std::declval< ArgZ >() ) ) >
                value;
        };
    } // namespace detail

    /// Evaluate f().
    template < Function F >
    struct D0
    {
        static constexpr bool present = true;

        D0( const F& f ) : value( f() )
        {
        }

        decltype( auto ) operator()() const
        {
            return value;
        }

        D0( const D0& ) = delete;
        D0& operator=( const D0& ) = delete;

    private:
        decltype( std::declval< F >()() ) value;
    };

    /// Evaluates f.d1(dx) if present.
    template < Function F, class IndexedArg >
    using D1 = detail::D1Impl< F, IndexedArg, static_check::has::mem_fn::d1< F, IndexedArg >::value,
                               static_check::has::mem_fn::d1_with_index< F, IndexedArg >::value >;

    /// Evaluates f.d2(dx,dy) if present.
    template < Function F, class IndexedArgX, class IndexedArgY >
    using D2 = detail::D2Impl<
        F, IndexedArgX, IndexedArgY,
        static_check::has::mem_fn::d2< F, IndexedArgX, IndexedArgY >::value,
        static_check::has::mem_fn::d2_with_index< F, IndexedArgX, IndexedArgY >::value >;

    /// Evaluates f.d3(dx,dy,dz) if present.
    template < Function F, class IndexedArgX, class IndexedArgY, class IndexedArgZ >
    using D3 = detail::D3Impl<
        F, IndexedArgX, IndexedArgY, IndexedArgZ,
        static_check::has::mem_fn::d3< F, IndexedArgX, IndexedArgY, IndexedArgZ >::value,
        static_check::has::mem_fn::d3_with_index< F, IndexedArgX, IndexedArgY,
                                                  IndexedArgZ >::value >;

    template < Function F, class IndexedArg,
               bool has_member_function = static_check::has::mem_fn::d1< F, IndexedArg >::value,
               bool with_index = static_check::has::mem_fn::d1_with_index< F, IndexedArg >::value >
    struct D1_
    {
        static constexpr bool present = false;
        template < class Arg >
        static decltype( auto ) apply( const F&, Arg&& )
        {
        }
    };

    template < Function F, class IndexedArg >
    struct D1_< F, IndexedArg, true, true >
    {
        static constexpr bool present = true;
        template < class Arg >
        static decltype( auto ) apply( const F& f, Arg&& dx )
        {
            return f.template d1< IndexedArg::index >( std::forward< Arg >( dx ) );
        }
    };

    template < Function F, class IndexedArg >
    struct D1_< F, IndexedArg, true, false >
    {
        static constexpr bool present = true;
        template < class Arg >
        static decltype( auto ) apply( const F& f, Arg&& dx )
        {
            return f.d1( std::forward< Arg >( dx ) );
        }
    };

    template < Function F, class IndexedArgX, class IndexedArgY,
               bool has_member_function =
                   static_check::has::mem_fn::d2< F, IndexedArgX, IndexedArgY >::value,
               bool withIndex =
                   static_check::has::mem_fn::d2_with_index< F, IndexedArgX, IndexedArgY >::value >
    struct D2_
    {
        static constexpr bool present = false;
        template < class... Args >
        static decltype( auto ) apply( const F&, Args&&... )
        {
        }
    };

    template < Function F, class IndexedArgX, class IndexedArgY >
    struct D2_< F, IndexedArgX, IndexedArgY, true, true >
    {
        static constexpr bool present = true;
        template < class... Args >
        static decltype( auto ) apply( const F& f, Args&&... dx )
        {
            return f.template d2< IndexedArgX::index, IndexedArgY::index >(
                std::forward< Args >( dx )... );
        }
    };

    template < Function F, class IndexedArgX, class IndexedArgY >
    struct D2_< F, IndexedArgX, IndexedArgY, true, false >
    {
        static constexpr bool present = true;
        template < class... Args >
        static decltype( auto ) apply( const F& f, Args&&... dx )
        {
            return f.d2( std::forward< Args >( dx )... );
        }
    };

    template < Function F, class IndexedArgX, class IndexedArgY, class IndexedArgZ,
               bool has_member_function =
                   static_check::has::mem_fn::d3< F, IndexedArgX, IndexedArgY, IndexedArgZ >::value,
               bool withIndex = static_check::has::mem_fn::d3_with_index<
                   F, IndexedArgX, IndexedArgY, IndexedArgZ >::value >
    struct D3_
    {
        static constexpr bool present = false;
        template < class... Args >
        static decltype( auto ) apply( const F&, Args&&... )
        {
        }
    };

    template < Function F, class IndexedArgX, class IndexedArgY, class IndexedArgZ >
    struct D3_< F, IndexedArgX, IndexedArgY, IndexedArgZ, true, true >
    {
        static constexpr bool present = true;
        template < class... Args >
        static decltype( auto ) apply( const F& f, Args&&... dx )
        {
            return f.template d3< IndexedArgX::index, IndexedArgY::index, IndexedArgZ::index >(
                std::forward< Args >( dx )... );
        }
    };

    template < Function F, class IndexedArgX, class IndexedArgY, class IndexedArgZ >
    struct D3_< F, IndexedArgX, IndexedArgY, IndexedArgZ, true, false >
    {
        static constexpr bool present = true;
        template < class... Args >
        static decltype( auto ) apply( const F& f, Args&&... dx )
        {
            return f.d3( std::forward< Args >( dx )... );
        }
    };
    /// @endcond
} // namespace funcy
