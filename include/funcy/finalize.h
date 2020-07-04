#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/type_traits.h>
#include <funcy/util/derivative_wrappers.h>
#include <funcy/util/indexed_type.h>
#include <funcy/util/macros.h>
#include <funcy/util/static_checks.h>
#include <funcy/util/type_traits.h>
#include <funcy/variable.h>

#include <type_traits>
#include <utility>

namespace funcy
{
    /// @cond
    namespace detail
    {
        template < class ReturnT >
        struct FillDefault
        {
            template < class... Args >
            FUNCY_ALWAYS_INLINE ReturnT operator()( const Args&... ) const
            {
                return zero< ReturnT >();
            }
        };

        template < int id, class ReturnT, bool present >
        struct FinalizeD1 : FillDefault< ReturnT >
        {
        };

        template < int id, class ReturnT >
        struct FinalizeD1< id, ReturnT, true >
        {
            template < class F, class Arg >
            FUNCY_ALWAYS_INLINE ReturnT operator()( const F& f, const Arg& dx ) const
            {
                return D1_< F, IndexedType< Arg, id > >::apply( f, dx );
            }
        };

        template < int idx, int idy, class ReturnT, bool present >
        struct FinalizeD2 : FillDefault< ReturnT >
        {
        };

        template < int idx, int idy, class ReturnT >
        struct FinalizeD2< idx, idy, ReturnT, true >
        {
            template < class F, class ArgX, class ArgY >
            FUNCY_ALWAYS_INLINE ReturnT operator()( const F& f, const ArgX& dx,
                                                    const ArgY& dy ) const
            {
                return D2_< F, IndexedType< ArgX, idx >, IndexedType< ArgY, idy > >::apply( f, dx,
                                                                                            dy );
            }
        };

        template < int idx, int idy, int idz, class ReturnT, bool present >
        struct FinalizeD3 : FillDefault< ReturnT >
        {
        };

        template < int idx, int idy, int idz, class ReturnT >
        struct FinalizeD3< idx, idy, idz, ReturnT, true >
        {
            template < class F, class ArgX, class ArgY, class ArgZ >
            FUNCY_ALWAYS_INLINE ReturnT operator()( const F& f, const ArgX& dx, const ArgY& dy,
                                                    const ArgZ& dz ) const
            {
                return D3_< F, IndexedType< ArgX, idx >, IndexedType< ArgY, idy >,
                            IndexedType< ArgZ, idz > >::apply( f, dx, dy, dz );
            }
        };

        /// Finish function definition. The task of this class is to add undefined higher order
        /// derivatives if undefined.
        template < class F >
        struct Finalize : F
        {
            using ReturnT = std::decay_t< decltype( std::declval< F >()() ) >;

            Finalize( F&& f ) : F( std::move( f ) )
            {
            }

            Finalize( const F& f ) : F( f )
            {
            }

            decltype( auto ) operator()() const
            {
                return F::operator()();
            }

            template < int id, class Arg >
            ReturnT d1( const Arg& dx ) const
                requires( static_check::has::variableId< F, id >() &&
                          static_check::checkArgument< F, Arg, id >() )
            {
                return FinalizeD1<
                    id, ReturnT,
                    static_check::has::mem_fn::d1< F, IndexedType< Arg, id > >::value >()(
                    static_cast< const F& >( *this ), dx );
            }

            template < int id >
            ReturnT d1() const requires( static_check::has::variableId< F, id >() &&
                                         is_arithmetic< Variable_t< F, id > >::value )
            {
                using Arg = Variable_t< F, id >;
                return FinalizeD1<
                    id, ReturnT,
                    static_check::has::mem_fn::d1< F, IndexedType< Arg, id > >::value >()(
                    static_cast< const F& >( *this ), Arg( 1 ) );
            }

            template < int idx, int idy, class ArgX, class ArgY >
            ReturnT d2( const ArgX& dx, const ArgY& dy ) const
                requires( static_check::has::variableId< F, idx >() &&
                          static_check::has::variableId< F, idy >() &&
                          static_check::checkArgument< F, ArgX, idx >() &&
                          static_check::checkArgument< F, ArgY, idy >() )
            {
                return FinalizeD2<
                    idx, idy, ReturnT,
                    static_check::has::mem_fn::d2< F, IndexedType< ArgX, idx >,
                                                   IndexedType< ArgY, idy > >::value >()(
                    static_cast< const F& >( *this ), dx, dy );
            }

            template < int idx, int idy >
            ReturnT d2() const requires( static_check::has::variableId< F, idx >() &&
                                         static_check::has::variableId< F, idy >() &&
                                         is_arithmetic< Variable_t< F, idx > >::value &&
                                         is_arithmetic< Variable_t< F, idy > >::value )
            {
                using ArgX = Variable_t< F, idx >;
                using ArgY = Variable_t< F, idy >;
                return FinalizeD2<
                    idx, idy, ReturnT,
                    static_check::has::mem_fn::d2< F, IndexedType< ArgX, idx >,
                                                   IndexedType< ArgY, idy > >::value >()(
                    static_cast< const F& >( *this ), ArgX( 1 ), ArgY( 1 ) );
            }

            template < int idx, int idy, int idz, class ArgX, class ArgY, class ArgZ >
            ReturnT d3( const ArgX& dx, const ArgY& dy, const ArgZ& dz ) const
                requires( static_check::has::variableId< F, idx >() &&
                          static_check::has::variableId< F, idy >() &&
                          static_check::has::variableId< F, idz >() &&
                          static_check::checkArgument< F, ArgX, idx >() &&
                          static_check::checkArgument< F, ArgY, idy >() &&
                          static_check::checkArgument< F, ArgZ, idz >() )
            {
                return FinalizeD3< idx, idy, idz, ReturnT,
                                   static_check::has::mem_fn::d3<
                                       F, IndexedType< ArgX, idx >, IndexedType< ArgY, idy >,
                                       IndexedType< ArgZ, idz > >::value >()(
                    static_cast< const F& >( *this ), dx, dy, dz );
            }

            template < int idx, int idy, int idz >
            ReturnT d3() const requires( static_check::has::variableId< F, idx >() &&
                                         static_check::has::variableId< F, idy >() &&
                                         static_check::has::variableId< F, idz >() &&
                                         is_arithmetic< Variable_t< F, idx > >::value &&
                                         is_arithmetic< Variable_t< F, idy > >::value &&
                                         is_arithmetic< Variable_t< F, idz > >::value )
            {
                using ArgX = Variable_t< F, idx >;
                using ArgY = Variable_t< F, idy >;
                using ArgZ = Variable_t< F, idz >;
                return FinalizeD3< idx, idy, idz, ReturnT,
                                   static_check::has::mem_fn::d3<
                                       F, IndexedType< ArgX, idx >, IndexedType< ArgY, idy >,
                                       IndexedType< ArgZ, idz > >::value >()(
                    static_cast< const F& >( *this ), ArgX( 1 ), ArgY( 1 ), ArgZ( 1 ) );
            }
        };

        template < class F >
        struct FinalizeSimple : F
        {
            using ReturnT = std::decay_t< decltype( std::declval< F >()() ) >;

            FinalizeSimple( F&& f ) : F( std::move( f ) )
            {
            }

            FinalizeSimple( const F& f ) : F( f )
            {
            }

            decltype( auto ) operator()() const
            {
                return F::operator()();
            }

            template < class Arg >
            decltype( auto ) operator()( Arg&& x ) const
            {
                F::update( std::forward< Arg >( x ) );
                return F::operator()();
            }

            template < class Arg >
            ReturnT d1( const Arg& dx ) const
            {
                return FinalizeD1<
                    -1, ReturnT,
                    static_check::has::mem_fn::d1< F, IndexedType< Arg, -1 > >::value >()(
                    static_cast< const F& >( *this ), dx );
            }

            template < class ArgX, class ArgY >
            ReturnT d2( const ArgX& dx, const ArgY& dy ) const
            {
                return FinalizeD2<
                    -1, -1, ReturnT,
                    static_check::has::mem_fn::d2< F, IndexedType< ArgX, -1 >,
                                                   IndexedType< ArgY, -1 > >::value >()(
                    static_cast< const F& >( *this ), dx, dy );
            }

            template < class ArgX, class ArgY, class ArgZ >
            ReturnT d3( const ArgX& dx, const ArgY& dy, const ArgZ& dz ) const
            {
                return FinalizeD3< -1, -1, -1, ReturnT,
                                   static_check::has::mem_fn::d3<
                                       F, IndexedType< ArgX, -1 >, IndexedType< ArgY, -1 >,
                                       IndexedType< ArgZ, -1 > >::value >()(
                    static_cast< const F& >( *this ), dx, dy, dz );
            }
        };
    } // namespace detail
    /// @endcond

    /**
     * @brief Finish function definition.
     *
     * Adds the definition of possibly undefined vanishing higher order derivatives.
     * If the template class Variable is not used, then no ids must be provided for the
     * update-function and derivatives.
     */
    template < Function F >
    auto finalize( F&& f ) requires( static_check::has::variable< std::decay_t< F > >() )
    {
        return detail::Finalize( std::forward< F >( f ) );
    }

    /**
     * @brief Finish function definition.
     *
     * Adds the definition of possibly undefined vanishing higher order derivatives.
     * If the template class Variable is not used, then no ids must be provided for the
     * update-function and derivatives.
     */
    template < Function F >
    auto finalize( F&& f ) requires( !static_check::has::variable< std::decay_t< F > >() )
    {
        return detail::FinalizeSimple( std::forward< F >( f ) );
    }
} // namespace funcy
