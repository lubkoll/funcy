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

#ifndef RFFGEN_UTIL_ADDTRANSPOSEDMATRIX_HH
#define RFFGEN_UTIL_ADDTRANSPOSEDMATRIX_HH

#include "../LinearAlgebra/dimension.hh"

namespace RFFGen
{
  /**
   * Overwrites \f$A\f$ with \f$A+A^T\f$.
   * \return \f$A+A^T\f$
   */
  template <class Matrix>
  Matrix addTransposed(Matrix& A)
  {
    for(int i=0; i<LinearAlgebra::dimension<Matrix>(); ++i)
      for(int j=i+1; j<LinearAlgebra::dimension<Matrix>(); ++j)
        at(A,j,i) = at(A,i,j) = at(A,i,j) + at(A,j,i);
    for(int i=0; i<LinearAlgebra::dimension<Matrix>(); ++i) at(A,i,i) *= 2;
    return A;
  }
}

#endif // RFFGEN_UTIL_ADDTRANSPOSEDMATRIX_HH
