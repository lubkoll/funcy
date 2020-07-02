#pragma once

#include <funcy/funcy.h>

/**
 * \ingroup Biomechanics
 * \file skin_tissue_hendriks.hh
 * @brief Versions of the skin model of \cite Hendriks2005.
 */

namespace funcy
{
    /** @cond */
    namespace SkinDetail
    {
        template < Matrix M, int n = linalg::dim< M >() >
        auto incompressibleSkin_HendriksImpl( double c0, double c1, const M& F )
        {
            using namespace linalg;
            auto S = strainTensor( F );
            auto si1 = i1( S() ) - n;
            auto si2 = i2( S() ) - n;
            auto f = c0 * si1 + c1 * si1 * si2;
            return f( S );
        }
    } // namespace SkinDetail
    /** @endcond */

    /**
     * @ingroup Biomechanics
     * @brief Model for skin tissue of \cite Hendriks2005.
     *
     * Implementation of the stored energy function
     * \f$W(F)=c_0(\iota_1-3) + c_1(\iota_1-3)(\iota_2-3)\f$, where \f$\iota_1,\iota_2\f$ are the
     * first and second principal invariants of the strain tensor \f$F^T F\f$.
     *
     * @param c0 scaling of the shifted first principal invariant
     * @param c1 scaling of the product of shifted first and second principal invariant
     * @param F initial deformation gradient
     */
    template < Matrix M, int n = linalg::dim< M >() >
    auto incompressibleSkin_Hendriks( double c0, double c1, const M& F )
    {
        return finalize( Skindetail::incompressibleSkin_HendriksImpl< M, n >( c0, c1, F ) );
    }

    /**
     * @ingroup Biomechanics
     * @brief Model for skin tissue of \cite Hendriks2005.
     *
     * Implementation of the stored energy function
     * \f$W(F)=c_0(\iota_1-3) + c_1(\iota_1-3)(\iota_2-3)\f$, where \f$\iota_1,\iota_2\f$ are the
     * first and second principal invariants of the strain tensor \f$F^T F\f$.
     *
     * Material parameters are taken from \cite Xu2011,
     * i.e \f$c_0=9.4 (\,\mathrm{kPa})\f$ and \f$ c_1 = 82 (\,\mathrm{kPa}) \f$.
     *
     * @param F initial deformation gradient
     */
    template < Matrix M, int n = linalg::dim< M >() >
    auto incompressibleSkin_Hendriks( const M& F )
    {
        return incompressibleSkin_Hendriks< M, n >( 9.4, 82., F );
    }

    /**
     * @ingroup Biomechanics
     * @brief Compressible version of the model for skin tissue of \cite Hendriks2005.
     *
     * Implementation of the stored energy function
     * \f$W(F)=c_0(\iota_1-3) + c_1(\iota_1-3)(\iota_2-3) + d_0\Gamma_\mathrm{Inflation}(\det(F)) +
     * d_1\Gamma_\mathrm{Compression}\f$, where \f$\iota_1,\iota_2\f$ are the first and second
     * principal invariants of the strain tensor \f$F^T F\f$.
     *
     * @param c0 scaling of the shifted first principal invariant
     * @param c1 scaling of the product of shifted first and second principal invariant
     * @param d0 scaling of the penalty function for inflation
     * @param d1 scaling of the penalty function for compression
     * @param F initial deformation gradient
     */
    template < class InflationPenalty, class CompressionPenalty, Matrix M,
               int n = linalg::dim< M >() >
    auto compressibleSkin_Hendriks( double c0, double c1, double d0, double d1, const M& F )
    {
        return finalize( Skindetail::incompressibleSkin_HendriksImpl< M, n >( c0, c1, F ) +
                         volumetricPenalty< InflationPenalty, CompressionPenalty >( d0, d1, F ) );
    }

    /**
     * @ingroup Biomechanics
     * @brief Compressible version of the model for skin tissue of \cite Hendriks2005.
     *
     * Implementation of the stored energy function
     * \f$W(F)=c_0(\iota_1-3) + c_1(\iota_1-3)(\iota_2-3) + d_0\Gamma_\mathrm{Inflation}(\det(F)) +
     * d_1\Gamma_\mathrm{Compression}\f$, where \f$\iota_1,\iota_2\f$ are the first and second
     * principal invariants of the strain tensor \f$F^T F\f$.
     *
     * Material parameters are taken from \cite Xu2011,
     * i.e \f$c_0=9.4 (\,\mathrm{kPa})\f$ and \f$ c_1 = 82 (\,\mathrm{kPa}) \f$.
     *
     * @param d0 scaling of the penalty function for inflation
     * @param d1 scaling of the penalty function for compression
     * @param F initial deformation gradient
     */
    template < class InflationPenalty, class CompressionPenalty, Matrix M,
               int n = linalg::dim< M >() >
    auto compressibleSkin_Hendriks( double d0, double d1, const M& F )
    {
        return compressibleSkin_Hendriks< InflationPenalty, CompressionPenalty, M, n >( 9.4, 82.,
                                                                                        d0, d1, F );
    }
} // namespace funcy
