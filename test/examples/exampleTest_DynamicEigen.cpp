#include <Eigen/Dense>
#include <gtest/gtest.h>

#include <tuple>

#define FUNCY_ENABLE_EXCEPTIONS
#include <funcy/examples/biomechanics/adipose_tissue_sommer_holzapfel.h>
#include <funcy/examples/biomechanics/muscle_tissue_martins.h>
#include <funcy/examples/biomechanics/skin_tissue_hendriks.h>
#include <funcy/examples/rubber/mooney_rivlin.h>
#include <funcy/examples/rubber/neo_hooke.h>

namespace
{
    using funcy::LN;
    using funcy::Pow;
    constexpr int dim = 3;
    using M = Eigen::MatrixXd;

    template < class Function >
    auto runTest( Function& f )
    {
        M a = funcy::linalg::unit_matrix< M >( dim );
        M da0 = 2 * a, da1 = 3 * a, da2 = 4 * a;

        f.update( a );

        return std::make_tuple( f(), f.d1( da0 ), f.d2( da0, da1 ), f.d3( da0, da1, da2 ) );
    }

    auto c0 = 1., c1 = 1., d0 = 1., d1 = 1.;

    auto initFiberTensor()
    {
        M m( dim, dim );
        m.fill( 0 );
        m( 0, 0 ) = 1;
        return m;
    }

    M fiberTensor = initFiberTensor(), I = funcy::linalg::unit_matrix< M >( dim );
} // namespace

TEST( NeoHooke, Incompressible_Dynamic_Eigen )
{
    auto incompressible_neo_hooke = funcy::incompressible_neo_hooke< M, dim >( c0, I );
    auto f = runTest( incompressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 12 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 36 );
    EXPECT_DOUBLE_EQ( std::get< 3 >( f ), 0 );
}

TEST( NeoHooke, Compressible_Dynamic_Eigen )
{
    auto compressible_neo_hooke =
        funcy::compressible_neo_hooke< Pow< 2 >, LN, M, dim >( c0, d0, d1, I );
    auto f = runTest( compressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 30 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 198 );
    EXPECT_DOUBLE_EQ( std::get< 3 >( f ), 3024 );
}

TEST( NeoHooke, ModifiedIncompressible_Dynamic_Eigen )
{
    auto modifiedincompressible_neo_hooke =
        funcy::modified_incompressible_neo_hooke< M, dim >( c0, I );
    auto f = runTest( modifiedincompressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 0 );
    EXPECT_NEAR( std::get< 3 >( f ), 0, 1e-11 );
}

TEST( NeoHooke, ModifiedCompressible_Dynamic_Eigen )
{
    auto modified_compressible_neo_hooke =
        funcy::modified_compressible_neo_hooke< Pow< 2 >, LN, M, dim >( c0, d0, d1, I );
    auto f = runTest( modified_compressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 18 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 162 );
    EXPECT_NEAR( std::get< 3 >( f ), 3024, 1e-11 );
}

TEST( MooneyRivlin, Incompressible_Dynamic_Eigen )
{
    auto mooneyRivlin = funcy::incompressible_mooney_rivlin< M, dim >( c0, c1, I );
    auto f = runTest( mooneyRivlin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 36 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 252 );
    EXPECT_NEAR( std::get< 3 >( f ), 1728, 1e-13 );
}

TEST( MooneyRivlin, Compressible_Dynamic_Eigen )
{
    auto mooneyRivlin =
        funcy::compressible_mooney_rivlin< Pow< 2 >, LN, M, dim >( c0, c1, d0, d1, I );
    auto f = runTest( mooneyRivlin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 54 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 414 );
    EXPECT_NEAR( std::get< 3 >( f ), 4752, 1e-13 );
}

TEST( Skin_Hendriks, Incompressibsle_Dynamic_Eigen )
{
    auto skin = funcy::incompressible_skin_hendriks< M, dim >( c0, c1, I );
    auto f = runTest( skin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 12 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 900 );
    EXPECT_NEAR( std::get< 3 >( f ), 20736, 1e-13 );
}

TEST( Skin_Hendriks, Compressible_Dynamic_Eigen )
{
    auto skin = funcy::compressible_skin_hendriks< Pow< 2 >, LN, M, dim >( c0, c1, d0, d1, I );
    auto f = runTest( skin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 30 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 1062 );
    EXPECT_NEAR( std::get< 3 >( f ), 23760, 1e-13 );
}

TEST( Adipose_SommerHolzapfel, Incompressible_Dynamic_Eigen )
{
    auto adipose =
        funcy::incompressible_adipose_tissue_sommer_holzapfel< M, dim >( fiberTensor, I );
    auto f = runTest( adipose );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 1.8, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 43.8, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 460.8, 1e-11 );
}

TEST( Adipose_SommerHolzapfel, Compressible_Dynamic_Eigen )
{
    auto adipose = funcy::compressible_adipose_tissue_sommer_holzapfel< Pow< 2 >, LN, M, dim >(
        d0, d1, fiberTensor, I );
    auto f = runTest( adipose );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 19.8, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 205.8, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 3484.8, 1e-11 );
}

TEST( Muscle_Martins, Incompressible_Dynamic_Eigen )
{
    auto muscle = funcy::incompressible_muscle_tissue_martins< M, dim >( fiberTensor, I );
    auto f = runTest( muscle );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 0, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 0, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 0, 1e-10 );
}

TEST( Muscle_Martins, Compressible_Dynamic_Eigen )
{
    auto muscle =
        funcy::compressible_muscle_tissue_martins< Pow< 2 >, LN, M, dim >( d0, d1, fiberTensor, I );
    auto f = runTest( muscle );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 18, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 162, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 3024, 1e-10 );
}
