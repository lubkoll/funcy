#pragma once

#include <funcy/concepts.h>
#include <funcy/util/chainer.h>
#include <funcy/util/compute_sum.h>
#include <funcy/util/derivative_wrappers.h>
#include <funcy/util/evaluate_if_present.h>
#include <funcy/util/indexed_type.h>
#include <funcy/util/mathop_traits.h>
#include <type_traits>
#include <utility>

namespace funcy
{
    namespace mathop
    {
        /**
         * \ingroup MathematicalOperationsGroup
         * \brief %Sum of functions of type F and G (F and G must satisfy the requirements of
         * Concepts::FunctionConcept).
         */
        template < Function F, Function G >
        struct Sum : Chainer< Sum< F, G > >
        {
            /**
             * @brief Constructor
             * @param f_ initializer for F
             * @param g_ initializer for G
             */
            template < class InitF, class InitG >
            constexpr Sum( InitF&& f_, InitG&& g_ )
                : f( std::forward< InitF >( f_ ) ), g( std::forward< InitG >( g_ ) ),
                  value( add_via_traits( f(), g() ) )
            {
            }

            /// Update point of evaluation.
            template < class Arg >
            void update( Arg&& x )
            {
                update_if_present( f, x );
                update_if_present( g, std::forward< Arg >( x ) );
                value = add_via_traits( f(), g() );
            }

            /// Update variable corresponding to index.
            template < int index, class Arg >
            void update( Arg&& x )
            {
                update_if_present< index >( f, x );
                update_if_present< index >( g, std::forward< Arg >( x ) );
                value = add_via_traits( f(), g() );
            }

            template < class... IndexedArgs >
            void bulk_update( IndexedArgs&&... args )
            {
                bulk_update_if_present( f, args... );
                bulk_update_if_present( g, std::forward< IndexedArgs >( args )... );
                value = add_via_traits( f(), g() );
            }

            /// Function value.
            constexpr decltype( auto ) d0() const noexcept
            {
                return value;
            }

            /// First directional derivative.
            template < int id, class Arg, class IndexedArg = IndexedType< std::decay_t< Arg >, id >,
                       class = std::enable_if_t<
                           ComputeSum< D1< F, IndexedArg >, D1< G, IndexedArg > >::present > >
            auto d1( Arg&& dx ) const
            {
                return ComputeSum< D1< F, IndexedArg >, D1< G, IndexedArg > >(
                    f, g, std::forward< Arg >( dx ) )();
            }

            /// Second directional derivative.
            template < int idx, int idy, class ArgX, class ArgY,
                       class IndexedArgX = IndexedType< std::decay_t< ArgX >, idx >,
                       class IndexedArgY = IndexedType< std::decay_t< ArgY >, idy >,
                       class = std::enable_if_t<
                           ComputeSum< D2< F, IndexedArgX, IndexedArgY >,
                                       D2< G, IndexedArgX, IndexedArgY > >::present > >
            auto d2( ArgX&& dx, ArgY&& dy ) const
            {
                return ComputeSum< D2< F, IndexedArgX, IndexedArgY >,
                                   D2< G, IndexedArgX, IndexedArgY > >(
                    f, g, std::forward< ArgX >( dx ), std::forward< ArgY >( dy ) )();
            }

            /// Third directional derivative.
            template < int idx, int idy, int idz, class ArgX, class ArgY, class ArgZ,
                       class IndexedArgX = IndexedType< std::decay_t< ArgX >, idx >,
                       class IndexedArgY = IndexedType< std::decay_t< ArgY >, idy >,
                       class IndexedArgZ = IndexedType< std::decay_t< ArgZ >, idz >,
                       class = std::enable_if_t<
                           ComputeSum< D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >,
                                       D3< G, IndexedArgX, IndexedArgY, IndexedArgZ > >::present > >
            auto d3( ArgX&& dx, ArgY&& dy, ArgZ&& dz ) const
            {
                return ComputeSum< D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >,
                                   D3< G, IndexedArgX, IndexedArgY, IndexedArgZ > >(
                    f, g, std::forward< ArgX >( dx ), std::forward< ArgY >( dy ),
                    std::forward< ArgZ >( dz ) )();
            }

        private:
            F f;
            G g;
            decay_t< decltype( add_via_traits( std::declval< F >()(), std::declval< G >()() ) ) >
                value;
        };
    } // namespace mathop
} // namespace funcy
