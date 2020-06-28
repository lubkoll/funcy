#pragma once

#include <texy/constant.h>
#include <texy/examples/volumetric_penalty_functions.h>
#include <texy/generate.h>
#include <texy/linalg/principal_invariants.h>
#include <texy/linalg/strain_tensor.h>

#include <string>

/**
 * \ingroup Rubber
 * \file neo_hooke.hh
 * \brief Models based on the neo-Hookean material law. Input argument is the deformation gradient.
 */
namespace texy
{
    /**
     * \ingroup Rubber
     * \brief Generate an "incompressible" neo-Hookean material law \f$ W(F)=c\iota_1(F^T F) \f$,
     * where \f$\iota_1\f$ is the first principal matrix invariant .
     */
    template < int n >
    auto incompressibleNeoHooke( const std::string& c = "c", const std::string& F = "F" )
    {
        using namespace linalg;
        return constant( c ) * ( i1( strainTensor( F ) ) - n );
    }

    /**
     * \ingroup Rubber
     * \brief Generate an "incompressible" neo-Hookean material law \f$ W(F)=c\bar\iota_1(F^T F)
     * \f$, where \f$\bar\iota_1\f$ is the modified first principal matrix invariant.
     */
    template < int n >
    auto modifiedIncompressibleNeoHooke( const std::string& c = "c", const std::string& F = "F" )
    {
        using namespace linalg;
        auto S = LeftCauchyGreenStrainTensor( F );
        return constant( c ) * ( mi1< n >( S ) - n );
    }

    /**
     * \ingroup Rubber
     * \brief Generate a compressible neo-Hookean material law \f$ W(F)=c\iota_1(F^T
     * F)+d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F)) \f$,
     * where \f$\iota_1\f$ is the first principal matrix invariant.
     */
    template < class InflationPenalty, class CompressionPenalty, int n >
    auto compressibleNeoHooke( const std::string& c = "c", const std::string& d0 = "d_0",
                               const std::string& d1 = "d_1", const std::string& F = "F" )
    {
        using namespace linalg;
        return c * ( i1( strainTensor( F ) ) - n ) +
               volumetricPenalty< InflationPenalty, CompressionPenalty >( d0, d1, F );
    }

    /**
     * \ingroup Rubber
     * \brief Generate a compressible neo-Hookean material law \f$ W(F)=c\bar\iota_1(F^T
     * F)+d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F)) \f$,
     * where \f$\bar\iota_1\f$ is the modified first principal matrix invariant.
     */
    template < class InflationPenalty, class CompressionPenalty, int n >
    auto modifiedCompressibleNeoHooke( const std::string& c = "c", const std::string& d0 = "d_0",
                                       const std::string& d1 = "d_1", const std::string& F = "F" )
    {
        using namespace linalg;
        auto S = LeftCauchyGreenStrainTensor( F );
        return c * ( mi1< decltype( S ), n >( S ) - n ) +
               volumetricPenalty< InflationPenalty, CompressionPenalty >( d0, d1, F );
    }
}
