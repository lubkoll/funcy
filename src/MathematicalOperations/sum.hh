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

#ifndef RFFGEN_MATHEMATICAL_OPERATIONS_SUM_HH
#define RFFGEN_MATHEMATICAL_OPERATIONS_SUM_HH

#include <type_traits>
#include <utility>

#include "../Util/base.hh"
#include "../Util/computeSum.hh"
#include "../Util/derivativeWrappers.hh"
#include "../Util/indexedType.hh"

namespace RFFGen
{
  namespace MathematicalOperations
  {
    /**
     * \cond DOCUMENT_FORWARD_DECLARATIONS
     */
    template <class> struct FunctionConceptCheck;
    /**
     * \endcond
     */

    /**
     * \ingroup MathematicalOperationsGroup
     *
     * \brief %Sum of functions of type F and G (F and G must satisfy the requirements of Concepts::FunctionConcept).
     */
    template <class F, class G,
              class = FunctionConceptCheck<F> ,
              class = FunctionConceptCheck<G> >
    struct Sum : Base
    {
      Sum() = default;

      /**
       * @brief Constructor passing arguments to function constructors.
       * @param f_ input for constructor of first summand
       * @param g_ input for constructor of second summand
       */
      template <class InitF, class InitG>
      Sum(const InitF& f_, const InitG& g_)
        : f(f_), g(g_)
      {
        updateResultOfD0();
      }

      /// Reset point of evaluation.
      template <class Arg>
      void update(Arg const& x)
      {
        f.update(x);
        g.update(x);
        updateResultOfD0();
      }

      /// Propagate call to updateVariable() to f and g.
      template <int index, class Arg>
      void updateVariable(const Arg& x)
      {
        f.template updateVariable<index>(x);
        g.template updateVariable<index>(x);
      }

      /// Function value. Convenient access to d0() with prior call to update(x).
      template <class Arg>
      const auto& operator()(const Arg& x) const noexcept
      {
        update(x);
        return d0();
      }

      /// Function value. Convenient access to d0().
      const auto& operator()() const noexcept
      {
        return d0();
      }

      /// Function value.
      const auto& d0() const noexcept
      {
        return resultOfD0;
      }

      /**
       * \brief First directional derivative.
       * \param dx direction for which the derivative is computed
       */
      template < int id , class Arg ,
                 class IndexedArg = IndexedType<Arg,id> ,
                 class = std::enable_if_t< ComputeSum< D1<F,IndexedArg>, D1<G,IndexedArg> >::present > >
      auto d1(const Arg& dx) const
      {
        return ComputeSum< D1<F,IndexedArg>, D1<G,IndexedArg> >( f,g,dx )();
      }

      /**
       * \brief Second directional derivative.
       * \param dx direction for which the derivative is computed
       * \param dy direction for which the derivative is computed
       */
      template < int idx , int idy , class ArgX , class ArgY ,
                 class IndexedArgX = IndexedType<ArgX,idx> ,
                 class IndexedArgY = IndexedType<ArgY,idy> ,
                 class = std::enable_if_t< ComputeSum< D2<F,IndexedArgX,IndexedArgY>, D2<G,IndexedArgX,IndexedArgY> >::present > >
      auto d2(const ArgX& dx, const ArgY& dy) const
      {
        return ComputeSum< D2<F,IndexedArgX,IndexedArgY>, D2<G,IndexedArgX,IndexedArgY> >( f,g,dx,dy )();
      }

      /**
       * \brief Third directional derivative.
       * \param dx direction for which the derivative is computed
       * \param dy direction for which the derivative is computed
       * \param dz direction for which the derivative is computed
       */
      template < int idx , int idy , int idz , class ArgX, class ArgY, class ArgZ ,
                 class IndexedArgX = IndexedType<ArgX,idx> ,
                 class IndexedArgY = IndexedType<ArgY,idy> ,
                 class IndexedArgZ = IndexedType<ArgZ,idz> ,
                 class = std::enable_if_t< ComputeSum< D3<F,IndexedArgX,IndexedArgY,IndexedArgZ>, D3<G,IndexedArgX,IndexedArgY,IndexedArgZ> >::present > >
      auto d3(const ArgX& dx, const ArgY& dy, const ArgZ& dz) const
      {
        return ComputeSum< D3<F,IndexedArgX,IndexedArgY,IndexedArgZ>, D3<G,IndexedArgX,IndexedArgY,IndexedArgZ> >( f,g,dx,dy,dz )();
      }

    private:
      void updateResultOfD0()
      {
        resultOfD0 = f.d0() + g.d0();
      }

      F f;
      G g;
      decltype(std::declval<F>().d0() + std::declval<G>().d0()) resultOfD0;
    };
  }
}

#endif // RFFGEN_MATHEMATICAL_OPERATIONS_SUM_HH
