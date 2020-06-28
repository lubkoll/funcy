#pragma once

#include <funcy/finalize.h>
#include <funcy/generate.h>
#include <funcy/linalg/principal_invariants.h>
#include <funcy/linalg/strain_tensor.h>
#include <funcy/linalg/unit_matrix.h>
#include <funcy/examples/volumetric_penalty_functions.h>

/**
 * \ingroup Rubber
 * \file neo_hooke.hh
 * \brief Models based on the neo-Hookean material law. Input argument is the deformation gradient.
 */

namespace funcy
{
  /**
   * \ingroup Rubber
   * \brief Generate an "incompressible" neo-Hookean material law \f$ W(F)=c\iota_1(F^T F) \f$, where \f$\iota_1\f$ is the first principal matrix invariant .
   */
  template < class Matrix , int n = linalg::dim<Matrix>() >
  auto incompressibleNeoHooke(double c, const Matrix& F)
  {
    using namespace linalg;
    return finalize( c*(i1(strainTensor(F)) - n) );
  }

  /**
   * \ingroup Rubber
   * \brief Generate an "incompressible" neo-Hookean material law \f$ W(F)=c\bar\iota_1(F^T F) \f$, where \f$\bar\iota_1\f$ is the modified first principal matrix invariant.
   */
  template < class Matrix , int n = linalg::dim<Matrix>() >
  auto modifiedIncompressibleNeoHooke(double c, const Matrix& F)
  {
    using namespace linalg;
    auto S = LeftCauchyGreenStrainTensor<Matrix>(F);
    return finalize( c*(mi1<decltype(S),n>(S) - n) );
  }

  /**
   * \ingroup Rubber
   * \brief Generate a compressible neo-Hookean material law \f$ W(F)=c\iota_1(F^T F)+d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F)) \f$,
   * where \f$\iota_1\f$ is the first principal matrix invariant.
   */
  template <class InflationPenalty, class CompressionPenalty, class Matrix , int n = linalg::dim<Matrix>() >
  auto compressibleNeoHooke(double c, double d0, double d1, const Matrix& F)
  {
    using namespace linalg;
    return finalize( c*(i1(strainTensor(F)) - n) + volumetricPenalty<InflationPenalty,CompressionPenalty>(d0,d1,F) );
  }

  /**
   * \ingroup Rubber
   * \brief Generate a compressible neo-Hookean material law \f$ W(F)=c\bar\iota_1(F^T F)+d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F)) \f$,
   * where \f$\bar\iota_1\f$ is the modified first principal matrix invariant.
   */
  template <class InflationPenalty, class CompressionPenalty, class Matrix , int n = linalg::dim<Matrix>() >
  auto modifiedCompressibleNeoHooke(double c, double d0, double d1, const Matrix& F)
  {
    using namespace linalg;
    auto S = LeftCauchyGreenStrainTensor<Matrix>(F);
    return finalize( c*(mi1<decltype(S),n>(S) - n) + volumetricPenalty<InflationPenalty,CompressionPenalty>(d0,d1,F) );
  }
}
