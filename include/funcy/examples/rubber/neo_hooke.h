#pragma once

#include <funcy/examples/volumetric_penalty_functions.h>
#include <funcy/funcy.h>

/**
 * \ingroup Rubber
 * \file neo_hooke.hh
 * @brief Models based on the neo-Hookean material law. Input argument is the deformation gradient.
 */

namespace funcy
{
    /**
     * \ingroup Rubber
     * @brief Generate an "incompressible" neo-Hookean material law \f$ W(F)=c\iota_1(F^T F) \f$,
     * where \f$\iota_1\f$ is the first principal matrix invariant .
     */
    template < Matrix M, int n = linalg::dim< M >() >
    auto incompressible_neo_hooke( double c, const M& F )
    {
        using namespace linalg;
        auto S = strain_tensor( F );
        auto x = i1( S );
        return finalize( c * ( x - n ) );
    }

    /**
     * \ingroup Rubber
     * @brief Generate an "incompressible" neo-Hookean material law \f$ W(F)=c\bar\iota_1(F^T F)
     * \f$, where \f$\bar\iota_1\f$ is the modified first principal matrix invariant.
     */
    template < Matrix M, int n = linalg::dim< M >() >
    auto modified_incompressible_neo_hooke( double c, const M& F )
    {
        using namespace linalg;
        auto S = LeftCauchyGreenStrainTensor( F );
        return finalize( c * ( mi1< decltype( S ), n >( S ) - n ) );
    }

    /**
     * \ingroup Rubber
     * @brief Generate a compressible neo-Hookean material law \f$ W(F)=c\iota_1(F^T
     * F)+d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F)) \f$, where \f$\iota_1\f$ is
     * the first principal matrix invariant.
     */
    template < class InflationPenalty, class CompressionPenalty, Matrix M,
               int n = linalg::dim< M >() >
    auto compressible_neo_hooke( double c, double d0, double d1, const M& F )
    {
        using namespace linalg;
        return finalize( c * ( i1( strain_tensor( F ) ) - n ) +
                         volumetric_penalty< InflationPenalty, CompressionPenalty >( d0, d1, F ) );
    }

    /**
     * \ingroup Rubber
     * @brief Generate a compressible neo-Hookean material law \f$ W(F)=c\bar\iota_1(F^T
     * F)+d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F)) \f$, where \f$\bar\iota_1\f$
     * is the modified first principal matrix invariant.
     */
    template < class InflationPenalty, class CompressionPenalty, Matrix M,
               int n = linalg::dim< M >() >
    auto modified_compressible_neo_hooke( double c, double d0, double d1, const M& F )
    {
        using namespace linalg;
        auto S = LeftCauchyGreenStrainTensor< M >( F );
        return finalize( c * ( mi1< decltype( S ), n >( S ) - n ) +
                         volumetric_penalty< InflationPenalty, CompressionPenalty >( d0, d1, F ) );
    }
} // namespace funcy
