#pragma once

#include <type_traits>
#include "static_checks.h"
#include "type_traits.h"

/// @cond
namespace Dune
{
  template <class,int> class FieldVector;
  template <class,int,int> class FieldMatrix;
}
/// @endcond

namespace funcy
{
  /// Computation of the l2 scalar product for Dune::FieldVector.
  template <class Scalar, class OtherScalar, int n,
            std::enable_if_t< !Concepts::Has::Free::multiplication< Dune::FieldVector<Scalar,n> , Dune::FieldVector<OtherScalar,n> >() >* = nullptr>
  auto operator*(const Dune::FieldVector<Scalar,n>& a, const Dune::FieldVector<OtherScalar,n>& b)
  {
    Scalar result = a[0] * b[0];
    for(int i=1; i<n; ++i)
      result += a[i]*b[i];
    return result;
  }

  /// Define matrix-vector multiplication for Dune::FieldMatrix and Dune::FieldVector, i.e. compute \f$y=Ax\f$.
  template <class Scalar, class OtherScalar, int n, int m,
            std::enable_if_t< !Concepts::Has::Free::multiplication< Dune::FieldMatrix<Scalar,n,m> , Dune::FieldVector<OtherScalar,m> >() >* = nullptr>
  auto operator*(const Dune::FieldMatrix<Scalar,n,m>& A, const Dune::FieldVector<OtherScalar,m>& x)
  {
    Dune::FieldVector<decltype(std::declval<Scalar>()*std::declval<OtherScalar>()),n> y(0);
    A.mv(x,y);
    return y;
  }

  /// Define vector-matrix multiplication for Dune::FieldMatrix and Dune::FieldVector, i.e. compute \f$x^T A = y^T\f$ resp. \f$y=A^T x\f$.
  template <class Scalar, class OtherScalar, int n, int m,
            std::enable_if_t< !Concepts::Has::Free::multiplication< Dune::FieldVector<OtherScalar,n> , Dune::FieldMatrix<Scalar,n,m> >() >* = nullptr>
  auto operator*(const Dune::FieldVector<OtherScalar,n>& x, const Dune::FieldMatrix<Scalar,n,m>& A)
  {
    Dune::FieldVector<decltype(std::declval<Scalar>()*std::declval<OtherScalar>()),m> y(0);
    A.mtv(x,y);
    return y;
  }


  /// Defines operator* for multiplication with arithmetic types from the left if undefined and in-place multiplication (operator*=()) is supported.
  template < class Arg, class ScalarArg,
             std::enable_if_t< is_arithmetic<ScalarArg>::value >* = nullptr,
             std::enable_if_t< !Concepts::isFunction<Arg>() && !is_arithmetic<Arg>() >* = nullptr,
             std::enable_if_t< !Concepts::Has::Free::multiplication<ScalarArg,Arg>() >* = nullptr,
             std::enable_if_t< Concepts::Has::MemOp::inPlaceMultiplication<Arg,ScalarArg>() >* = nullptr >
  auto operator*( ScalarArg a , Arg x )
  {
    x *= a;
    return x;
  }

  /// Defines operator* for multiplication with arithmetic types from the right if undefined and in-place multiplication (operator*=()) is supported.
  template < class Arg, class ScalarArg,
             std::enable_if_t< is_arithmetic<ScalarArg>::value >* = nullptr,
             std::enable_if_t< !Concepts::isFunction<Arg>() && !is_arithmetic<Arg>::value>* = nullptr,
             std::enable_if_t< !Concepts::Has::Free::multiplication<ScalarArg,Arg>() >* = nullptr,
             std::enable_if_t< Concepts::Has::MemOp::inPlaceMultiplication<Arg,ScalarArg>() >* = nullptr >
  auto operator*( Arg x , ScalarArg a )
  {
    x *= a;
    return x;
  }

  /// Defines operator* for multiplication of non-arithmetic types if undefined and in-place multiplication (operator*=()) is supported.
  template < class Arg1, class Arg2,
             std::enable_if_t< !Concepts::isFunction<Arg1>() && !Concepts::isFunction<Arg2>() >* = nullptr,
             std::enable_if_t< !is_arithmetic<Arg1>() && !is_arithmetic<Arg2>() >* = nullptr,
             std::enable_if_t< !Concepts::Has::Free::multiplication<Arg1,Arg2>() &&
                                Concepts::Has::MemOp::inPlaceMultiplication<Arg1,Arg2>() >* = nullptr >
  auto operator*( Arg1 x, const Arg2& y)
  {
    x *= y;
    return x;
  }

  /// Defines operator* for multiplication of non-arithmetic types if undefined and in-place multiplication is provided in terms of the member function rightmultiplyany() (such as for Dune::FieldMatrix).
  template < class Arg1, class Arg2,
             std::enable_if_t< !Concepts::isFunction<Arg1>() && !Concepts::isFunction<Arg2>() >* = nullptr,
             std::enable_if_t< !is_arithmetic<Arg1>() && !is_arithmetic<Arg2>() >* = nullptr,
             std::enable_if_t< !Concepts::Has::Free::multiplication<Arg1,Arg2>() &&
                               !Concepts::Has::MemOp::inPlaceMultiplication<Arg1,Arg2>() &&
                               Concepts::Has::MemFn::rightmultiplyany<Arg1,Arg2>() >* = nullptr >
  auto operator*( Arg1 x , const Arg2& y)
  {
    return x.rightmultiplyany(y);
  }

  /// Defines operator+ if not yet defined and in-place summation (operator+=()) is supported.
  template < class Arg ,
             std::enable_if_t< !Concepts::isFunction<Arg>() && !is_arithmetic<Arg>() >* = nullptr,
             std::enable_if_t< !Concepts::Has::Free::summation<Arg>() &&
                                Concepts::Has::MemOp::inPlaceSummation<Arg>() >* = nullptr >
  auto operator+(Arg x, const Arg& y)
  {
    x += y;
    return x;
  }
}
