#pragma once

#include <iostream>

#include <funcy/identity.h>
#include <funcy/finalize.h>
#include <funcy/generate.h>
#include <funcy/linalg/strain_tensor.h>
#include <funcy/linalg/unit_matrix.h>
#include <funcy/linalg/principal_invariants.h>

/**
  \ingroup Rubber
 * \file mooney_rivlin.hh
 * \brief Models based on the Mooney-Rivlin material law. Input argument is the deformation gradient.
 */
namespace funcy
{
  /**
   * \ingroup Rubber
   * \brief Generate an "incompressible" Mooney-Rivlin material law \f$ W(F)=c_0\iota_1(F^T F) + c_1\iota_2(F^T F) \f$,
   * where \f$\iota_1\f$ is the first and \f$\iota_2\f$ the second principal matrix invariant.
   */
  template < class Matrix , int n = linalg::dim<Matrix>() >
  auto incompressibleMooneyRivlin(double c0, double c1, const Matrix& F)
  {
    using namespace linalg;
    auto S = LeftCauchyGreenStrainTensor<Matrix>(F);
    auto f = ( c0 * ( i1(F) - n ) + c1 * ( i2(F) - n ) );
    return finalize( f(S) );
  }


  /**
   * \ingroup Rubber
   * \brief Generate a compressible Mooney-Rivlin material law \f$ W(F)=c_0\iota_1(F^T F) + c_1\iota_2(F^T F) + d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F))  \f$,
   * where \f$\iota_1\f$ is the first and \f$\iota_2\f$ the second principal matrix invariant.
   */
  template <class InflationPenalty, class CompressionPenalty, class Matrix , int n = linalg::dim<Matrix>() >
  auto compressibleMooneyRivlin(double c0, double c1, double d0, double d1, const Matrix& F)
  {
    using namespace linalg;
    auto S = LeftCauchyGreenStrainTensor<Matrix>(F);
    auto f = ( c0 * ( i1(F) - n ) + c1 * ( i2(F) - n ) );
    return finalize( f(S) + volumetricPenalty<InflationPenalty,CompressionPenalty>(d0,d1,F) );
  }


//  /**
//   * \ingroup Rubber
//   *
//   * \brief Generate a compressible Mooney-Rivlin material law \f$ W(F)=c_0\iota_1(F^T F) + c_1\iota_2(F^T F) + d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F))  \f$,
//   * where \f$\iota_1\f$ is the first and \f$\iota_2\f$ the second principal matrix invariant.
//   * The parameters \f$c_0,c_1,d_0,d_1\f$ are chosen such that for \f$F\rightarrow I\f$ the model asymptotically yields Hooke's model of linearized elasticity with Lam\'e constants \f$\lambda,\mu\f$.
//   * Here \f$I\f$ denotes the unit matrix.
//   *
//   * \param lambda first Lame constant
//   * \param mu second Lame constant
//   */
//  template <class Matrix, class InflationPenalty, class CompressionPenalty>
//  auto createMooneyRivlinFromLameConstants(double lambda, double mu)
//  {
//    auto I = 1.;
//    auto g0 = CompressionPenalty(I) << Identity<double>(1.);
//    Finalize<decltype(g0)> g(g0);

//    auto rho = g.d1(I)/(-g.d2(I,I)+g.d1(I));
//    auto d = (lambda+2.0*mu)/(g.d2(I,I)-g.d1(I));
//    auto c = (0.5*rho-0.25)*mu+0.25*rho*lambda;
//    if(c > 0.25*mu) c = (rho-0.75)*mu+0.5*rho*lambda;
//    auto b = -mu + rho*(lambda+2.*mu)-2.*c;
//    auto a = b + mu;
//    auto alpha = 0.5*a - b;
//    auto beta = 0.5*b;

//    if(a<0 || b<0 || c<0)
//    {
//      std::cout << "In the generation of Mooney-Rivlin material model from Lame constants." << std::endl;
//      std::cout << "Computed parameters: " << alpha << ", " << beta<< ", " << c << ", " << d << std::endl;
//      std::cout << "Material law is not polyconvex! -> Terminating." << std::endl;
//      exit(1);
//    }

//    return compressibleMooneyRivlin<InflationPenalty,CompressionPenalty>(alpha,beta,c,d,linalg::unitMatrix<Matrix>());
//  }


//  /**
//   * \ingroup Rubber
//   *
//   * \brief Generate a compressible Mooney-Rivlin material law \f$ W(F)=c_0\iota_1(F^T F) + c_1\iota_2(F^T F) + d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F))  \f$,
//   * where \f$\iota_1\f$ is the first and \f$\iota_2\f$ the second principal matrix invariant.
//   * The parameters \f$c_0,c_1,d_0,d_1\f$ are chosen such that for \f$F\rightarrow I\f$ the model asymptotically yields Hooke's model of linearized elasticity with Young's modulus \f$E\f$ and
//   * Poisson ratio \f$\nu\f$. Here \f$I\f$ denotes the unit matrix.
//   *
//   * \param E Young's modulus
//   * \param nu Poisson ratio
//   */
//  template <class Matrix, class InflationPenalty, class CompressionPenalty>
//  auto createMooneyRivlinFromMaterialConstants(double E, double nu)
//  {
//    double lambda = E*nu/((1+nu)*(1-2*nu));
//    double mu = E/(2*(1+nu));
//    return createMooneyRivlinFromLameConstants<Matrix,InflationPenalty,CompressionPenalty>(lambda,mu);
//  }
}