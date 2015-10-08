// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef FUNG_UTIL_STATIC_CHECKS_NROWS_NCOLS_HH
#define FUNG_UTIL_STATIC_CHECKS_NROWS_NCOLS_HH

#include <utility>
#include "voider.hh"

namespace FunG
{
  namespace Checks
  {
    /**
     * \cond DOCUMENT_IMPLEMENTATION_DETAILS
     */
    // check functions for accessing the number of rows and columns in a dynamic matrix
    template < class Matrix >
    using TryCallOfRowsForMatrix = decltype(std::declval<Matrix>().rows());

    template < class Matrix >
    using TryAccessTo_n_rowsForMatrix = decltype(std::declval<Matrix>().n_rows);

    template < class Matrix >
    using TryCallOfColsForMatrix = decltype(std::declval<Matrix>().cols());

    template < class Matrix >
    using TryAccessTo_n_colsForMatrix = decltype(std::declval<Matrix>().n_cols);

    template < class Matrix , class = void > struct CallOfRowsForMatrix                                                                 : std::false_type {};
    template < class Matrix > struct CallOfRowsForMatrix< Matrix , void_t< TryCallOfRowsForMatrix< Matrix > > >                         : std::true_type {};

    template < class Matrix , class = void > struct CallOfColsForMatrix                                                                 : std::false_type {};
    template < class Matrix > struct CallOfColsForMatrix< Matrix , void_t< TryCallOfColsForMatrix< Matrix > > >                         : std::true_type {};

    template < class Matrix , class = void > struct AccessTo_n_rows                                                                     : std::false_type {};
    template < class Matrix > struct AccessTo_n_rows< Matrix , void_t < TryAccessTo_n_rowsForMatrix<Matrix> > >                         : std::true_type {};

    template < class Matrix , class = void > struct AccessTo_n_cols                                                                     : std::false_type {};
    template < class Matrix > struct AccessTo_n_cols< Matrix , void_t < TryAccessTo_n_colsForMatrix<Matrix> > >                         : std::true_type {};
    /**
     * \endcond
     */

    /**
     * \ingroup Checks
     * \brief Check if object of type Matrix has a member function rows().
     */
    template < class Matrix >
    constexpr bool hasRowsFunction()
    {
      return CallOfRowsForMatrix<Matrix>::value;
    }

    /**
     * \ingroup Checks
     * \brief Check if object of type Matrix has a member n_rows.
     */
    template < class Matrix >
    constexpr bool hasMember_n_rows()
    {
      return AccessTo_n_rows<Matrix>::value;
    }

    /**
     * \ingroup Checks
     * \brief Check if object of type Matrix has a member function cols().
     */
    template < class Matrix >
    constexpr bool hasColsFunction()
    {
      return CallOfColsForMatrix<Matrix>::value;
    }

    /**
     * \ingroup Checks
     * \brief Check if object of type Matrix has a member n_cols.
     */
    template < class Matrix >
    constexpr bool hasMember_n_cols()
    {
      return AccessTo_n_cols<Matrix>::value;
    }

//    /**
//     * \ingroup Checks
//     * \brief Check if object is a dynamic matrix for some type satisfying Concepts::MatrixConcept.
//     */
//    template < class Arg >
//    constexpr bool isDynamicMatrix()
//    {
//      return ( hasRowsFunction<Arg>() && hasColsFunction<Arg>() ) ||
//           ( hasMember_n_rows<Arg>() && hasMember_n_cols<Arg>() );
//    }

//    /**
//     * \ingroup Checks
//     * \brief Check if object is a dynamic vector for some type satisfying Concepts::VectorConcept.
//     */
//    template < class Arg >
//    constexpr bool isDynamicVector()
//    {
//      return hasRowsFunction<Arg>() || hasMember_n_rows<Arg>();
//    }
  }
}

#endif // FUNG_UTIL_STATIC_CHECKS_NROWS_NCOLS_HH
