#pragma once

#include <funcy/operations.h>

#include <concepts>
#include <texy/concepts.h>
#include <texy/constant.h>
#include <texy/util/string.h>
#include <texy/variable.h>
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
        using std::to_string;
        return mathop::Sum( constant( to_string( std::forward< F >( f ) ) ),
                            std::forward< G >( g ) );
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
        using std::to_string;
        return mathop::Sum( std::forward< F >( f ),
                            constant( to_string( std::forward< G >( g ) ) ) );
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
        using std::to_string;
        return mathop::Product( constant( to_string( std::forward< F >( f ) ) ),
                                std::forward< G >( g ) );
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
        using std::to_string;
        return mathop::Product( std::forward< F >( f ),
                                constant( to_string( std::forward< G >( g ) ) ) );
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
        using std::to_string;
        return mathop::Dot( constant( to_string( std::forward< F >( f ) ) ),
                            std::forward< G >( g ) );
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
        using std::to_string;
        return mathop::Dot( std::forward< F >( f ),
                            constant( to_string( std::forward< G >( g ) ) ) );
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
        using std::to_string;
        return mathop::Subtraction( constant( to_string( std::forward< F >( f ) ) ),
                                    std::forward< G >( g ) );
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
        using std::to_string;
        return mathop::Subtraction( std::forward< F >( f ),
                                    constant( to_string( std::forward< G >( g ) ) ) );
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
} // namespace funcy
