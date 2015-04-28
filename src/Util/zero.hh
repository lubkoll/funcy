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

#ifndef RFFGEN_UTIL_ZERO_HH
#define RFFGEN_UTIL_ZERO_HH

namespace RFFGen
{
  /// Specialize this struct for your matrix type if a zero matrix cannot be generated via Matrix(0.).
  template <class Matrix>
  struct Zero
  {
    /**
     * @return zero matrix
     */
    Matrix operator()() const
    {
      return Matrix(0.);
    }
  };

  /**
   * Requires that a specialization of struct Zero exists for Matrix.
   * @return zero matrix
   */
  template <class Matrix>
  Matrix zero()
  {
    return Zero<Matrix>()();
  }
}

#endif // RFFGEN_UTIL_ZERO_HH
