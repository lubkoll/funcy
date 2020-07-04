#pragma once

#include <funcy/concepts.h>
#include <funcy/util/chainer.h>
#include <funcy/util/compute_product.h>
#include <funcy/util/compute_sum.h>
#include <funcy/util/derivative_wrappers.h>
#include <funcy/util/evaluate_if_present.h>
#include <funcy/util/mathop_traits.h>
#include <funcy/util/type_traits.h>

#include <type_traits>
#include <utility>

namespace funcy
{
    namespace mathop
    {
        /**
         * @ingroup MathematicalOperationsGroup
         * @brief %Squared function \f$f^2\f$.
         */
        template < Function F >
        struct Squared : Chainer< Squared< F > >
        {
        private:
            template < class IndexedArgX, class IndexedArgY >
            using D2Sum =
                ComputeSum< ComputeProduct< D0< F >, D2< F, IndexedArgX, IndexedArgY > >,
                            ComputeProduct< D1< F, IndexedArgY >, D1< F, IndexedArgX > > >;

            template < class IndexedArgX, class IndexedArgY, class IndexedArgZ >
            using D3Sum = ComputeSum<
                ComputeProduct< D0< F >, D3< F, IndexedArgX, IndexedArgY, IndexedArgZ > >,
                ComputeProduct< D1< F, IndexedArgZ >, D2< F, IndexedArgX, IndexedArgY > >,
                ComputeProduct< D1< F, IndexedArgY >, D2< F, IndexedArgX, IndexedArgZ > >,
                ComputeProduct< D2< F, IndexedArgY, IndexedArgZ >, D1< F, IndexedArgX > > >;

        public:
            /**
             * @brief Constructor
             * @param f_ initializer for F
             */
            constexpr Squared( F&& f_ )
                : f( std::move( f_ ) ), value( multiply_via_traits( f(), f() ) )
            {
            }
            /**
             * @brief Constructor
             * @param f_ initializer for F
             */
            constexpr Squared( const F& f_ ) : f( f_ ), value( multiply_via_traits( f(), f() ) )
            {
            }

            /**
             * @brief Constructor
             * @param f_ initializer for F
             */
            template < class InitF,
                       std::enable_if_t< !std::is_same< std::decay_t< InitF >, Squared >::value >* =
                           nullptr >
            constexpr Squared(
                InitF&& f_ ) requires std::is_constructible_v< F, std::decay_t< InitF > >
                : f( std::forward< InitF >( f_ ) ), value( multiply_via_traits( f(), f() ) )
            {
            }

            /// Update point of evaluation.
            template < class Arg >
            void update( Arg const& x )
            {
                update_if_present( f, x );
                value = multiply_via_traits( f(), f() );
            }

            /// Update variable corresponding to index.
            template < int index, class Arg >
            void update( const Arg& x )
            {
                update_if_present< index >( f, x );
                value = multiply_via_traits( f(), f() );
            }

            template < class... IndexedArgs >
            void bulk_update( IndexedArgs&&... args )
            {
                bulk_update_if_present( f, std::forward< IndexedArgs >( args )... );
                value = multiply_via_traits( f(), f() );
            }

            /// Function value.
            constexpr decltype( auto ) d0() const noexcept
            {
                return value;
            }

            /**
             * @brief First directional derivative.
             * @param dx direction for which the derivative is computed
             */
            template < int id, class Arg, class IndexedArg = IndexedType< Arg, id > >
            auto d1( Arg const& dx ) const
                requires( ComputeProduct< D0< F >, D1< F, IndexedArg > >::present )
            {
                return multiply_via_traits(
                    2, multiply_via_traits( f(), D1_< F, IndexedArg >::apply( f, dx ) ) );
            }

            /**
             * @brief Second directional derivative.
             * @param dx direction for which the derivative is computed
             * @param dy direction for which the derivative is computed
             */
            template < int idx, int idy, class ArgX, class ArgY,
                       class IndexedArgX = IndexedType< ArgX, idx >,
                       class IndexedArgY = IndexedType< ArgY, idy > >
            auto d2( ArgX const& dx, ArgY const& dy ) const
                requires( D2Sum< IndexedArgX, IndexedArgY >::present )
            {
                return multiply_via_traits(
                    2, sum( product( D0< F >( f ), D2< F, IndexedArgX, IndexedArgY >( f, dx, dy ) ),
                            product( D1< F, IndexedArgY >( f, dy ),
                                     D1< F, IndexedArgX >( f, dx ) ) )() );
            }

            /**
             * @brief Third directional derivative.
             * @param dx direction for which the derivative is computed
             * @param dy direction for which the derivative is computed
             * @param dz direction for which the derivative is computed
             */
            template < int idx, int idy, int idz, class ArgX, class ArgY, class ArgZ,
                       class IndexedArgX = IndexedType< ArgX, idx >,
                       class IndexedArgY = IndexedType< ArgY, idy >,
                       class IndexedArgZ = IndexedType< ArgZ, idz > >
            auto d3( ArgX const& dx, ArgY const& dy, ArgZ const& dz ) const
                requires( D3Sum< IndexedArgX, IndexedArgY, IndexedArgZ >::present )
            {
                return multiply_via_traits(
                    2, sum( product( D0< F >( f ), D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >(
                                                       f, dx, dy, dz ) ),
                            product( D1< F, IndexedArgZ >( f, dz ),
                                     D2< F, IndexedArgX, IndexedArgY >( f, dx, dy ) ),
                            product( D1< F, IndexedArgY >( f, dy ),
                                     D2< F, IndexedArgX, IndexedArgZ >( f, dx, dz ) ),
                            product( D2< F, IndexedArgY, IndexedArgZ >( f, dy, dz ),
                                     D1< F, IndexedArgX >( f, dx ) ) )() );
            }

        private:
            F f;
            decay_t< decltype(
                multiply_via_traits( std::declval< F >()(), std::declval< F >()() ) ) >
                value;
        };
    } // namespace mathop
} // namespace funcy
