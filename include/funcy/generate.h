#pragma once

#include <funcy/concepts.h>
#include <funcy/constant.h>
#include <funcy/operations.h>
#include <funcy/variable.h>

#include <concepts>
#include <type_traits>
#include <utility>

namespace funcy
{
    /**
     * @brief overload of "+"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Function F, Function G >
    auto operator+( F&& f, G&& g )
    {
        return mathop::Sum( std::forward< F >( f ), std::forward< G >( g ) );
    }

    /**
     * @brief overload of "+"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, Function G >
    auto operator+( F&& f, G&& g )
    {
        return mathop::Sum( constant( std::forward< F >( f ) ), std::forward< G >( g ) );
    }

    /**
     * @brief overload of "+"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Function F, class G >
    auto operator+( F&& f, G&& g )
    {
        return mathop::Sum( std::forward< F >( f ), constant( std::forward< G >( g ) ) );
    }

    /**
     * @brief overload of "*"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Function F, Function G >
    auto operator*( F&& f, G&& g )
    {
        return mathop::Product( std::forward< F >( f ), std::forward< G >( g ) );
    }

    /**
     * @brief overload of "*"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, Function G >
    auto operator*( F&& f, G&& g )
    {
        return mathop::Product( constant( std::forward< F >( f ) ), std::forward< G >( g ) );
    }

    /**
     * @brief overload of "*"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Arithmetic F, Function G >
    auto operator*( F&& f, G&& g )
    {
        return mathop::Scale( std::forward< F >( f ), std::forward< G >( g ) );
    }

    /**
     * @brief overload of "*"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Function F, class G >
    auto operator*( F&& f, G&& g )
    {
        return mathop::Product( std::forward< F >( f ), constant( std::forward< G >( g ) ) );
    }

    /**
     * @brief overload of "*"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Function F, Arithmetic G >
    auto operator*( F&& f, G&& g )
    {
        return mathop::Scale( std::forward< G >( g ), std::forward< F >( f ) );
    }

    /**
     * @brief overload of "dot"-function for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Function F, Function G >
    auto dot( F&& f, G&& g )
    {
        return mathop::Dot< std::decay_t< F >, std::decay_t< G > >( std::forward< F >( f ),
                                                                    std::forward< G >( g ) );
    }

    /**
     * @brief overload of "dot"-function for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, Function G >
    auto dot( F&& f, G&& g )
    {
        return mathop::Dot< std::decay_t< F >, std::decay_t< G > >(
            constant( std::forward< F >( f ) ), std::forward< G >( g ) );
    }

    /**
     * @brief overload of "dot"-function for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Function F, class G >
    auto dot( F&& f, G&& g )
    {
        return mathop::Dot< std::decay_t< F >, std::decay_t< G > >(
            std::forward< F >( f ), constant( std::forward< G >( g ) ) );
    }

    /**
     * @brief Generate squared function
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
     * @brief overload of "-"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Function F, Function G >
    auto operator-( F&& f, G&& g )
    {
        return mathop::Subtraction( std::forward< F >( f ), std::forward< G >( g ) );
    }

    /**
     * @brief overload of "-"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, Function G >
    auto operator-( F&& f, G&& g )
    {
        return mathop::Subtraction( constant( std::forward< F >( f ) ), std::forward< G >( g ) );
    }

    /**
     * @brief overload of "-"-operator for the generation of functions.
     *
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < Function F, class G >
    auto operator-( F&& f, G&& g )
    {
        return mathop::Subtraction( std::forward< F >( f ), constant( std::forward< G >( g ) ) );
    }

    /**
     * @brief overload of "/"-operator for the generation of functions.
     *
     * Only for functions that return types that are convertible to double
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, class G >
    auto operator/( F&& f, G&& g ) requires( requires( G g ) {
        {
            g()
        }
        ->std::convertible_to< double >;
    } )
    {
        return std::forward< F >( f ) * pow< -1 >( std::forward< G >( g ) );
    }

    /**
     * @brief overload of "/"-operator for the generation of functions.
     *
     * Only for functions that return types that are convertible to double
     * If the resulting type represents a polynomial of order smaller than two, than you need to
     * wrap it into Finalize to generate missing derivatives.
     */
    template < class F, Arithmetic G >
    auto operator/( F&& f, G g )
    {
        return std::forward< F >( f ) * constant( 1 / g );
    }
} // namespace funcy
