#include <funcy/examples/biomechanics/adipose_tissue_sommer_holzapfel.h>
#include <funcy/examples/biomechanics/muscle_tissue_martins.h>
#include <funcy/examples/biomechanics/skin_tissue_hendriks.h>
#include <funcy/examples/rubber/mooney_rivlin.h>
#include <funcy/examples/rubber/neo_hooke.h>

#include <Eigen/Dense>
#include <gtest/gtest.h>

#include <dune/common/fmatrix.hh>
#include <tuple>

namespace
{

    using funcy::LN;
    using funcy::Pow;
    constexpr int dim = 3;
    using M = Dune::FieldMatrix< double, dim, dim >;

    template < class M, class Function >
    auto run_test( Function& f )
    {
        const auto a = funcy::linalg::unit_matrix< M >();
        M da0 = a;
        da0 *= 2;
        M da1 = a;
        da1 *= 3;
        M da2 = a;
        da2 *= 4;

        f.update( a );

        return std::make_tuple( f(), f.d1( da0 ), f.d2( da0, da1 ), f.d3( da0, da1, da2 ) );
    }
    const auto c0 = 1.0;
    const auto c1 = 1.0;
    const auto d0 = 1.0;
    const auto d1 = 1.0;

    auto initfiber_tensor()
    {
        M m( 0 );
        m[ 0 ][ 0 ] = 1;
        return m;
    }

    M fiber_tensor = initfiber_tensor();
    M I = funcy::linalg::unit_matrix< M >();
} // namespace

TEST( NeoHooke, Incompressible_DUNE )
{
    auto incompressible_neo_hooke = funcy::incompressible_neo_hooke( c0, I );
    auto f = run_test< M >( incompressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 12 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 36 );
    EXPECT_DOUBLE_EQ( std::get< 3 >( f ), 0 );
}

TEST( NeoHooke, Compressible_DUNE )
{
    auto compressible_neo_hooke = funcy::compressible_neo_hooke< Pow< 2 >, LN >( c0, d0, d1, I );
    auto f = run_test< M >( compressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 30 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 198 );
    EXPECT_DOUBLE_EQ( std::get< 3 >( f ), 3024 );
}

TEST( NeoHooke, ModifiedIncompressible_DUNE )
{
    auto modified_incompressible_neo_hooke = funcy::modified_incompressible_neo_hooke( c0, I );
    auto f = run_test< M >( modified_incompressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 0 );
    EXPECT_NEAR( std::get< 3 >( f ), 0, 1e-11 );
}

TEST( NeoHooke, ModifiedCompressible_DUNE )
{
    auto modifiedcompressible_neo_hooke =
        funcy::modified_compressible_neo_hooke< Pow< 2 >, LN >( c0, d0, d1, I );
    auto f = run_test< M >( modifiedcompressible_neo_hooke );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 18 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 162 );
    EXPECT_NEAR( std::get< 3 >( f ), 3024, 1e-11 );
}

TEST( MooneyRivlin, Incompressible_DUNE )
{
    auto mooney_rivlin = funcy::incompressible_mooney_rivlin( c0, c1, I );
    auto f = run_test< M >( mooney_rivlin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 36 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 252 );
    EXPECT_NEAR( std::get< 3 >( f ), 1728, 1e-13 );
}

TEST( MooneyRivlin, Compressible_DUNE )
{
    auto mooney_rivlin = funcy::compressible_mooney_rivlin< Pow< 2 >, LN >( c0, c1, d0, d1, I );
    auto f = run_test< M >( mooney_rivlin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 54 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 414 );
    EXPECT_NEAR( std::get< 3 >( f ), 4752, 1e-13 );
}

TEST( Skin_Hendriks, Incompressible_DUNE )
{
    auto skin = funcy::incompressible_skin_hendriks( c0, c1, I );
    auto f = run_test< M >( skin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 12 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 900 );
    EXPECT_NEAR( std::get< 3 >( f ), 20736, 1e-13 );
}

TEST( Skin_Hendriks, Compressible_DUNE )
{
    auto skin = funcy::compressible_skin_hendriks< Pow< 2 >, LN >( c0, c1, d0, d1, I );
    auto f = run_test< M >( skin );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_DOUBLE_EQ( std::get< 1 >( f ), 30 );
    EXPECT_DOUBLE_EQ( std::get< 2 >( f ), 1062 );
    EXPECT_NEAR( std::get< 3 >( f ), 23760, 1e-13 );
}

TEST( Adipose_SommerHolzapfel, Incompressible_DUNE )
{
    auto adipose = funcy::incompressible_adipose_tissue_sommer_holzapfel( fiber_tensor, I );
    auto f = run_test< M >( adipose );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 1.8, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 43.8, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 460.8, 1e-11 );
}

TEST( Adipose_SommerHolzapfel, Compressible_DUNE )
{
    auto adipose = funcy::compressible_adipose_tissue_sommer_holzapfel< Pow< 2 >, LN >(
        d0, d1, fiber_tensor, I );
    auto f = run_test< M >( adipose );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 19.8, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 205.8, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 3484.8, 1e-11 );
}

TEST( Muscle_Martins, Incompressible_DUNE )
{
    auto muscle = funcy::incompressible_muscle_tissue_martins( fiber_tensor, I );
    auto f = run_test< M >( muscle );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 0, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 0, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 0, 1e-10 );
}

TEST( Muscle_Martins, Compressible_DUNE )
{
    auto muscle =
        funcy::compressible_muscle_tissue_martins< Pow< 2 >, LN >( d0, d1, fiber_tensor, I );
    auto f = run_test< M >( muscle );
    EXPECT_DOUBLE_EQ( std::get< 0 >( f ), 0 );
    EXPECT_NEAR( std::get< 1 >( f ), 18, 1e-11 );
    EXPECT_NEAR( std::get< 2 >( f ), 162, 1e-11 );
    EXPECT_NEAR( std::get< 3 >( f ), 3024, 1e-10 );
}
