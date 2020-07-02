#pragma once

#include "operations.h"

#include <funcy/util/static_checks.h>

#include <iostream>
#include <texy/constant.h>
#include <type_traits>

namespace texy
{
    /// @cond
    namespace GenerateDetail
    {
        template < class F0, class G0,
                   bool = funcy::static_check::isFunction< std::decay_t< F0 > >(),
                   bool = funcy::static_check::isFunction< std::decay_t< G0 > >() >
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
            template < class F, class G,
                       std::enable_if_t< std::is_arithmetic< G >::value >* = nullptr >
            static auto apply( F&& f, G g )
            {
                return mathop::Sum< std::decay_t< F >, Constant >(
                    std::forward< F >( f ), constant( std::to_string( g ) ) );
            }

            template < class F >
            static auto apply( F&& f, const std::string& g )
            {
                return mathop::Sum< std::decay_t< F >, Constant >( std::forward< F >( f ),
                                                                   constant( g ) );
            }
        };

        template < class F0, class G0 >
        struct SumGenerator< F0, G0, false, true >
        {
            template < class F, class G,
                       std::enable_if_t< std::is_arithmetic< F >::value >* = nullptr >
            static auto apply( F f, G&& g )
            {
                return mathop::Sum< Constant, std::decay_t< G > >( constant( std::to_string( f ) ),
                                                                   std::forward< G >( g ) );
            }

            template < class G >
            static auto apply( const std::string& f, G&& g )
            {
                return mathop::Sum< Constant, std::decay_t< G > >( constant( f ),
                                                                   std::forward< G >( g ) );
            }
        };

        template < class F0, class G0,
                   bool = funcy::static_check::isFunction< std::decay_t< F0 > >(),
                   bool = funcy::static_check::isFunction< std::decay_t< G0 > >(),
                   bool = funcy::is_arithmetic< std::decay_t< F0 > >::value,
                   bool = funcy::is_arithmetic< std::decay_t< G0 > >::value >
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
            template < class G >
            static auto apply( const std::string& f, G&& g )
            {
                return mathop::Product< Constant, std::decay_t< G > >( Constant( f ),
                                                                       std::forward< G >( g ) );
            }
        };

        template < class F0, class G0 >
        struct ProductGenerator< F0, G0, true, false, false, false >
        {
            template < class F >
            static auto apply( F&& f, const std::string& g )
            {
                return mathop::Product< std::decay_t< F >, Constant >( std::forward< F >( f ),
                                                                       Constant( g ) );
            }
        };

        template < class F0, class G0,
                   bool = funcy::static_check::isFunction< std::decay_t< F0 > >(),
                   bool = funcy::static_check::isFunction< std::decay_t< G0 > >() >
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
            template < class G >
            static auto apply( const std::string& f, G&& g )
            {
                return mathop::Dot< Constant, std::decay_t< G > >( Constant( f ),
                                                                   std::forward< G >( g ) );
            }
        };

        template < class F0, class G0 >
        struct DotGenerator< F0, G0, true, false >
        {
            template < class F >
            static auto apply( F&& f, const std::string& g )
            {
                return mathop::Dot< std::decay_t< F >, Constant >( std::forward< F >( f ),
                                                                   Constant( g ) );
            }
        };
    } // namespace GenerateDetail
    /// @endcond

    /**
     * @brief overload of "+"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than
     * you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template <
        class F, class G,
        std::enable_if_t< funcy::static_check::isFunction< std::decay_t< F > >() ||
                          funcy::static_check::isFunction< std::decay_t< G > >() >* = nullptr >
    auto operator+( F&& f, G&& g )
    {
        return Generatedetail::SumGenerator< F, G >::apply( std::forward< F >( f ),
                                                            std::forward< G >( g ) );
    }

    /**
     * @brief overload of "*"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than
     * you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template <
        class F, class G,
        std::enable_if_t< funcy::static_check::isFunction< std::decay_t< F > >() ||
                          funcy::static_check::isFunction< std::decay_t< G > >() >* = nullptr >
    auto operator*( F&& f, G&& g )
    {
        return Generatedetail::ProductGenerator< std::decay_t< F >, std::decay_t< G > >::apply(
            std::forward< F >( f ), std::forward< G >( g ) );
    }

    /**
     * @brief overload of "dot"-function for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than
     * you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template <
        class F, class G,
        std::enable_if_t< funcy::static_check::isFunction< std::decay_t< F > >() ||
                          funcy::static_check::isFunction< std::decay_t< G > >() >* = nullptr >
    auto dot( F&& f, G&& g )
    {
        return Generatedetail::DotGenerator< F, G >::apply( std::forward< F >( f ),
                                                            std::forward< G >( g ) );
    }

    /**
     * @brief overload of "^"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than
     * you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, std::enable_if_t<
                            funcy::static_check::isFunction< std::decay_t< F > >() >* = nullptr >
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
     * @brief Generate squared function
     *
     * If the resulting type represents a polynomial of order smaller than two, than
     * you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, std::enable_if_t<
                            funcy::static_check::isFunction< std::decay_t< F > >() >* = nullptr >
    auto squared( F&& f )
    {
        return mathop::Squared< std::decay_t< F > >( std::forward< F >( f ) );
    }

    //    /**
    //     * @brief overload of "<<"-operator for chaining functions \f$f\f$ and
    //     \f$g\f$ to \f$ f
    //     \circ g
    //     * \f$.
    //     *
    //     * If the resulting type represents a polynomial of order smaller than
    //     two, than you need
    //     to
    //     * wrap it into Finalize to generate missing derivatives.
    //     */

    //    template < class F, class G,
    //               std::enable_if_t< funcy::static_check::isFunction< std::decay_t< F >
    //               >() &&
    //                                 funcy::static_check::isFunction< std::decay_t< G >
    //                                 >() >* = nullptr
    //                                 >
    //    auto operator<<( F&& f, G&& g )
    //    {
    //        static_assert( !static_check::has::variable< std::decay_t< F > >(),
    //                       "Independent variables can not be on the left side of
    //                       the chain
    //                       operator." );
    //        return mathop::Chain< std::decay_t< F >, std::decay_t<
    //        G > >(
    //            std::forward< F >( f ), std::forward< G >( g ) );
    //    }

    //    /**
    //     * @brief overload of "-"-operator for the generation of functions.
    //     *
    //     * If the resulting type represents a polynomial of order smaller than
    //     two, than you need
    //     to
    //     * wrap it into Finalize to generate missing derivatives.
    //     */
    //    template < class F, class G,
    //               std::enable_if_t< funcy::static_check::isFunction< std::decay_t< F >
    //               >() ||
    //                                 funcy::static_check::isFunction< std::decay_t< G >
    //                                 >() >* = nullptr
    //                                 >
    //    auto operator-( F&& f, G&& g )
    //    {
    //        return std::forward< F >( f ) + ( -1 * std::forward< G >( g ) );
    //    }

    /**
     * @brief overload of "-"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than
     * you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, class G,
               std::enable_if_t< funcy::static_check::isFunction< std::decay_t< F > >() &&
                                 funcy::is_arithmetic< G >::value >* = nullptr >
    auto operator-( F&& f, G g )
    {
        return std::forward< F >( f ) + constant( std::to_string( -1 * g ) );
    }

    /**
     * @brief overload of "-"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than
     * you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, std::enable_if_t<
                            funcy::static_check::isFunction< std::decay_t< F > >() >* = nullptr >
    auto operator-( F&& f, const std::string& g )
    {
        return std::forward< F >( f ) + ( -1 * constant( g ) );
    }
} // namespace texy
