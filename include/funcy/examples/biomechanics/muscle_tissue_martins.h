#pragma once

#include <funcy/funcy.h>

/**
 * @ingroup Biomechanics
 * @file muscle_tissue_martins.hh
 * @brief Versions of the muscle model of \cite Martins1998.
 */

namespace funcy
{
    /// @cond
    namespace MuscleTissueDetail
    {
        template < Matrix M, int n = linalg::dim< M >() >
        auto generateIncompressibleMuscleTissue_Martins( double c, double b, double d, double e,
                                                         const M& A, const M& F )
        {
            using namespace linalg;
            auto S = strainTensor( F );
            auto si1 = mi1< M, n >( S() ) - n;
            auto si6 = mi6< M, Matrix, n >( S(), A ) - 1;

            auto f = c * ( exp( b * si1 ) - 1 ) + d * ( exp( e * si6 ^ 2 ) - 1 );
            return f( S );
        }
    } // namespace MuscleTissueDetail
    /// @endcond

    /**
     * @ingroup Biomechanics
     * @brief Incompressible version of the model for muscle tissue of \cite Martins1998.
     *
     * Implementation of the stored energy function
     * \f$ W(F)=c(\exp(b(\bar\iota_1-3))-1) + A(\exp(a(\bar\iota_6-1)^2)-1) \f$, where
     * \f$\bar\iota_1,\bar\iota_6=\bar\iota_4\f$ are the first modified principal and the third
     * modified mixed invariant of the strain tensor \f$F^T F\f$.
     *
     * @param c first material parameter for the isotropic part
     * @param b second material parameter for the isotropic part
     * @param d first material parameter for the anisotropic part
     * @param e second material parameter for the anisotropic part
     * @param M structural (rank-one) tensor describing the initial orientation of muscle fibers for
     * \f$F=I\f$, where \f$I\f$ is the unit matrix.
     * @param F deformation gradient
     * @tparam offset number of rows/columns of F, this is only required to adjust the offset of the
     * energy functional such that \f$W(F)=0\f$ for \f$F=I\f$.
     */
    template < Matrix M, int offset = linalg::dim< M >() >
    auto incompressibleMuscleTissue_Martins( double c, double b, double d, double e, const M& A,
                                             const M& F )
    {
        return finalize(
            MuscleTissuedetail::generateIncompressibleMuscleTissue_Martins< M, offset >( c, b, d, e,
                                                                                         A, F ) );
    }

    /**
     * @ingroup Biomechanics
     * @brief Incompressible version of the model for muscle tissue of \cite Martins1998.
     *
     * Implementation of the stored energy function
     * \f$ W(F)=c(\exp(b(\bar\iota_1-3))-1) + A(\exp(a(\bar\iota_6-1)^2)-1) \f$, where
     * \f$\bar\iota_1,\bar\iota_6=\bar\iota_4\f$ are the first modified principal and the third
     * modified mixed invariant of the strain tensor \f$F^T F\f$.
     *
     * Material parameters taken from the same above mentioned publication, i.e. \f$a=0.387
     * (\,\mathrm{kPa})\f$, \f$ b = 23.46 \f$, \f$ A = 0.584 (\,\mathrm{kPa}) \f$ and \f$ a
     * = 12.43\f$.
     *
     * @param M structural (rank-one) tensor describing the initial orientation of muscle fibers for
     * \f$F=I\f$, where \f$I\f$ is the unit matrix.
     * @param F deformation gradient
     */
    template < Matrix M, int offset = linalg::dim< M >() >
    auto incompressibleMuscleTissue_Martins( const M& A, const M& F )
    {
        return incompressibleMuscleTissue_Martins< M, offset >( 0.387, 23.46, 0.584, 12.43, A, F );
    }

    /**
     * @ingroup Biomechanics
     * @brief Compressible version of the model for muscle tissue of \cite Martins1998.
     *
     * Implementation of the stored energy function
     * \f$ W(F)=c(\exp(b(\bar\iota_1-3))-1) + A(\exp(a(\bar\iota_6-1)^2)-1) +
     * d_0\Gamma_\mathrm{Inflation}(\det(F)) + d_1\Gamma_\mathrm{Compression} \f$, where
     * \f$\bar\iota_1,\bar\iota_6=\bar\iota_4\f$ are the first modified principal and the third
     * modified mixed invariant of the strain tensor \f$F^T F\f$.
     *
     * @param c first material parameter for the isotropic part
     * @param b second material parameter for the isotropic part
     * @param A first material parameter for the anisotropic part
     * @param a second material parameter for the anisotropic part
     * @param d0 material parameter for the penalty for inflation
     * @param d1 material parameter for the penalty for compression
     * @param M structural (rank-one) tensor describing the initial orientation of muscle fibers for
     * \f$F=I\f$, where \f$I\f$ is the unit matrix.
     * @param F deformation gradient
     */
    template < class Inflation, class Compression, Matrix M, int offset = linalg::dim< M >() >
    auto compressibleMuscleTissue_Martins( double c, double b, double A, double a, double d0,
                                           double d1, const M& A, const M& F )
    {
        return finalize(
            MuscleTissuedetail::generateIncompressibleMuscleTissue_Martins< M, offset >( c, b, A, a,
                                                                                         A, F ) +
            volumetricPenalty< Inflation, Compression >( d0, d1, F ) );
    }

    /**
     * @ingroup Biomechanics
     * @brief Compressible version of the model for muscle tissue of \cite Martins1998.
     *
     * Implementation of the stored energy function
     * \f$ W(F)=c(\exp(b(\bar\iota_1-3))-1) + A(\exp(a(\bar\iota_6-1)^2)-1) +
     * d_0\Gamma_\mathrm{Inflation}(\det(F)) + d_1\Gamma_\mathrm{Compression}(\det(F))\f$, where
     * \f$\bar\iota_1,\bar\iota_6=\bar\iota_4\f$ are the first modified principal and the third
     * modified mixed invariant of the strain tensor \f$F^T F\f$.
     *
     * Material parameters taken from the above mentioned publication, i.e. \f$a=0.387
     * (\,\mathrm{kPa})\f$, \f$ b = 23.46 \f$, \f$ A = 0.584 (\,\mathrm{kPa}) \f$ and \f$ a
     * = 12.43\f$.
     *
     * @param d0 material parameter for the penalty for inflation
     * @param d1 material parameter for the penalty for compression
     * @param M structural (rank-one) tensor describing the initial orientation of muscle fibers for
     * \f$F=I\f$, where \f$I\f$ is the unit matrix.
     * @param F deformation gradient
     */
    template < class Inflation, class Compression, Matrix M, int offset = linalg::dim< M >() >
    auto compressibleMuscleTissue_Martins( double d0, double d1, const M& A, const M& F )
    {
        return compressibleMuscleTissue_Martins< Inflation, Compression, M, offset >(
            0.387, 23.46, 0.584, 12.43, d0, d1, A, F );
    }
} // namespace funcy
