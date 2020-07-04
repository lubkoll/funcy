#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/transpose.h>
#include <funcy/util/add_transposed_matrix.h>
#include <funcy/util/chainer.h>

namespace funcy
{
    /** @addtogroup LinearAlgebraGroup
     * @{
     */
    namespace linalg
    {
        /**
         * @brief Right Cauchy-Green strain tensor \f$ F^T F \f$ for a symmetric matrix \f$ F \f$.
         *
         * Used in nonlinear material models based on the deformation gradient \f$\nabla\varphi\f$,
         * which takes the role of \f$F\f$.
         */
        template < class Mat >
        class RightCauchyGreenStrainTensor : public Chainer< RightCauchyGreenStrainTensor< Mat > >
        {
        public:
            RightCauchyGreenStrainTensor() = default;
            /**
             * @brief Constructor.
             * @param F point of evaluation.
             */
            explicit RightCauchyGreenStrainTensor( const Mat& F )
            {
                update( F );
            }

            /// Reset point of evaluation.
            void update( const Mat& F )
            {
                FT = detail::transpose( F );
                FTF = FT * F;
            }

            /// Function value \f$ F^T * F \f$.
            const Mat& d0() const noexcept
            {
                return FTF;
            }

            /// First directional derivative \f$ F^T dF_1 + dF_1^T F \f$.
            Mat d1( const Mat& dF1 ) const
            {
                Mat FTdF1 = FT * dF1;
                return add_transposed( FTdF1 );
            }

            /// Second directional derivative \f$ dF_2^T dF_1 + dF_1^T dF_2 \f$.
            Mat d2( const Mat& dF1, const Mat& dF2 ) const
            {
                Mat dF2TdF1 = detail::transpose( dF2 ) * dF1;
                return add_transposed( dF2TdF1 );
            }

        private:
            Mat FT, FTF;
        };

        /**
         * @brief Left Cauchy-Green strain tensor \f$ F^T F \f$ for a symmetric matrix \f$ F \f$.
         *
         * Used in nonlinear material models based on the deformation gradient \f$\nabla\varphi\f$,
         * which takes the role of \f$F\f$.
         */
        template < class Mat >
        class LeftCauchyGreenStrainTensor : public Chainer< LeftCauchyGreenStrainTensor< Mat > >
        {
        public:
            LeftCauchyGreenStrainTensor() = default;
            /**
             * @brief Constructor.
             * @param F point of evaluation.
             */
            explicit LeftCauchyGreenStrainTensor( const Mat& F )
            {
                update( F );
            }

            /// Reset point of evaluation.
            void update( const Mat& F )
            {
                FT = detail::transpose( F );
                FFT = F * FT;
            }

            /// Function value \f$ F^T * F \f$.
            const Mat& d0() const noexcept
            {
                return FFT;
            }

            /// First directional derivative \f$ F^T dF_1 + dF_1^T F \f$.
            Mat d1( const Mat& dF1 ) const
            {
                Mat FTdF1 = dF1 * FT;
                return add_transposed( FTdF1 );
            }

            /// Second directional derivative \f$ dF_2^T dF_1 + dF_1^T dF_2 \f$.
            Mat d2( const Mat& dF1, const Mat& dF2 ) const
            {
                Mat dF1dF2T = dF1 * detail::transpose( dF2 );
                return add_transposed( dF1dF2T );
            }

        private:
            Mat FT, FFT;
        };

        /**
         * @brief Generate the right Cauchy-Green strain tensor \f$A*A^T\f$.
         * \param A matrix
         * \return RightCauchyGreenStrainTensor<Matrix>(A)
         */
        template < class Mat >
        auto strain_tensor( const Mat& A )
        {
            return RightCauchyGreenStrainTensor{ A };
        }

        /**
         * @brief Generate the right Cauchy-Green strain tensor \f$f*f^T\f$, where
         * \f$f:\cdot\mapsto\mathbb{R}^{n,n} \f$. \param f function object mapping into a space of
         * square matrices \return RightCauchyGreenStrainTensor< decay_t<decltype(f())> >(f())( f )
         */
        template < Function F >
        auto strain_tensor( const F& f )
        {
            return RightCauchyGreenStrainTensor< decay_t< decltype( f() ) > >{ f() }( f );
        }

        /**
         * @brief Generate the left Cauchy-Green strain tensor \f$A^T*A\f$.
         * \param A matrix
         * \return LeftCauchyGreenStrainTensor<Matrix>(A)
         */
        template < class Mat >
        auto leftStrainTensor( const Mat& A )
        {
            return LeftCauchyGreenStrainTensor{ A };
        }

        /**
         * @brief Generate the left Cauchy-Green strain tensor \f$f^T*f\f$, where
         * \f$f:\cdot\mapsto\mathbb{R}^{n,n} \f$. \param f function object mapping into a space of
         * square matrices \return LeftCauchyGreenStrainTensor< decay_t<decltype(f())> >(f())( f )
         */
        template < Function F >
        auto leftStrainTensor( const F& f )
        {
            return LeftCauchyGreenStrainTensor< decay_t< decltype( f() ) > >{ f() }( f );
        }
    } // namespace linalg
    /** @} */
} // namespace funcy
