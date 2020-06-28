#pragma once

#include <funcy/concepts.h>
#include <funcy/constant.h>
#include <funcy/operations.h>
#include <funcy/util/add_missing_operators.h>
#include <funcy/util/static_checks.h>
#include <funcy/util/type_traits.h>
#include <funcy/variable.h>
#include <iostream>
#include <type_traits>

namespace funcy
{
    /// @cond
    namespace GenerateDetail
    {
        template < class F0, class G0, bool = Concepts::isFunction< std::decay_t< F0 > >(),
                   bool = Concepts::isFunction< std::decay_t< G0 > >() >
        struct SumGenerator;

        template < class F0, class G0 >
        struct SumGenerator< F0, G0, true, true >
        {
            template < class F, class G >
            static auto apply( F&& f, G&& g )
            {
                return mathop::Sum< std::decay_t< F >, std::decay_t< G > >(
                    std::forward< F >( f ), std::forward< G >( g ) );
            }
        };

        template < class F0, class G0 >
        struct SumGenerator< F0, G0, true, false >
        {
            template < class F, class G >
            static auto apply( F&& f, G&& g )
            {
                return mathop::Sum< std::decay_t< F >, Constant< std::decay_t< G > > >(
                    std::forward< F >( f ), constant( std::forward< G >( g ) ) );
            }
        };

        template < class F0, class G0 >
        struct SumGenerator< F0, G0, false, true >
        {
            template < class F, class G >
            static auto apply( F&& f, G&& g )
            {
                return mathop::Sum< Constant< std::decay_t< F > >, std::decay_t< G > >(
                    constant( std::forward< F >( f ) ), std::forward< G >( g ) );
            }
        };

        template < class F0, class G0, bool = Concepts::isFunction< std::decay_t< F0 > >(),
                   bool = Concepts::isFunction< std::decay_t< G0 > >(),
                   bool = is_arithmetic< std::decay_t< F0 > >::value,
                   bool = is_arithmetic< std::decay_t< G0 > >::value >
        struct ProductGenerator;

        template < class F0, class G0 >
        struct ProductGenerator< F0, G0, true, true, false, false >
        {
            template < class F, class G >
            static auto apply( F&& f, G&& g )
            {
                return mathop::Product< std::decay_t< F >, std::decay_t< G > >(
                    std::forward< F >( f ), std::forward< G >( g ) );
            }
        };

        template < class F0, class G0 >
        struct ProductGenerator< F0, G0, false, true, true, false >
        {
            template < class F, class G >
            static auto apply( F f, G&& g )
            {
                return mathop::Scale< F, std::decay_t< G > >( f, std::forward< G >( g ) );
            }
        };

        template < class F0, class G0 >
        struct ProductGenerator< F0, G0, true, false, false, true >
        {
            template < class F, class G >
            static auto apply( F&& f, G g )
            {
                return mathop::Scale< G, std::decay_t< F > >( g, std::forward< F >( f ) );
            }
        };

        template < class F0, class G0 >
        struct ProductGenerator< F0, G0, false, true, false, false >
        {
            template < class F, class G >
            static auto apply( F&& f, G&& g )
            {
                using Const = Constant< std::decay_t< F > >;
                return mathop::Product< Const, std::decay_t< G > >( Const( std::forward< F >( f ) ),
                                                                    std::forward< G >( g ) );
            }
        };

        template < class F0, class G0 >
        struct ProductGenerator< F0, G0, true, false, false, false >
        {
            template < class F, class G >
            static auto apply( F&& f, G&& g )
            {
                using Const = Constant< std::decay_t< G > >;
                return mathop::Product< std::decay_t< F >, Const >(
                    std::forward< F >( f ), Const( std::forward< G >( g ) ) );
            }
        };

        template < class F0, class G0, bool = Concepts::isFunction< std::decay_t< F0 > >(),
                   bool = Concepts::isFunction< std::decay_t< G0 > >() >
        struct DotGenerator;

        template < class F0, class G0 >
        struct DotGenerator< F0, G0, true, true >
        {
            template < class F, class G >
            static auto apply( F&& f, G&& g )
            {
                return mathop::Dot< std::decay_t< F >, std::decay_t< G > >(
                    std::forward< F >( f ), std::forward< G >( g ) );
            }
        };

        template < class F0, class G0 >
        struct DotGenerator< F0, G0, false, true >
        {
            template < class F, class G >
            static auto apply( F&& f, G&& g )
            {
                using Const = Constant< std::decay_t< F > >;
                return mathop::Dot< Const, std::decay_t< G > >( Const( std::forward< F >( f ) ),
                                                                std::forward< G >( g ) );
            }
        };

        template < class F0, class G0 >
        struct DotGenerator< F0, G0, true, false >
        {
            template < class F, class G >
            static auto apply( F&& f, G&& g )
            {
                using Const = Constant< std::decay_t< G > >;
                return mathop::Dot< std::decay_t< F >, Const >( std::forward< F >( f ),
                                                                Const( std::forward< G >( g ) ) );
            }
        };
    } // namespace GenerateDetail
    /// @endcond

    /**
     * \brief overload of "+"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, class G,
               std::enable_if_t< Concepts::isFunction< std::decay_t< F > >() ||
                                 Concepts::isFunction< std::decay_t< G > >() >* = nullptr >
    auto operator+( F&& f, G&& g )
    {
        return GenerateDetail::SumGenerator< F, G >::apply( std::forward< F >( f ),
                                                            std::forward< G >( g ) );
    }

    /**
     * \brief overload of "*"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, class G,
               std::enable_if_t< Concepts::isFunction< std::decay_t< F > >() ||
                                 Concepts::isFunction< std::decay_t< G > >() >* = nullptr >
    auto operator*( F&& f, G&& g )
    {
        return GenerateDetail::ProductGenerator< std::decay_t< F >, std::decay_t< G > >::apply(
            std::forward< F >( f ), std::forward< G >( g ) );
    }

    /**
     * \brief overload of "dot"-function for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, class G,
               std::enable_if_t< Concepts::isFunction< std::decay_t< F > >() ||
                                 Concepts::isFunction< std::decay_t< G > >() >* = nullptr >
    auto dot( F&& f, G&& g )
    {
        return GenerateDetail::DotGenerator< F, G >::apply( std::forward< F >( f ),
                                                            std::forward< G >( g ) );
    }

    /**
     * \brief overload of "^"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Function F >
    auto operator^( F&& f, int k )
    {
        if ( k != 2 )
        {
            std::cerr << "operator^ only defined for k=2. Terminating." << std::endl;
            exit( 1 );
        }
        return mathop::Squared< std::decay_t< F > >( std::forward< F >( f ) );
    }

    /**
     * \brief Generate squared function
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Function F >
    auto squared( F&& f )
    {
        return mathop::Squared< std::decay_t< F > >( std::forward< F >( f ) );
    }

    /**
     * \brief overload of "<<"-operator for chaining functions \f$f\f$ and \f$g\f$ to \f$ f \circ g
     * \f$.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */

    template < class F, class G,
               std::enable_if_t< Concepts::isFunction< std::decay_t< F > >() &&
                                 Concepts::isFunction< std::decay_t< G > >() >* = nullptr >
    auto operator<<( F&& f, G&& g )
    {
        static_assert( !Concepts::Has::variable< std::decay_t< F > >(),
                       "Independent variables can not be on the left side of the chain operator." );
        return mathop::Chain< std::decay_t< F >, std::decay_t< G > >( std::forward< F >( f ),
                                                                      std::forward< G >( g ) );
    }

    /**
     * \brief overload of "-"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, class G,
               std::enable_if_t< Concepts::isFunction< std::decay_t< F > >() ||
                                 Concepts::isFunction< std::decay_t< G > >() >* = nullptr >
    auto operator-( F&& f, G&& g )
    {
        return std::forward< F >( f ) + ( -1 * std::forward< G >( g ) );
    }
} // namespace funcy