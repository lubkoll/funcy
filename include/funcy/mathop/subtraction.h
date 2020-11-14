#pragma once

#include <funcy/concepts.h>
#include <funcy/util/chainer.h>
#include <funcy/util/compute_subtraction.h>
#include <funcy/util/derivative_wrappers.h>
#include <funcy/util/evaluate_if_present.h>
#include <funcy/util/mathop_traits.h>
#include <funcy/util/type_traits.h>

#include <utility>

namespace funcy::mathop
{
    /**
     * \ingroup MathematicalOperationsGroup
     * @brief %Subtraction of functions of type F and G.
     */
    template < Function F, Function G >
    struct Subtraction : Chainer< Subtraction< F, G > >
    {
        /**
         * @brief Constructor
         * @param f_ initializer for F
         * @param g_ initializer for G
         */
        constexpr Subtraction( const F& f_, const G& g_ )
            : f( f_ ), g( g_ ), value( subtract_via_traits( f(), g() ) )
        {
        }

        /**
         * @brief Constructor
         * @param f_ initializer for F
         * @param g_ initializer for G
         */
        constexpr Subtraction( F&& f_, const G& g_ )
            : f( std::move( f_ ) ), g( g_ ), value( subtract_via_traits( f(), g() ) )
        {
        }

        /**
         * @brief Constructor
         * @param f_ initializer for F
         * @param g_ initializer for G
         */
        constexpr Subtraction( const F& f_, G&& g_ )
            : f( f_ ), g( std::move( g_ ) ), value( subtract_via_traits( f(), g() ) )
        {
        }

        /**
         * @brief Constructor
         * @param f_ initializer for F
         * @param g_ initializer for G
         */
        constexpr Subtraction( F&& f_, G&& g_ )
            : f( std::move( f_ ) ), g( std::move( g_ ) ), value( subtract_via_traits( f(), g() ) )
        {
        }

        /**
         * @brief Constructor
         * @param f_ initializer for F
         * @param g_ initializer for G
         */
        template < class InitF, class InitG >
        constexpr Subtraction( InitF&& f_, InitG&& g_ ) requires(
            std::is_constructible_v< F, std::decay_t< InitF > >&&
                std::is_constructible_v< G, std::decay_t< InitG > > &&
            !Function< InitF > && !Function< InitG > )
            : f( std::forward< InitF >( f_ ) ), g( std::forward< InitG >( g_ ) ),
              value( subtract_via_traits( f(), g() ) )
        {
        }

        /// Update point of evaluation.
        template < class Arg >
        void update( Arg&& x )
        {
            update_if_present( f, x );
            update_if_present( g, std::forward< Arg >( x ) );
            value = subtract_via_traits( f(), g() );
        }

        /// Update variable corresponding to index.
        template < int index, class Arg >
        void update( Arg&& x )
        {
            update_if_present< index >( f, x );
            update_if_present< index >( g, std::forward< Arg >( x ) );
            value = subtract_via_traits( f(), g() );
        }

        template < class... IndexedArgs >
        void bulk_update( IndexedArgs&&... args )
        {
            bulk_update_if_present( f, args... );
            bulk_update_if_present( g, std::forward< IndexedArgs >( args )... );
            value = subtract_via_traits( f(), g() );
        }

        /// Function value.
        constexpr decltype( auto ) d0() const noexcept
        {
            return value;
        }

        /// First directional derivative.
        template < int id, class Arg, class IndexedArg = IndexedType< std::decay_t< Arg >, id > >
        auto d1( Arg&& dx ) const
            requires( ComputeSubtraction< D1< F, IndexedArg >, D1< G, IndexedArg > >::present )
        {
            return ComputeSubtraction< D1< F, IndexedArg >, D1< G, IndexedArg > >(
                f, g, std::forward< Arg >( dx ) )();
        }

        /// Second directional derivative.
        template < int idx, int idy, class ArgX, class ArgY,
                   class IndexedArgX = IndexedType< std::decay_t< ArgX >, idx >,
                   class IndexedArgY = IndexedType< std::decay_t< ArgY >, idy > >
        auto d2( ArgX&& dx, ArgY&& dy ) const
            requires( ComputeSubtraction< D2< F, IndexedArgX, IndexedArgY >,
                                          D2< G, IndexedArgX, IndexedArgY > >::present )
        {
            return ComputeSubtraction< D2< F, IndexedArgX, IndexedArgY >,
                                       D2< G, IndexedArgX, IndexedArgY > >(
                f, g, std::forward< ArgX >( dx ), std::forward< ArgY >( dy ) )();
        }

        /// Third directional derivative.
        template < int idx, int idy, int idz, class ArgX, class ArgY, class ArgZ,
                   class IndexedArgX = IndexedType< std::decay_t< ArgX >, idx >,
                   class IndexedArgY = IndexedType< std::decay_t< ArgY >, idy >,
                   class IndexedArgZ = IndexedType< std::decay_t< ArgZ >, idz > >
        auto d3( ArgX&& dx, ArgY&& dy, ArgZ&& dz ) const requires(
            ComputeSubtraction< D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >,
                                D3< G, IndexedArgX, IndexedArgY, IndexedArgZ > >::present )
        {
            return ComputeSubtraction< D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >,
                                       D3< G, IndexedArgX, IndexedArgY, IndexedArgZ > >(
                f, g, std::forward< ArgX >( dx ), std::forward< ArgY >( dy ),
                std::forward< ArgZ >( dz ) )();
        }

    private:
        F f;
        G g;
        decay_t< decltype( subtract_via_traits( std::declval< F >()(), std::declval< G >()() ) ) >
            value;
    };
} // namespace funcy::mathop
