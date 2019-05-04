[![Build Status](https://travis-ci.org/lubkoll/funcy.svg?branch=master)](https://travis-ci.org/lubkoll/funcy)
[![Coverage Status](https://coveralls.io/repos/github/lubkoll/funcy/badge.svg?branch=master)](https://coveralls.io/github/lubkoll/funcy?branch=master)
[![Documentation](https://codedocs.xyz/lubkoll/funcy.svg)](https://codedocs.xyz/lubkoll/funcy/)
# funcy - automatic differentiation for biomechanical modeling

## Installation
funcy is header-only and requires no installation. To make it available in the local cmake-registry you still may find it useful install funcy using cmake.


#### Install funcy via cmake
```
mkdir build
cd build
cmake .. -DBuildTest=ON -DCMAKE_INSTALL_PREFIX=<install-prefix>
cmake --build . --target install
```
#### To include funcy in your project add this to your CMakeLists.txt:
```
find_package(funcy REQUIRED)
target_link_libraries(<target> PRIVATE funcy::funcy)
```

## Using funcy

The function ![alt text](doc/Eq1.gif) with *funcy*:
```cpp
#include <funcy/funcy.hh>

int main()
{
    using namespace funcy;
    // qualified function to sqrt to distinguish from the c-function sqrt in math.h, commonly included in the c++-header cmath.
    const auto y = funcy::sqrt(1.);
    auto f = finalize( pow<3>(y) + sin(y) );

    std::cout << "f(3) = " << f(3) << std::endl;
    f.update(4);
    std::cout << "f'(4) = " << f.d1() << std::endl;
    std::cout << "f'''(4) = " << f.d3() << std::endl;
}
```
The function `finalize` simplifies usage of `f`, taking advantage of the fact that it depends on only one variable and is defined on a one-dimensional space. The following examples illustrate usage without finalize and with vector and matrix-valued arguments.

A model for **nonlinear heat transfer** ![alt text](doc/Eq2.gif):
```cpp
#include <funcy/funcy.hh>

template <class Vector>
auto heatModel(double c, double d, double u0, const Vector& du0)
{
    using funcy::variable;
    const auto u = variable<0>(u0);
    const auto du = variable<0>(du0);
    return (c+d*squared(u))*du;
}

int main()
{
    auto f = heatModel(c, d, u, du);
    // update function value
    f.template update<0>(std::make_tuple(u, du));

    std::cout << "f(u, du) = " << f() << std::endl;
    // derivative with respect to variable with id 0
    std::cout << "f'(4) = " << f.template d1<0>(std::make_tuple(v,dv)) << std::endl;
}
```

A **complex biomechanical model** for adipose tissue, based on isotropic and anisotropic matrix invariants ![alt text](doc/Eq3.gif):
```cpp
#include <funcy/funcy.hh>

template <class Matrix>
auto adiposeTissue(double cCells, double k1, double k2, double kappa,
                   const Matrix& M const Matrix& F, int n = dim<Matrix>())
{
    using funcy::finalize;
    using namespace funcy::linalg;

    auto aniso = kappa*i1(F) + (1-3*kappa) * i4(F,M) - 1;
    auto materialLaw = cCells*( i1(F) - n ) + (k1/k2) * ( exp(k2*squared(aniso)) - 1 );

    return finalize( materialLaw( strainTensor(F) ) );
}

int main()
{
    // update function value
    f.update(du);

    std::cout << "f(du) = " << f() << std::endl;
    std::cout << "f''(du)(dv,dw) = " << f.d2(dv,dw) << std::endl;
}
```

## Citing
L. Lubkoll: [FunG - Automatic differentiation for invariant-based modeling.](https://journals.ub.uni-heidelberg.de/index.php/ans/article/download/27477/29446) Archive of Numerical Software, vol. 5, no. 1, 2017, pp. 169-192, DOI: 10.11588/ans.2017.1.27477

## Documentation

Available here: [![Documentation](https://codedocs.xyz/lubkoll/funcy.svg)](https://codedocs.xyz/lubkoll/funcy/)

## Compatibility

funcy can work with any type that satisfies basic arithmetic requirements as described in [requirements](REQUIREMENTS.md). Particular support has been implemented for scalars, vectors and matrices, enabling *funcy* to be used with all popular matrix libraries.


## Optimization Strategies

For details, and performance comparisons with other AD-libraries, see [FunG - Automatic differentiation for invariant-based modeling.](https://journals.ub.uni-heidelberg.de/index.php/ans/article/download/27477/29446)

## Publications:

Published:

* L. Lubkoll: [FunG - Automatic differentiation for invariant-based modeling.](https://journals.ub.uni-heidelberg.de/index.php/ans/article/download/27477/29446) Archive of Numerical Software, vol. 5, no. 1, 2017, pp. 169-192, DOI: 10.11588/ans.2017.1.27477
* L. Lubkoll, A. Schiela, M. Weiser: **An affine covariant composite step method for optimization with PDEs as equality constraints.**<br> Opt. Meth. Softw., 32(5), pp. 1132-1161, 2016, [(Preprint)](https://opus4.kobv.de/opus4-zib/files/5395/ZR-15-09.pdf)
* L. Lubkoll: **An Optimal Control Approach to Implant Shape Design: Modeling, Analysis and Numerics.**<br> Dissertation, Universität Bayreuth, 2015

Preprints:

* A. Schiela, M. Stöcklein: [Optimal Control of Static Contact in Finite Strain Elasticity.](https://spp1962.wias-berlin.de/preprints/097.pdf) 2018
* M. Schaller, A. Schiela, M. Stöcklein: [A Composite Step Method with Inexact Step Comptations for PDE Constrained Optimization.](https://spp1962.wias-berlin.de/preprints/098.pdf) 2018
