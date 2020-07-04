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
    template < class M, class Function >
    auto runTest( Function& f )
    {
        M a = funcy::linalg::unit_matrix< M >();
        M da0 = 2 * a, da1 = 3 * a, da2 = 4 * a;

        f.update( a );

        return std::make_tuple( f(), f.d1( da0 ), f.d2( da0, da1 ), f.d3( da0, da1, da2 ) );
    }

    using funcy::LN;
    using funcy::Pow;
    constexpr int dim = 3;
    using M = Eigen::Matrix< double, dim, dim >;
    auto c0 = 1., c1 = 1., d0 = 1., d1 = 1.;

    auto initFiberTensor()
    {
        M m;
        m.fill( 0 );
        m( 0, 0 ) = 1;
        return m;
    }

    M fiberTensor = initFiberTensor(), I = funcy::linalg::unit_matrix< M >();
} // namespace

TEST( NeoHooke, Incompressible_Eigen )
{
    auto incompressible_neo_hooke = funcy::incompressible_neo_hooke( c0, I );
    auto f = runTest< M >( incompressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 12 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 36 );
    EXPECT_DOUBLE_EQ( std::get< 3 >( f ), 0 );
}

TEST( NeoHooke, Compressible_Eigen )
{
    auto compressible_neo_hooke = funcy::compressible_neo_hooke< Pow< 2 >, LN >( c0, d0, d1, I );
    auto f = runTest< M >( compressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 30 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 198 );
    EXPECT_DOUBLE_EQ( std::get< 3 >( f ), 3024 );
}

TEST( NeoHooke, ModifiedIncompressible_Eigen )
{
    auto modifiedIncompressible_neo_hooke = funcy::modified_incompressible_neo_hooke( c0, I );
    auto f = runTest< M >( modifiedIncompressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 0 );
    EXPECT_NEAR( std::get< 3 >( f ), 0, 1e-11 );
}

TEST( NeoHooke, ModifiedCompressible_Eigen )
{
    auto modifiedcompressible_neo_hooke =
        funcy::modified_compressible_neo_hooke< Pow< 2 >, LN >( c0, d0, d1, I );
    auto f = runTest< M >( modifiedcompressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 18 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 162 );
    EXPECT_NEAR( std::get< 3 >( f ), 3024, 1e-11 );
}

TEST( MooneyRivlin, Incompressible_Eigen )
{
    auto mooneyRivlin = funcy::incompressible_mooney_rivlin( c0, c1, I );
    auto f = runTest< M >( mooneyRivlin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 36 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 252 );
    EXPECT_NEAR( std::get< 3 >( f ), 1728, 1e-13 );
}

TEST( MooneyRivlin, Compressible_Eigen )
{
    auto mooneyRivlin = funcy::compressible_mooney_rivlin< Pow< 2 >, LN >( c0, c1, d0, d1, I );
    auto f = runTest< M >( mooneyRivlin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 54 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 414 );
    EXPECT_NEAR( std::get< 3 >( f ), 4752, 1e-13 );
}

TEST( Skin_Hendriks, Incompressible_Eigen )
{
    auto skin = funcy::incompressible_skin_hendriks( c0, c1, I );
    auto f = runTest< M >( skin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 12 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 900 );
    EXPECT_NEAR( std::get< 3 >( f ), 20736, 1e-13 );
}

TEST( Skin_Hendriks, Compressible_Eigen )
{
    auto skin = funcy::compressible_skin_hendriks< Pow< 2 >, LN >( c0, c1, d0, d1, I );
    auto f = runTest< M >( skin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 30 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 1062 );
    EXPECT_NEAR( std::get< 3 >( f ), 23760, 1e-13 );
}

TEST( Adipose_SommerHolzapfel, Incompressible_Eigen )
{
    auto adipose = funcy::incompressible_adipose_tissue_sommer_holzapfel( fiberTensor, I );
    auto f = runTest< M >( adipose );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 1.8, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 43.8, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 460.8, 1e-11 );
}

TEST( Adipose_SommerHolzapfel, Compressible_Eigen )
{
    auto adipose = funcy::compressible_adipose_tissue_sommer_holzapfel< Pow< 2 >, LN >(
        d0, d1, fiberTensor, I );
    auto f = runTest< M >( adipose );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 19.8, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 205.8, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 3484.8, 1e-11 );
}

TEST( Muscle_Martins, Incompressible_Eigen )
{
    auto muscle = funcy::incompressible_muscle_tissue_martins( fiberTensor, I );
    auto f = runTest< M >( muscle );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 0, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 0, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 0, 1e-10 );
}

TEST( Muscle_Martins, Compressible_Eigen )
{
    auto muscle =
        funcy::compressible_muscle_tissue_martins< Pow< 2 >, LN >( d0, d1, fiberTensor, I );
    auto f = runTest< M >( muscle );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 18, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 162, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 3024, 1e-10 );
}
