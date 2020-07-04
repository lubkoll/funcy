#pragma once

#include <funcy/concepts.h>
#include <funcy/constant.h>
#include <funcy/operations.h>
#include <funcy/util/add_missing_operators.h>
#include <funcy/variable.h>

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
        return mathop::Dot( std::forward< F >( f ), std::forward< G >( g ) );
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
        return mathop::Dot( constant( std::forward< F >( f ) ), std::forward< G >( g ) );
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
        return mathop::Dot( std::forward< F >( f ), constant( std::forward< G >( g ) ) );
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
    template < class F, class G >
    auto operator-( F&& f, G&& g ) requires( Function< F > || Function< G > )
    {
        return std::forward< F >( f ) + ( -1 * std::forward< G >( g ) );
    }
} // namespace funcy
