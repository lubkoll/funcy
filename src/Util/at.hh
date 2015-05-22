/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                             */
/*   This file is part of the C++-library RFFGen.                              */
/*   Copyright 2015 Lars Lubkoll                                               */
/*                                                                             */
/*   RFFGen is free software: you can redistribute it and/or modify            */
/*   it under the terms of the GNU General Public License as published by      */
/*   the Free Software Foundation, either version 3 of the License, or         */
/*   (at your option) any later version.                                       */
/*                                                                             */
/*   RFFGen is distributed in the hope that it will be useful,                 */
/*   but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*   GNU General Public License for more details.                              */
/*                                                                             */
/*   You should have received a copy of the GNU General Public License         */
/*   along with RFFGen.  If not, see <http://www.gnu.org/licenses/>.           */
/*                                                                             */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef RFFGEN_UTIL_AT_HH
#define RFFGEN_UTIL_AT_HH

#include <type_traits>
#include <utility>
#include "staticChecks.hh"

namespace RFFGen
{
  /**
   * \cond DOCUMENT_IMPLEMENTATION_DETAILS
   */
  namespace AtDetail
  {


    template <class Matrix, bool accessViaSquareBrackets, bool accessViaRoundBrackets, bool isMatrix>
    struct ValueTypeImpl;

    template <class Matrix, bool accessViaRoundBrackets>
    struct ValueTypeImpl<Matrix,true,accessViaRoundBrackets,true>
    {
      using type = decltype(std::declval<Matrix>()[0][0]);
    };

    template <class Matrix>
    struct ValueTypeImpl<Matrix,false,true,true>
    {
      using type = decltype(std::declval<Matrix>()(0,0));
    };

    template <class Vector, bool accessViaRoundBrackets>
    struct ValueTypeImpl<Vector,true,accessViaRoundBrackets,false>
    {
      using type = decltype(std::declval<Vector>()[0]);
    };

    template <class Vector>
    struct ValueTypeImpl<Vector,false,true,false>
    {
      using type = decltype(std::declval<Vector>()(0));
    };

    template <class Matrix>
    using ValueType = ValueTypeImpl<Matrix,Checks::accessViaSquareBrackets<Matrix>(),Checks::accessViaRoundBrackets<Matrix>(),Checks::isConstantSizeMatrix<Matrix>()>;

    template <class Matrix, bool whatever>
    __attribute__((always_inline)) auto& at(Matrix& A, int i, int j, std::true_type, std::integral_constant<bool,whatever>)
    {
      return A[i][j];
    }

    template <class Matrix>
    __attribute__((always_inline)) auto& at(Matrix& A, int i, int j, std::false_type, std::true_type)
    {
      return A(i,j);
    }


    template <class Vector, bool whatever>
    __attribute__((always_inline)) auto& at(Vector& v, int i, std::true_type, std::integral_constant<bool,whatever>)
    {
      return v[i];
    }

    template <class Vector>
    __attribute__((always_inline)) auto& at(Vector& v, int i, std::false_type, std::true_type)
    {
      return v(i);
    }
  }

  /// Access underlying value type of Matrix.
  template <class Arg>
  using at_t = typename AtDetail::ValueType<Arg>::type;


  template <class Matrix>
  __attribute__((always_inline)) auto& at(Matrix& A, int i, int j)
  {
    return AtDetail::at<Matrix>(A,i,j,std::integral_constant<bool,Checks::accessViaSquareBrackets<Matrix>()>(),
                                      std::integral_constant<bool,Checks::accessViaRoundBrackets<Matrix>()>());
  }


  template <class Vector>
  __attribute__((always_inline)) auto& at(Vector& v, int i)
  {
    return AtDetail::at<Vector>(v,i,std::integral_constant<bool,Checks::accessViaSquareBrackets<Vector>()>(),
                                    std::integral_constant<bool,Checks::accessViaRoundBrackets<Vector>()>());
  }
  /**
   * \endcond
   */
}

#endif // RFFGEN_UTIL_AT_HH
