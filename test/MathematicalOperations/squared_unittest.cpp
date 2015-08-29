#include "FunG/CMath/pow.hh"
#include "FunG/generate.hh"
#include "FunG/finalize.hh"
#include "FunG/variable.hh"

#include <gtest/gtest.h>

TEST(SquaredTest,Update)
{
  auto fun = FunG::CMath::Pow<2>(2.)^2;
  EXPECT_NO_THROW( fun.update(-2) );
  EXPECT_DOUBLE_EQ( fun.d0() , 16. );
}

TEST(SquaredTest,UpdateVariable)
{
  auto x = FunG::variable<0>(2.);
  auto fun = FunG::CMath::Pow<2,1>()(x)^2;
  EXPECT_DOUBLE_EQ( fun.d0() , 16. );
  EXPECT_NO_THROW( fun.updateVariable<0>(-1.) );
  EXPECT_NO_THROW( fun.update(0); );
  EXPECT_DOUBLE_EQ( fun.d0() , 1. );
}

TEST(SquaredTest,D0)
{
  using FunG::CMath::Pow;
  auto fun = Pow<2>(2.)^2;
  EXPECT_DOUBLE_EQ( fun.d0() , 16. );
}

TEST(SquaredTest,D1)
{
  using FunG::CMath::Pow;
  auto fun = FunG::finalize_scalar ( Pow<2>(2.)^2 );
  EXPECT_DOUBLE_EQ( fun.d1() , 32. );
}

TEST(SquaredTest,D2)
{
  using FunG::CMath::Pow;
  auto fun = FunG::finalize_scalar( Pow<2>(2.)^2 );
  EXPECT_DOUBLE_EQ( fun.d2() , 48. );
}

TEST(SquaredTest,D3)
{
  using FunG::CMath::Pow;
  auto fun = FunG::finalize_scalar( Pow<2>(2.)^2 );
  EXPECT_DOUBLE_EQ( fun.d3() , 48. );
}



