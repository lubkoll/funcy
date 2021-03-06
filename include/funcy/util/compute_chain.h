#pragma once

#include <funcy/util/static_checks.h>
#include <funcy/util/type_traits.h>

#include <utility>

namespace funcy
{
    /// @cond
    namespace detail
    {
        template < class F, class IndexedX, bool allPresent, bool hasIndex,
                   class X = typename IndexedX::type, int id = IndexedX::index >
        struct ComputeChainD1Impl
        {
            static constexpr bool present = false;
            ComputeChainD1Impl( const F&, const X& )
            {
            }
        };

        template < class F, class IndexedX, class IndexedY, bool allPresent, bool hasIndex,
                   class X = typename IndexedX::type, class Y = typename IndexedY::type,
                   int idx = IndexedX::index, int idy = IndexedY::index >
        struct ComputeChainD2Impl
        {
            static constexpr bool present = false;
            ComputeChainD2Impl( const F&, const X&, const Y& )
            {
            }
        };

        template < class F, class IndexedX, class IndexedY, class IndexedZ, bool allPresent,
                   bool hasIndex, class X = typename IndexedX::type,
                   class Y = typename IndexedY::type, class Z = typename IndexedZ::type,
                   int idx = IndexedX::index, int idy = IndexedY::index, int idz = IndexedZ::index >
        struct ComputeChainD3Impl
        {
            static constexpr bool present = false;
            ComputeChainD3Impl( const F&, const X&, const Y&, const Z& )
            {
            }
        };

        template < class F, class IndexedX, class X, int id >
        struct ComputeChainD1Impl< F, IndexedX, true, true, X, id >
        {
            static constexpr bool present = true;

            ComputeChainD1Impl( const F& f, const X& x ) : value( f.template d1< id >( x() ) )
            {
            }

            auto operator()() const
            {
                return value;
            }

            decltype( std::declval< F >().template d1< id >( std::declval< X >()() ) ) value;
        };

        template < class F, class IndexedX, class X, int id >
        struct ComputeChainD1Impl< F, IndexedX, true, false, X, id >
        {
            static constexpr bool present = true;

            ComputeChainD1Impl( const F& f, const X& x ) : value( f.d1( x() ) )
            {
            }

            auto operator()() const
            {
                return value;
            }

            decltype( std::declval< F >().d1( std::declval< X >()() ) ) value;
        };

        template < class F, class IndexedX, class IndexedY, class X, class Y, int idx, int idy >
        struct ComputeChainD2Impl< F, IndexedX, IndexedY, true, true, X, Y, idx, idy >
        {
            static constexpr bool present = true;

            ComputeChainD2Impl( const F& f, const X& x, const Y& y )
                : value( f.template d2< idx, idy >( x(), y() ) )
            {
            }

            auto operator()() const
            {
                return value;
            }

            decltype( std::declval< F >().template d2< idx, idy >( std::declval< X >()(),
                                                                   std::declval< Y >()() ) ) value;
        };

        template < class F, class IndexedX, class IndexedY, class X, class Y, int idx, int idy >
        struct ComputeChainD2Impl< F, IndexedX, IndexedY, true, false, X, Y, idx, idy >
        {
            static constexpr bool present = true;

            ComputeChainD2Impl( const F& f, const X& x, const Y& y ) : value( f.d2( x(), y() ) )
            {
            }

            auto operator()() const
            {
                return value;
            }

            decltype(
                std::declval< F >().d2( std::declval< X >()(), std::declval< Y >()() ) ) value;
        };

        template < class F, class IndexedX, class IndexedY, class IndexedZ, class X, class Y,
                   class Z, int idx, int idy, int idz >
        struct ComputeChainD3Impl< F, IndexedX, IndexedY, IndexedZ, true, true, X, Y, Z, idx, idy,
                                   idz >
        {
            static constexpr bool present = true;

            ComputeChainD3Impl( const F& f, const X& x, const Y& y, const Z& z )
                : value( f.template d3< idx, idy, idz >( x(), y(), z() ) )
            {
            }

            auto operator()() const
            {
                return value;
            }

            decltype( std::declval< F >().template d3< idx, idy, idz >(
                std::declval< X >()(), std::declval< Y >()(), std::declval< Z >()() ) ) value;
        };

        template < class F, class IndexedX, class IndexedY, class IndexedZ, class X, class Y,
                   class Z, int idx, int idy, int idz >
        struct ComputeChainD3Impl< F, IndexedX, IndexedY, IndexedZ, true, false, X, Y, Z, idx, idy,
                                   idz >
        {
            static constexpr bool present = true;

            ComputeChainD3Impl( const F& f, const X& x, const Y& y, const Z& z )
                : value( f.d3( x(), y(), z() ) )
            {
            }

            auto operator()() const
            {
                return value;
            }

            decltype( std::declval< F >().d3( std::declval< X >()(), std::declval< Y >()(),
                                              std::declval< Z >()() ) ) value;
        };
    } // namespace detail

    template < class F, class X, class IndexedArg,
               class IndexedX = IndexedType< X, IndexedArg::index > >
    struct ComputeChainD1
        : detail::ComputeChainD1Impl<
              F, IndexedX, static_check::has::mem_fn::d1< F, IndexedArg >::value && X::present,
              static_check::has::mem_fn::d1_with_index< F, IndexedArg >::value >
    {
        ComputeChainD1( F const& f, X const& x )
            : detail::ComputeChainD1Impl < F,
        IndexedX, static_check::has::mem_fn::d1< F, IndexedArg >::value && X::present,
        static_check::has::mem_fn::d1_with_index< F, IndexedArg >::value > ( f, x )
        {
        }
    };

    template < class IndexedArg, class F, class X >
    auto chain( const F& f, const X& x )
    {
        return ComputeChainD1< F, X, IndexedArg >( f, x );
    }

    template < class F, class X, class Y, class IndexedArgX, class IndexedArgY,
               class IndexedX = IndexedType< X, IndexedArgX::index >,
               class IndexedY = IndexedType< Y, IndexedArgY::index > >
    struct ComputeChainD2
        : detail::ComputeChainD2Impl<
              F, IndexedX, IndexedY,
              static_check::has::mem_fn::d2< F, IndexedArgX, IndexedArgY >::value && X::present &&
                  Y::present,
              static_check::has::mem_fn::d2_with_index< F, IndexedArgX, IndexedArgY >::value >
    {
        ComputeChainD2( const F& f, const X& x, const Y& y )
            : detail::ComputeChainD2Impl < F,
        IndexedX, IndexedY, static_check::has::mem_fn::d2< F, IndexedArgX, IndexedArgY >::value
                                && X::present && Y::present,
        static_check::has::mem_fn::d2_with_index< F, IndexedArgX, IndexedArgY >::value > ( f, x, y )
        {
        }
    };

    template < class IndexedArgX, class IndexedArgY, class F, class X, class Y >
    auto chain( const F& f, const X& x, const Y& y )
    {
        return ComputeChainD2< F, X, Y, IndexedArgX, IndexedArgY >( f, x, y );
    }

    template < class F, class X, class Y, class Z, class IndexedArgX, class IndexedArgY,
               class IndexedArgZ, class IndexedX = IndexedType< X, IndexedArgX::index >,
               class IndexedY = IndexedType< Y, IndexedArgY::index >,
               class IndexedZ = IndexedType< Z, IndexedArgZ::index > >
    struct ComputeChainD3
        : detail::ComputeChainD3Impl<
              F, IndexedX, IndexedY, IndexedZ,
              static_check::has::mem_fn::d3< F, IndexedArgX, IndexedArgY, IndexedArgZ >::value &&
                  X::present && Y::present && Z::present,
              static_check::has::mem_fn::d3_with_index< F, IndexedArgX, IndexedArgY,
                                                        IndexedArgZ >::value >
    {
        ComputeChainD3( const F& f, const X& x, const Y& y, const Z& z )
            : detail::ComputeChainD3Impl < F,
        IndexedX, IndexedY, IndexedZ,
        static_check::has::mem_fn::d3< F, IndexedArgX, IndexedArgY, IndexedArgZ >::value
            && X::present && Y::present && Z::present,
        static_check::has::mem_fn::d3_with_index< F, IndexedArgX, IndexedArgY, IndexedArgZ >::value
            > ( f, x, y, z )
        {
        }
    };

    template < class IndexedArgX, class IndexedArgY, class IndexedArgZ, class F, class X, class Y,
               class Z >
    auto chain( const F& f, const X& x, const Y& y, const Z& z )
    {
        return ComputeChainD3< F, X, Y, Z, IndexedArgX, IndexedArgY, IndexedArgZ >( f, x, y, z );
    }
    /// @endcond
} // namespace funcy
