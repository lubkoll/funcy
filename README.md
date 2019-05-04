[![Build Status](https://travis-ci.org/lubkoll/funcy.svg?branch=master)](https://travis-ci.org/lubkoll/funcy)
[![Coverage Status](https://coveralls.io/repos/github/lubkoll/funcy/badge.svg?branch=master)](https://coveralls.io/github/lubkoll/funcy?branch=master)
[![Documentation](https://codedocs.xyz/lubkoll/funcy.svg)](https://codedocs.xyz/lubkoll/funcy/)
# funcy - automatic differentiation for biomechanical modeling

[install funcy](INSTALL.md)

### Using funcy

The function <img src="https://latex.codecogs.com/gif.latex?f(x)&space;=&space;x^{3/2}&plus;\sin(\sqrt{x})" title="f(x) = x^{3/2}+\sin(\sqrt{x})" /> with funcy:
```cpp
#include <funcy/funcy.hh>

int main()
{
    const auto y = funcy::sqrt(1.);
    auto f = finalize( pow<3>(y) + sin(y) );
    
    std::cout << "f(3) = " << f(3) << std::endl;
    f.update(4);
    std::cout << "f'(4) = " << f.d1() << std::endl;
    std::cout << "f'''(4) = " << f.d3() << std::endl;
}
```

See <a href="http://lubkoll.github.io/funcy">http://lubkoll.github.io/funcy</a>.
