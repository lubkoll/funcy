#pragma once

#include <funcy/concepts.h>
#include <funcy/util/chainer.h>
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
         * @brief Scaling \f$ af \f$ of some function \f$ f \f$ with a double \f$ a \f$.
         */
        template < class Scalar, Function F >
        struct Scale : Chainer< Scale< Scalar, F > >
        {
            /**
             * @brief Constructor passing arguments to function constructor.
             * @param a_ scaling
             * @param f_ input for constructor of outer function
             */
            constexpr Scale( Scalar a_, F&& f_ )
                : a( a_ ), f( std::move( f_ ) ), value( multiply_via_traits( a, f() ) )
            {
            }

            /**
             * @brief Constructor passing arguments to function constructor.
             * @param a_ scaling
             * @param f_ input for constructor of outer function
             */
            constexpr Scale( Scalar a_, const F& f_ )
                : a( a_ ), f( f_ ), value( multiply_via_traits( a, f() ) )
            {
            }

            /**
             * @brief Constructor passing arguments to function constructor.
             * @param a_ scaling
             * @param f_ input for constructor of outer function
             */
            template < class... InitF >
            constexpr Scale(
                Scalar a_,
                InitF&&... f_ ) requires std::is_constructible_v< F, std::decay_t< InitF >... >
                : a( a_ ),
                  f( std::forward< InitF >( f_ )... ),
                  value( multiply_via_traits( a, f() ) )
            {
            }

            /// Update point of evaluation.
            template < class Arg >
            void update( const Arg& x )
            {
                update_if_present( f, x );
                value = multiply_via_traits( a, f() );
            }

            /// Update variable corresponding to index.
            template < int index, class Arg >
            void update( const Arg& x )
            {
                update_if_present< index >( f, x );
                value = multiply_via_traits( a, f() );
            }

            template < class... IndexedArgs >
            void bulk_update( IndexedArgs&&... args )
            {
                bulk_update_if_present( f, std::forward< IndexedArgs >( args )... );
                value = multiply_via_traits( a, f() );
            }

            /// Function value.
            constexpr decltype( auto ) d0() const noexcept
            {
                return value;
            }

            /// First directional derivative.
            template < int idx, class Arg, class IndexedArg = IndexedType< Arg, idx > >
            auto d1( const Arg& dx ) const requires( D1< F, IndexedArg >::present )
            {
                return multiply_via_traits( a, D1_< F, IndexedArg >::apply( f, dx ) );
            }

            /// Second directional derivative.
            template < int idx, int idy, class ArgX, class ArgY,
                       class IndexedArgX = IndexedType< ArgX, idx >,
                       class IndexedArgY = IndexedType< ArgY, idy > >
            auto d2( const ArgX& dx, const ArgY& dy ) const
                requires( D2< F, IndexedArgX, IndexedArgY >::present )
            {
                return multiply_via_traits(
                    a, D2_< F, IndexedArgX, IndexedArgY >::apply( f, dx, dy ) );
            }

            /// Third directional derivative.
            template < int idx, int idy, int idz, class ArgX, class ArgY, class ArgZ,
                       class IndexedArgX = IndexedType< ArgX, idx >,
                       class IndexedArgY = IndexedType< ArgY, idy >,
                       class IndexedArgZ = IndexedType< ArgZ, idz > >
            auto d3( const ArgX& dx, const ArgY& dy, const ArgZ& dz ) const
                requires( D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >::present )
            {
                return multiply_via_traits(
                    a, D3_< F, IndexedArgX, IndexedArgY, IndexedArgZ >::apply( f, dx, dy, dz ) );
            }

        private:
            Scalar a = 1.;
            F f;
            std::decay_t< decltype( std::declval< F >()() ) > value;
        };
    } // namespace mathop
} // namespace funcy
