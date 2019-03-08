#pragma once

#include <funcy/generate.hh>
#include <funcy/util/static_checks.hh>
#include <type_traits>

namespace texy
{
    using funcy::operator+;
    using funcy::operator-;
    using funcy::operator*;
    using funcy::operator<<;
    using funcy::dot;
    using funcy::squared;
    //    /**
    //     * \brief overload of "+"-operator for the generation of functions.
    //     *
    //     * If the resulting type represents a polynomial of order smaller than two, than you need
    //     to
    //     * wrap it into Finalize to generate missing derivatives.
    //     */
    //    template < class F, class G,
    //               std::enable_if_t< funcy::funcy::Checks::isFunction< std::decay_t< F > >() ||
    //                                 funcy::funcy::Checks::isFunction< std::decay_t< G > >() >* =
    //                                 nullptr >
    //    auto operator+( F&& f, G&& g )
    //    {
    //        return funcy::operator+(std::forward<F>(f), std::forward<G>(g));
    //    }

    //    /**
    //     * \brief overload of "*"-operator for the generation of functions.
    //     *
    //     * If the resulting type represents a polynomial of order smaller than two, than you need
    //     to
    //     * wrap it into Finalize to generate missing derivatives.
    //     */
    //    template < class F, class G,
    //               std::enable_if_t< funcy::funcy::Checks::isFunction< std::decay_t< F > >() ||
    //                                 funcy::funcy::Checks::isFunction< std::decay_t< G > >() >* =
    //                                 nullptr >
    //    auto operator*( F&& f, G&& g )
    //    {
    //        return funcy::operator*(std::forward<F>(f), std::forward<G>(g));
    //    }

    //    /**
    //     * \brief overload of "dot"-function for the generation of functions.
    //     *
    //     * If the resulting type represents a polynomial of order smaller than two, than you need
    //     to
    //     * wrap it into Finalize to generate missing derivatives.
    //     */
    //    template < class F, class G,
    //               std::enable_if_t< funcy::funcy::Checks::isFunction< std::decay_t< F > >() ||
    //                                 funcy::funcy::Checks::isFunction< std::decay_t< G > >() >* =
    //                                 nullptr >
    //    auto dot( F&& f, G&& g )
    //    {
    //        return funcy::dot(std::forward<F>(f), std::forward<G>(g));    }

    //    /**
    //     * \brief Generate squared function
    //     *
    //     * If the resulting type represents a polynomial of order smaller than two, than you need
    //     to
    //     * wrap it into Finalize to generate missing derivatives.
    //     */
    //    template < class F, std::enable_if_t< funcy::funcy::Checks::isFunction< std::decay_t< F >
    //    >() >* = nullptr >
    //    auto squared( F&& f )
    //    {
    //        return funcy::squared(std::forward<F>(f), std::forward<G>(g));
    //    }

    //    /**
    //     * \brief overload of "<<"-operator for chaining functions \f$f\f$ and \f$g\f$ to \f$ f
    //     \circ g
    //     * \f$.
    //     *
    //     * If the resulting type represents a polynomial of order smaller than two, than you need
    //     to
    //     * wrap it into Finalize to generate missing derivatives.
    //     */

    //    template < class F, class G,
    //               std::enable_if_t< funcy::funcy::Checks::isFunction< std::decay_t< F > >() &&
    //                                 funcy::funcy::Checks::isFunction< std::decay_t< G > >() >* =
    //                                 nullptr >
    //    auto operator<<( F&& f, G&& g )
    //    {
    //        return funcy::operator<<(std::forward<F>(f), std::forward<G>(g));
    //    }

    //    /**
    //     * \brief overload of "-"-operator for the generation of functions.
    //     *
    //     * If the resulting type represents a polynomial of order smaller than two, than you need
    //     to
    //     * wrap it into Finalize to generate missing derivatives.
    //     */
    //    template < class F, class G,
    //               std::enable_if_t< funcy::funcy::Checks::isFunction< std::decay_t< F > >() ||
    //                                 funcy::funcy::Checks::isFunction< std::decay_t< G > >() >* =
    //                                 nullptr >
    //    auto operator-( F&& f, G&& g )
    //    {
    //        return funcy::operator-(std::forward<F>(f), std::forward<G>(g));
    //    }
}
