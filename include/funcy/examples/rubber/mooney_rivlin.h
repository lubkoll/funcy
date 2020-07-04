#pragma once

#include <funcy/examples/volumetric_penalty_functions.h>
#include <funcy/funcy.h>

#include <iostream>
#include <string>

/**
  \ingroup Rubber
 * \file mooney_rivlin.hh
 * @brief Models based on the Mooney-Rivlin material law. Input argument is the deformation
 gradient.
 */
namespace funcy
{
    /**
     * \ingroup Rubber
     * @brief Generate an "incompressible" Mooney-Rivlin material law \f$ W(F)=c_0\iota_1(F^T F) +
     * c_1\iota_2(F^T F) \f$, where \f$\iota_1\f$ is the first and \f$\iota_2\f$ the second
     * principal matrix invariant.
     */
    template < linalg::Matrix Mat, int n = linalg::dim< Mat >() >
    auto incompressible_mooney_rivlin( double c0, double c1, const Mat& F )
    {
        using namespace linalg;
        auto S = LeftCauchyGreenStrainTensor( F );
        auto f = ( c0 * ( i1( F ) - n ) + c1 * ( i2( F ) - n ) );
        return finalize( f( S ) );
    }

    /**
     * \ingroup Rubber
     * @brief Generate a compressible Mooney-Rivlin material law \f$ W(F)=c_0\iota_1(F^T F) +
     * c_1\iota_2(F^T F) + d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F))  \f$, where
     * \f$\iota_1\f$ is the first and \f$\iota_2\f$ the second principal matrix invariant.
     */
    template < class InflationPenalty, class CompressionPenalty, linalg::Matrix Mat,
               int n = linalg::dim< Mat >() >
    auto compressible_mooney_rivlin( double c0, double c1, double d0, double d1, const Mat& F )
    {
        using namespace linalg;
        auto S = LeftCauchyGreenStrainTensor( F );
        auto f = ( c0 * ( i1( F ) - n ) + c1 * ( i2( F ) - n ) );
        return finalize( f( S ) +
                         volumetric_penalty< InflationPenalty, CompressionPenalty >( d0, d1, F ) );
    }

    /**
     * \ingroup Rubber
     *
     * @brief Generate a compressible Mooney-Rivlin material law \f$ W(F)=c_0\iota_1(F^T F) +
     c_1\iota_2(F^T F) + d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F))  \f$,
     * where \f$\iota_1\f$ is the first and \f$\iota_2\f$ the second principal matrix invariant.
     * The parameters \f$c_0,c_1,d_0,d_1\f$ are chosen such that for \f$F\rightarrow I\f$ the
     model asymptotically yields Hooke's model of linearized elasticity with Lam\'e constants
     \f$\lambda,\mu\f$.
     * Here \f$I\f$ denotes the unit matrix.
     *
     * \param lambda first Lame constant
     * \param mu second Lame constant
     */
    template < linalg::Matrix Mat, class InflationPenalty, class CompressionPenalty >
    auto create_mooney_rivlin_from_lame_constants( double lambda, double mu )
    {
        auto I = 1.;
        auto g = finalize( CompressionPenalty( I )( Identity< double >( 1. ) ) );

        auto rho = g.d1( I ) / ( -g.d2( I, I ) + g.d1( I ) );
        auto d = ( lambda + 2.0 * mu ) / ( g.d2( I, I ) - g.d1( I ) );
        auto c = ( 0.5 * rho - 0.25 ) * mu + 0.25 * rho * lambda;
        if ( c > 0.25 * mu )
            c = ( rho - 0.75 ) * mu + 0.5 * rho * lambda;
        auto b = -mu + rho * ( lambda + 2. * mu ) - 2. * c;
        auto a = b + mu;
        auto alpha = 0.5 * a - b;
        auto beta = 0.5 * b;

        if ( a < 0 || b < 0 || c < 0 )
        {
            std::cout << "In the generation of Mooney-Rivlin material model from Lame constants."
                      << std::endl;
            std::cout << "Computed parameters: " << alpha << ", " << beta << ", " << c << ", " << d
                      << std::endl;
            std::cout << "Material law is not polyconvex! -> Terminating." << std::endl;
            exit( 1 );
        }

        return compressible_mooney_rivlin< InflationPenalty, CompressionPenalty >(
            alpha, beta, c, d, linalg::unit_matrix< Mat >() );
    }

    /**
     * \ingroup Rubber
     *
     * @brief Generate a compressible Mooney-Rivlin material law \f$ W(F)=c_0\iota_1(F^T F) +
     c_1\iota_2(F^T F) + d_0\Gamma_\mathrm{In}(\det(F))+d_1\Gamma_\mathrm{Co}(\det(F))  \f$,
     * where \f$\iota_1\f$ is the first and \f$\iota_2\f$ the second principal matrix invariant.
     * The parameters \f$c_0,c_1,d_0,d_1\f$ are chosen such that for \f$F\rightarrow I\f$ the
     model asymptotically yields Hooke's model of linearized elasticity with Young's modulus
     \f$E\f$ and
     * Poisson ratio \f$\nu\f$. Here \f$I\f$ denotes the unit matrix.
     *
     * \param E Young's modulus
     * \param nu Poisson ratio
     */
    template < linalg::Matrix Mat, class InflationPenalty, class CompressionPenalty >
    auto create_mooney_rivlin_from_material_constants( double E, double nu )
    {
        double lambda = E * nu / ( ( 1 + nu ) * ( 1 - 2 * nu ) );
        double mu = E / ( 2 * ( 1 + nu ) );
        return create_mooney_rivlin_from_lame_constants< Mat, InflationPenalty,
                                                         CompressionPenalty >( lambda, mu );
    }
} // namespace funcy
